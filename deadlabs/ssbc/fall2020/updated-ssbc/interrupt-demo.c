#include "ssbc.h"

uint32_t bcdToSevenSegmentDisplay(uint16_t bcdNumber);
void number_handler();
int position = -1;
int running = 1;

pthread_mutex_t *mutex;
uint32_t *display_controls;
uint8_t *toggle_control;
uint16_t *keypad_control;

int main() {
    ssbc_launch();
    mutex = ssbc_get_mutex();
    display_controls = ssbc_get_7_segment_address();
    toggle_control = ssbc_get_toggle_address();
    keypad_control = ssbc_get_keypad_address();
    // enable interrupt
    *keypad_control = *keypad_control | 0x1u;
    sigset(SIGUSR1, number_handler);
    while(running);
    ssbc_terminate();
    return 0;
}

const static uint8_t conversion[] = {0x3F, 0x03, 0x6D, 0x67, 0x53, 0x76, 0x7E, 0x23, 0x7F, 0x77};

void number_handler() {
    if (++position < 4) {
        pthread_mutex_lock(mutex);
        uint16_t number = keypad_control[1] & 0x0Fu;
        *display_controls = (*display_controls << 8u) | conversion[number];
        // clear the dirty bit
        keypad_control[0] &= 0xFFFDu;
        pthread_mutex_unlock(mutex);
    } else {
        running = 0;
    }
}


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
    return result;
}
