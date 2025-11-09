/**************************************************************************//**
 *
 * @file number_builder.c
 *
 * @author (TYPE YOUR NAME HERE)
 * @author (TYPE YOUR PARTNER'S NAME HERE, IF APPLICABLE)
 *
 * @brief Code to demonstrate "building" a number by polling inputs.
 *
 ******************************************************************************/

/*
 * CalculatorLab assignment and starter code (c) 2020-25 Christopher A. Bohn
 * CalculatorLab solution (c) the above-named student(s)
 */

#include <CowPi.h>
#include "display.h"
#include "number_builder.h"


typedef enum {
    NOT_PRESSED, RESPOND_TO_PRESS, PRESSED, RESPOND_TO_RELEASE
} input_states_t;


static char buffer[18] = {0};
static int16_t number = 0;
static bool overflow = false;

int16_t get_number(void) { return number; }
bool number_overflowed(void) { return overflow; }
void reset_number(void) { number = 0; overflow = false; }


static int16_t process_digit(int16_t old_number, uint8_t digit);
static bool overflow_occurred(int16_t old_number, int16_t new_number);


void build_number(void) {
    static input_states_t keypad_state = NOT_PRESSED;
    static input_states_t left_button_state = NOT_PRESSED;
    static input_states_t right_button_state = NOT_PRESSED;



}

static int16_t process_digit(int16_t old_number, uint8_t digit) {
    return 0;
}

static bool overflow_occurred(int16_t old_number, int16_t new_number) {
    return false;
}