/**************************************************************************//**
 *
 * @file io_functions.c
 *
 * @author (TYPE YOUR NAME HERE)
 * @author (TYPE YOUR PARTNER'S NAME HERE, IF APPLICABLE)
 *
 * @brief Functions that students must re-implement using memory-mapped I/O.
 *
 ******************************************************************************/

/*
 * PollingLab assignment and starter code (c) 2021-24 Christopher A. Bohn
 * PollingLab solution (c) the above-named student(s)
 */

#include <CowPi.h>
#include "io_functions.h"
#include "starter.h"


static bool show_key_press;

/****************************************************/
/***** I/O CODE COMPLETED WITH YOUR LAB SECTION *****/
/****************************************************/

// Layout of Matrix Keypad
//        1 2 3 A
//        4 5 6 B
//        7 8 9 C
//        * 0 # D
// This array holds the values we want each keypad button to correspond to
static const uint8_t keys[4][4] = {
        {},
        {},
        {},
        {}
};

// Pointers to memory-mapped I/O structures
static cowpi_ioport_t volatile *ioports;    // an array of I/O ports
static cowpi_timer8bit_t volatile *timer;   // TIMER0

/**
 * @brief Assigns I/O register addresses to pointers and instructs CowPi library to use `send_halfbyte()`.
 */
void initialize_io(bool key_mode) {
    show_key_press = key_mode;
    // Uncomment these lines and set the correct addresses during lab time
    // ioports = (cowpi_ioport_t *) (0x00);
    // timer = (cowpi_timer8bit_t *) (0x00);
}

/**
 * @brief Detects whether a key -- *any* key -- on the numeric keypad is being pressed.
 *
 * If no key is being pressed, then all column inputs will be high.
 * On the other hand, if a key is being pressed, then one of the column inputs will be low.
 *
 * This function really isn't necessary -- this function is, however, a useful warm-up exercise to do with a
 * lab partner when you're learning memory-mapped I/O.
 *
 * @return `true` if a key is pressed, `false` otherwise
 */
static bool key_is_pressed(void) {
    // this is four distinct reads to figure out if any of the column pins has a 0 on it -- can you do it in one read?
    bool key_is_pressed = !(digitalRead(14) && digitalRead(15) && digitalRead(16) && digitalRead(17));
    return cowpi_debounce_byte(key_is_pressed, INPUT_X);
}

/**
 * @brief Tuns the left LED on or off.
 *
 * An LED illuminates when the pin is placed high and deluminates when the pin is placed low.
 *
 * @param turn_on a boolean value indicating whether the led should be turn on (`true`) or off (`false`)
 */
void set_left_led(bool turn_on) {
    if (turn_on) {
        cowpi_illuminate_left_led();
    } else {
        cowpi_deluminate_left_led();
    }
}


/******************************************/
/***** I/O CODE COMPLETED ON YOUR OWN *****/
/******************************************/


/**
 * @brief Reports the number of microseconds since the system was powered-up.
 * 
 * The number of microseconds will reset after approximately 72 minutes.
 * 
 * @return the number of microseconds that the system has been running
 */
uint32_t get_microseconds(void) {
    // global variable `timer_overflow_count` increments every 1024 microseconds
    // TIMER0's counter increments every 4 microseconds
    return micros();
}


/**
 * @brief Reports whether the left button is pressed.
 *
 * A pressed button grounds a pulled-high input.
 *
 * @return `true` if the button is pressed, `false` otherwise
 */
bool left_button_is_pressed(void) {
    bool button_is_pressed = cowpi_left_button_is_pressed();
    return cowpi_debounce_byte(button_is_pressed, LEFT_BUTTON_DOWN);
}

/**
 * @brief Reports whether the right button is pressed.
 *
 * A pressed button grounds a pulled-high input.
 *
 * @return `true` if the button is pressed, `false` otherwise
 */
bool right_button_is_pressed(void) {
    bool button_is_pressed = cowpi_right_button_is_pressed();
    return cowpi_debounce_byte(button_is_pressed, RIGHT_BUTTON_DOWN);
}

/**
 * @brief Reports whether the left switch is in the left position.
 *
 * A switch in the left position grounds a pulled-high input.
 *
 * @return `true` if the switch is in the left position, `false` otherwise
 */
bool left_switch_is_in_left_position(void) {
    return !left_switch_is_in_right_position();
}

/**
 * @brief Reports whether the left switch is in the right position.
 *
 * A switch in the right position floats, allowing pulled-high input to remain high.
 *
 * @return `true` if the switch is in the right position, `false` otherwise
 */
bool left_switch_is_in_right_position(void) {
    bool switch_in_position = cowpi_left_switch_is_in_right_position();
    return cowpi_debounce_byte(switch_in_position, LEFT_SWITCH_RIGHT);
}

/**
 * @brief Reports whether the right switch is in the left position.
 *
 * A switch in the left position grounds a pulled-high input.
 *
 * @return `true` if the switch is in the left position, `false` otherwise
 */
bool right_switch_is_in_left_position(void) {
    return !right_switch_is_in_right_position();
}

/**
 * @brief Reports whether the right switch is in the right position.
 *
 * A switch in the right position floats, allowing pulled-high input to remain high.
 *
 * @return `true` if the switch is in the right position, `false` otherwise
 */
