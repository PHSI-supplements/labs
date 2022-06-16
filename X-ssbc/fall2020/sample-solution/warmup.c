/*
 * Simulated Single Board Computer, (c) 2020 Christopher A. Bohn
 *
 * Student: Sample Solution
 */

#include "ssbc.h"

pthread_mutex_t *mutex;
uint32_t *display_controls;
uint8_t *toggle_control;
uint16_t *keypad_control;
int running = 1;

const static uint8_t conversion[] = {0x3F, 0x03, 0x6D, 0x67, 0x53, 0x76, 0x7E, 0x23, 0x7F, 0x77};

int main() {
    ssbc_launch();
    mutex = ssbc_get_mutex();
    display_controls = ssbc_get_7_segment_address();
    toggle_control = ssbc_get_toggle_address();
    keypad_control = ssbc_get_keypad_address();
    keypad_control++;
    uint32_t display231x = (uint32_t)conversion[2] << 24u | (uint32_t)conversion[3] << 16u | (uint32_t)conversion[1] << 8u | 0u;
    while (running) {
        pthread_mutex_lock(mutex);
        uint8_t toggle_positions = *toggle_control;
        uint16_t number = *keypad_control & 0x0Fu;
        uint32_t number_display = 0x0u;
        if (number < 10) {
            number_display = conversion[number];
        }
        pthread_mutex_unlock(mutex);
        if(toggle_positions & 0x8u) {
            pthread_mutex_lock(mutex);
            *display_controls = *display_controls | display231x;
            pthread_mutex_unlock(mutex);
        } else {
            pthread_mutex_lock(mutex);
            *display_controls = *display_controls & 0xFFu;
            pthread_mutex_unlock(mutex);
        }
        if(toggle_positions & 0x1u) {
            pthread_mutex_lock(mutex);
            *display_controls = (*display_controls & 0xFFFFFF00u) | number_display;
            pthread_mutex_unlock(mutex);
        } else {
            pthread_mutex_lock(mutex);
            *display_controls = *display_controls & 0xFFFFFF00u;
            pthread_mutex_unlock(mutex);
        }
    }
    ssbc_terminate();
    return 0;
}
