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
 * PollingLab assignment and starter code (c) 2021-24 Christopher A. Bohn
 * PollingLab solution (c) the above-named student(s)
 */

#include <CowPi.h>
#include "display.h"
#include "number_builder.h"
#include "io_functions.h"


void print_number(int32_t number);
int32_t process_digit(int32_t old_number, uint8_t digit);
bool overflow_occurred(int32_t old_number, int32_t new_number);

typedef enum {
    NOT_PRESSED, RESPOND_TO_PRESS, PRESSED, RESPOND_TO_RELEASE
} input_states_t;


void initialize_number_system(void) {
    record_build_timestamp(__FILE__, __DATE__, __TIME__);
    clear_display();                                                // requirement 7
}


void build_number(void) {
    // Req 1:     left switch to left = left justified; left switch to right = right justified
    // Reg 2, 6:  toggling switches has well-defined behavior only when it doesn't require immediate attention
    // Req 3, 4:  right switch to left = decimal input
    // Req 3, 5:  right switch to right = hexadecimal input
    // Req 7:     display initially blank
    // Req 8:     decimal output on first row; hexadecimal output on second row
    // Req 9, 10: keypress illuminates right LED 500ms; buttonpress illuminates left LED 500ms -- note that 500ms = 500,000us
    // Req 11:    building numbers
    //        a, k                - 32-bit signed integer with overflow
    //        b, c, d, f, g, h, i - formatting
    //        e                   - left button negates
    //        j                   - right button clears display & sets number to 0
    // Req 12:    respond only once to each distinct press
    // Req 13:    responsiveness
    static input_states_t keypad_state = NOT_PRESSED;
    static input_states_t left_button_state = NOT_PRESSED;
    static input_states_t right_button_state = NOT_PRESSED;
    ;
}

void clear_display(void) {
    display_string(0, "");
    display_string(1, "");   
}

void print_number(int32_t number) {
    ;
}

int32_t process_digit(int32_t old_number, uint8_t digit) {
    return 0;
}

bool overflow_occurred(int32_t old_number, int32_t new_number) {
    return false;
}