bool right_switch_is_in_right_position(void) {
    bool switch_in_position = cowpi_right_switch_is_in_right_position();
    return cowpi_debounce_byte(switch_in_position, RIGHT_SWITCH_RIGHT);
}

/**
 * @brief Tuns the right LED on or off.
 *
 * An LED illuminates when the pin is placed high and deluminates when the pin is placed low.
 *
 * @param turn_on a boolean value indicating whether the led should be turn on (`true`) or off (`false`)
 */
void set_right_led(bool turn_on) {
    if (turn_on) {
        cowpi_illuminate_right_led();
    } else {
        cowpi_deluminate_right_led();
    }
}

/**
 * @brief Scans the keypad to determine which, if any, key was pressed.
 *
 * Returns the hexadecimal numeric value of the key that was pressed.
 * The values 0x0-0xD are obtained from the keys with those hex digits.
 * The value 0xE is obtained from the '#' key,
 * and 0xF is obtained from the '*' key.
 *
 * @return hexadecimal value of the pressed key, or 0xFF if no key is pressed
 */
uint8_t get_keypress(void) {
    int8_t row, column;
    char key = cowpi_get_keypress();
    switch (key) {
        case '1':
        case '2':
        case '3':
        case 'A':
            row = 0;
            break;
        case '4':
        case '5':
        case '6':
        case 'B':
            row = 1;
            break;
        case '7':
        case '8':
        case '9':
        case 'C':
            row = 2;
            break;
        case '*':
        case '#':
        case '0':
        case 'D':
            row = 3;
            break;
        default:
            row = -1;
    }
    switch (key) {
        case '1':
        case '4':
        case '7':
        case '*':
            column = 0;
            break;
        case '2':
        case '5':
        case '8':
        case '0':
            column = 1;
            break;
        case '3':
        case '6':
        case '9':
        case '#':
            column = 2;
            break;
        case 'A':
        case 'B':
        case 'C':
        case 'D':
            column = 3;
            break;
        default:
            column = -1;
    }
    if (row == -1 || column == -1) {
        return cowpi_debounce_byte(0xFF, KEYPAD);
    } else {
        return cowpi_debounce_byte(keys[row][column], KEYPAD);
    }
}


/*********************/
/***** TEST CODE *****/
/*********************/


/**
 * @brief Code to test the I/O functions.
 *
 * Prints, on both the serial terminal and on the LCD1602, the position of
 * the buttons and switches, and any key that is pressed. If both switches
 * are pressed, then the left LED illuminates; if both switches are to the
 * right, then the right LED illuminates.
 *
 * *** *** !!! DO NOT EDIT THIS FUNCTION !!! *** ***
 */
void test_io(void) {
    // These variables preserve their values between calls to `test_io()`
    static bool left_button_position = true;
    static bool right_button_position = true;
    static bool left_switch_position = true;
    static bool right_switch_position = true;
    static uint8_t key_pressed = 0xFF;
    // This variable does not
    bool change_is_present = false;

    // Poll the inputs
    if (left_button_is_pressed() != left_button_position) {
        left_button_position = !left_button_position;
        change_is_present = true;
    }
    if (right_button_is_pressed() != right_button_position) {
        right_button_position = !right_button_position;
        change_is_present = true;
    }
    if (left_switch_is_in_right_position() != left_switch_position) {
        left_switch_position = !left_switch_position;
        change_is_present = true;
    }
    if (right_switch_is_in_right_position() != right_switch_position) {
        right_switch_position = !right_switch_position;
        change_is_present = true;
    }
    uint8_t this_key;
    if (show_key_press) {
        if ((this_key = (key_is_pressed() ? 'Y' : 'N')) != key_pressed) {
            key_pressed = this_key;
            change_is_present = true;
        }
    } else {
        if ((this_key = get_keypress()) != key_pressed) {
            key_pressed = this_key;
            change_is_present = true;
        }
    }

    // Show what we found
    if (change_is_present) {
        char output[17];
        set_left_led(left_button_position && right_button_position);
        set_right_led(left_switch_position && right_switch_position);

        if (show_key_press) {
            uint32_t microseconds = get_microseconds();
            uint32_t seconds = microseconds / 1000000;
            uint32_t fraction = microseconds - (seconds * 1000000);
            sprintf(output, "KEYPRESS    TIME");
            display_string(0, output);
            if (key_pressed == 'Y' || key_pressed == 'N') {
                sprintf(output, "%3s%5lu.%06lus",
                        key_pressed == 'Y' ? "YES" : "NO", seconds, fraction);
            } else {
                sprintf(output, "%3s%5lu.%06lus",
                        "ERR", seconds, fraction);
            }
            display_string(1, output);
        } else {
            sprintf(output, "KEY   BTN   SW");
            display_string(0, output);
            if (key_pressed <= 0x0F) {
                sprintf(output, "%2X%5c%2c%4c%2c",
                        key_pressed,
                        left_button_position ? 'D' : 'U', right_button_position ? 'D' : 'U',
                        left_switch_position ? 'R' : 'L', right_switch_position ? 'R' : 'L');
            }  else {
                sprintf(output, "%2c%5c%2c%4c%2c",
                        key_pressed == 0xFF ? '-' : '?',
                        left_button_position ? 'D' : 'U', right_button_position ? 'D' : 'U',
                        left_switch_position ? 'R' : 'L', right_switch_position ? 'R' : 'L');
            }
            display_string(1, output);
        }
    }
}