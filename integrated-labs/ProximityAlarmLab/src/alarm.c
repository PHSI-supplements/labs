/**************************************************************************//**
 *
 * @file alarm.c
 *
 * @author (TYPE YOUR NAME HERE)
 * @author (TYPE YOUR PARTNER'S NAME HERE, IF APPLICABLE)
 *
 * @brief Code to manage the piezobuzzer and LEDs.
 *
 ******************************************************************************/

/*
 * ProximityAlarmLab assignment and starter code (c) 2023-25 Christopher A. Bohn
 * ProximityAlarmLab solution (c) the above-named student(s)
 */

#include <CowPi.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "display.h"
#include "common.h"
#include "interrupt_support.h"
#include "alarm.h"


static char buffer[18] = {0};


#define INTERRUPT_PERIOD_us (500U)  // 1kHz
//#define INTERRUPT_PERIOD_us (100U)  // 5kHz
static bool volatile sound_alarm;
static uint32_t silence_buzzer_at;


static void handle_alarm_timer(void);


void initialize_alarm(void) {
    cowpi_set_output_pins(1 << BUZZER_PIN);     // configures the pin
    sound_alarm = false;
    silence_buzzer_at = 0;
    /* CONFIGURE THE INTERRUPT/REGISTER THE ISR HERE */

}

void manage_alarm(void) {
    static input_states_t left_button_state = NOT_PRESSED;
    static input_states_t right_button_state = NOT_PRESSED;
    bool left_button_pressed = cowpi_debounce_byte(cowpi_left_button_is_pressed(), LEFT_BUTTON_DOWN);
    bool right_button_pressed = cowpi_debounce_byte(cowpi_right_button_is_pressed(), RIGHT_BUTTON_DOWN);
    switch(left_button_state) {
        case NOT_PRESSED:
            if (left_button_pressed) {
                left_button_state = RESPOND_TO_PRESS;
            }
            break;
        case RESPOND_TO_PRESS:
            chirp();
            left_button_state = PRESSED;
            break;
        case PRESSED:
            if (!left_button_pressed) {
                left_button_state = RESPOND_TO_RELEASE;
            }
            break;
        case RESPOND_TO_RELEASE:
            left_button_state = NOT_PRESSED;
            break;
        default:
            sprintf(buffer, "ERROR line %d\n", __LINE__);
            display_string(6, buffer);
    }
    switch(right_button_state) {
        case NOT_PRESSED:
            if (right_button_pressed) {
                right_button_state = RESPOND_TO_PRESS;
            }
            break;
        case RESPOND_TO_PRESS:
            silence_buzzer_at = UINT32_MAX;
            sound_alarm = true;
            right_button_state = PRESSED;
            break;
        case PRESSED:
            if (!right_button_pressed) {
                right_button_state = RESPOND_TO_RELEASE;
            }
            break;
        case RESPOND_TO_RELEASE:
            sound_alarm = false;
            right_button_state = NOT_PRESSED;
            break;
        default:
            sprintf(buffer, "ERROR line %d\n", __LINE__);
            display_string(6, buffer);
    }
}

void chirp(void) {
    /* YOUR CODE GOES HERE */


}

static void handle_alarm_timer(void) {
    /* YOUR CODE GOES HERE */


}