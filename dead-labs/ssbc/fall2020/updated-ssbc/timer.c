#include <stdint.h>
#include <unistd.h>
#include "ssbc.h"

uint32_t bcdToSevenSegmentDisplay(uint16_t bcdNumber);

int main() {
    ssbc_launch();
    pthread_mutex_t *mutex = ssbc_get_mutex();
    uint32_t *display_controls = ssbc_get_7_segment_address();
    uint8_t *toggle_control = ssbc_get_toggle_address();
    uint8_t *keypad_control = ssbc_get_keypad_address();
    keypad_control += 2;
    uint16_t bcd2310 = (2u<<12u) | (3u<<8u) | (1u<<4u) | 0x0u;
    uint16_t bcdXXX0 = 0xFFF0;
    int hot = 0;
    uint16_t bcdValue = 0xFFFF;
    int running = 1;
    while (running) {
        pthread_mutex_lock(mutex);
        uint8_t toggle_positions = *toggle_control;
        uint8_t number = *keypad_control & 0x0Fu;
        pthread_mutex_unlock(mutex);
        if (toggle_positions || !hot) {
            if (toggle_positions & 0x8u) {
                bcdValue = bcd2310;
            } else {
                bcdValue = bcdXXX0;
            }
            if (toggle_positions & 0x1u) {
                bcdValue = bcdValue | number;
                hot = 1;
            } else {
                bcdValue = bcdValue | 0x0Fu;
                hot = 0;
            }
            pthread_mutex_lock(mutex);
            *display_controls = bcdToSevenSegmentDisplay(bcdValue);
            pthread_mutex_unlock(mutex);
        } else {
            sleep(1);
            do {
                bcdValue--;
                pthread_mutex_lock(mutex);
                *display_controls = bcdToSevenSegmentDisplay(bcdValue);
                pthread_mutex_unlock(mutex);
                sleep(1);
            } while(bcdValue & 0x000Fu);
            running = 0;
        }
    }
    ssbc_terminate();
    return 0;
}

const static uint8_t conversion[] = {0x3F, 0x03, 0x6D, 0x67, 0x53, 0x76, 0x7E, 0x23, 0x7F, 0x77};

uint32_t bcdToSevenSegmentDisplay( uint16_t bcdNumber ) {
    uint32_t result = 0x0;
    uint16_t mask = 0x000F;
    uint8_t currentBCD;
    uint32_t currentDisplay;
    for(unsigned int i=0; i<4; i++) {
        currentBCD = (bcdNumber >> (4 * i)) & mask; // NOLINT(hicpp-signed-bitwise)
        if (currentBCD < 10) {
            currentDisplay = conversion[currentBCD];
            result = result | (currentDisplay << 8 * i);
        }
    }
//    ssbc_print("0x%04x\t0x%08x\n", bcdNumber, result);
    return result;
}