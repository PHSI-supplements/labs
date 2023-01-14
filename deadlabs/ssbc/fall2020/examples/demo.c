#include "ssbc.h"

int main() {
    ssbc_launch();
    uint8_t letters[] = {0x78, 0x4F, 0x76, 0x6F}; // {f,d,s,a}
    pthread_mutex_t *mutex = ssbc_get_mutex();
    uint32_t *display_controls = ssbc_get_7_segment_address();
    uint8_t *toggle_control = ssbc_get_toggle_address();
    uint16_t *keypad_control = ssbc_get_keypad_address();
    keypad_control += 1;
    uint8_t lastNumber = 0x0F;
    int running = 1;
    while (running) {
        pthread_mutex_lock(mutex);
        uint8_t toggle_positions = *toggle_control;
        uint8_t number = *keypad_control & 0x0Fu;
        pthread_mutex_unlock(mutex);
        for (unsigned int i = 0; i < 4; i++) {
            if (toggle_positions & 0x1u << i) {
                pthread_mutex_lock(mutex);
                uint32_t clear_position = ~(0xFFu << (8 * i));
                uint32_t character_in_position = (uint32_t)(letters[i]) << (8 * i);
                *display_controls = (*display_controls & clear_position) | character_in_position;
                pthread_mutex_unlock(mutex);
            } else {
                pthread_mutex_lock(mutex);
                uint32_t clear_position = ~(0xFFu << (8 * i));
                *display_controls = *display_controls & clear_position;
                pthread_mutex_unlock(mutex);
            }
        }
        if (number != lastNumber) {
            pthread_mutex_lock(mutex);
            ssbc_print("%d\n", number);
            pthread_mutex_unlock(mutex);
        }
        lastNumber = number;
        if (number == 0) {
            running = 0;
        }
    }
    ssbc_terminate();
    return 0;
}
