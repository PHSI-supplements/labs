/*
 * Simulated Single Board Computer, (c) 2020 Christopher A. Bohn
 *
 * Student: Sample Solution
 * Evaluate for bonus credit: yes
 */

#include "ssbc.h"

pthread_mutex_t *mutex;
uint32_t *display_controls;
uint8_t *toggle_control;
uint16_t *keypad_control;

typedef enum {
    WAITING, BUILDING1, BUILDING2, ADDING, SUBTRACTING
} state;
state new_state, old_state;
int operand1, operand2, building_operand;

int running = 1;

const static uint8_t conversion[] = {0x3F, 0x03, 0x6D, 0x67, 0x53, 0x76, 0x7E, 0x23, 0x7F, 0x77};

void number_builder();
uint32_t int_to_display_vector( int value );

int main() {
    ssbc_launch();
    mutex = ssbc_get_mutex();
    display_controls = ssbc_get_7_segment_address();
    toggle_control = ssbc_get_toggle_address();
    keypad_control = ssbc_get_keypad_address();
    operand1 = 0;
    operand2 = 0;
    new_state = WAITING;
    // enable interrupt
    *keypad_control = *keypad_control | 0x1u;
    sigset(SIGUSR1, number_builder);
    while (running) {
        old_state = new_state;
        pthread_mutex_lock(mutex);
        uint8_t toggle = *toggle_control;
        pthread_mutex_unlock(mutex);
        switch (toggle) {
            case 0x8u:
                new_state = BUILDING1;
                if (old_state != BUILDING1) {
                    building_operand = 0;
                }
                pthread_mutex_lock(mutex);
                *display_controls = int_to_display_vector(building_operand);
                pthread_mutex_unlock(mutex);
                break;
            case 0x4u:
                new_state = BUILDING2;
                if (old_state != BUILDING2) {
                    building_operand = 0;
                }
                pthread_mutex_lock(mutex);
                *display_controls = int_to_display_vector(building_operand);
                pthread_mutex_unlock(mutex);
                break;
            case 0x2u:
                new_state = ADDING;
                pthread_mutex_lock(mutex);
                *display_controls = int_to_display_vector(operand1 + operand2);
                pthread_mutex_unlock(mutex);
                break;
            case 0x1u:
                new_state = SUBTRACTING;
                pthread_mutex_lock(mutex);
                *display_controls = int_to_display_vector(operand1 - operand2);
                pthread_mutex_unlock(mutex);
                break;
            case 0x0u:
                new_state = WAITING;
                switch (old_state) {
                    case BUILDING1:
                        operand1 = (building_operand < 10000) ? building_operand : operand1;
                        break;
                    case BUILDING2:
                        operand2 = (building_operand < 10000) ? building_operand : operand2;
                        break;
                    case WAITING:
                    case ADDING:
                    case SUBTRACTING:
                        break;
                    default:
                        pthread_mutex_lock(mutex);
                        ssbc_print("Unreachable code has been reached: new state = WAITING; old state = %d\n", old_state);
                        pthread_mutex_unlock(mutex);
                }
                pthread_mutex_lock(mutex);
                *display_controls = 0x0u;
                pthread_mutex_unlock(mutex);
                break;
            default:
                pthread_mutex_lock(mutex);
                ssbc_print("Unspecified state: 0x%x; setting state to WAITING\n", toggle);
                pthread_mutex_unlock(mutex);
                new_state = WAITING;
        }
    }
    ssbc_terminate();
    return 0;
}

void number_builder() {
    if (new_state == BUILDING1 || new_state == BUILDING2) {
        pthread_mutex_lock(mutex);
        uint8_t numeral = keypad_control[1] & 0xFu;
        keypad_control[0] = keypad_control[0] & 0xFFFDu;    // clearing dirty bit
        pthread_mutex_unlock(mutex);
        building_operand = building_operand * 10 + numeral;
    }
}


uint32_t int_to_display_vector( int value ) {
    if (value == 0) {
        return conversion[0];
    }
    if (value > 9999 || value < -999) {
        return 0x007C4848u; // Err
    }
    uint32_t vector = 0x0u;
    uint32_t working_value = (uint32_t)value;
    uint8_t digit = 0;
    int is_negative = 0;
    if (value < 0) {
        is_negative = 1;
        working_value = -working_value;
    }
    do {
        uint32_t numeral = working_value % 10;
        vector = vector | ((uint32_t)conversion[numeral] << (8u * digit++));
        working_value = working_value / 10;
    } while (working_value);
    if (is_negative) {
        vector = vector | (0x40u << (8u * digit)); // negative sign
    }
    return vector;
}
