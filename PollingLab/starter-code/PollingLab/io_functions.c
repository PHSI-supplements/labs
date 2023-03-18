/**************************************************************************//**
 *
 * @file io_functions.c
 *
 * @author (STUDENT -- TYPE YOUR NAME HERE)
 *
 * @brief Functions that students must re-implement using memory-mapped I/O.
 *
 ******************************************************************************/

/*
 * PollingLab (c) 2021-23 Christopher A. Bohn
 * Pollinglab solution (c) the above-named student
 *
 * Assignment and starter code licensed under the Apache License,
 * Version 2.0 (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include <CowPi.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "io_functions.h"
#include "i2c_address.h"
#include "supplement.h"


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

volatile cowpi_ioport_t *ioports;   // an array of I/O ports
volatile cowpi_i2c_t *i2c;          // a pointer to the single set of I2C registers

/**
 * @brief Assigns I/O register addresses to pointers and instructs CowPi library to use `send_halfbyte()`.
 */
void initialize_io(void) {
  // Uncomment these lines and set the offsets during lab time
  // ioports = (cowpi_ioport_t *)(COWPI_IO_BASE + 0);
  // i2c = (cowpi_i2c_t *)(COWPI_IO_BASE + 0);

  // Uncomment this line when you are ready to implement the `send_halfbyte()` function
  // cowpi_lcd1602_set_send_halfbyte_function(send_halfbyte);
}

/**
 * @brief Detects whether a key -- *any* key -- on the numeric keypad is being pressed.
 *
 * If no key is being pressed, then all column inputs will be high, and the Keypad NAND will be low.
 * On the other hand, if a key is being pressed, then one of the column inputs will be low, 
 * and the Keypad NAND will be high.
 *
 * @return `true` if a key is pressed, `false` otherwise
 */
bool key_movement_detected(void) {
  static bool key_was_pressed = false;
  bool key_is_pressed = debounce_byte(digitalRead(3), KEYPAD);
  bool change_detected = (key_is_pressed != key_was_pressed);
  key_was_pressed = key_is_pressed;
  return change_detected;
}


/******************************************/
/***** I/O CODE COMPLETED ON YOUR OWN *****/
/******************************************/


/**
 * @brief Reports whether the left button is pressed.
 *
 * A pressed button grounds a pulled-high input.
 *
 * @return `true` if the button is pressed, `false` otherwise
 */
bool left_button_is_pressed(void) {
  bool button_is_pressed;
  button_is_pressed = cowpi_left_button_is_pressed();
  return debounce_byte(button_is_pressed, LEFT_BUTTON);
}

/**
 * @brief Reports whether the right button is pressed.
 *
 * A pressed button grounds a pulled-high input.
 *
 * @return `true` if the button is pressed, `false` otherwise
 */
bool right_button_is_pressed(void) {
  bool button_is_pressed;
  button_is_pressed = cowpi_right_button_is_pressed();
  return debounce_byte(button_is_pressed, RIGHT_BUTTON);
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
  bool switch_in_position;
  switch_in_position = cowpi_left_switch_is_in_right_position();
  return debounce_byte(switch_in_position, LEFT_SWITCH);
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
  bool switch_in_position;
  switch_in_position = cowpi_right_switch_is_in_right_position();
  return debounce_byte(switch_in_position, RIGHT_SWITCH);
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
  static uint8_t key_pressed = 0xFF;
  if (key_movement_detected()) {
    char key = cowpi_get_keypress();
    switch (key) {
      case '1':
        key_pressed = keys[0][0];
        break;
      case '2':
        key_pressed = keys[0][1];
        break;
      case '3':
        key_pressed = keys[0][2];
        break;
      case 'A':
        key_pressed = keys[0][3];
        break;
      case '4':
        key_pressed = keys[1][0];
        break;
      case '5':
        key_pressed = keys[1][1];
        break;
      case '6':
        key_pressed = keys[1][2];
        break;
      case 'B':
        key_pressed = keys[1][3];
        break;
      case '7':
        key_pressed = keys[2][0];
        break;
      case '8':
        key_pressed = keys[2][1];
        break;
      case '9':
        key_pressed = keys[2][2];
        break;
      case 'C':
        key_pressed = keys[2][3];
        break;
      case '*':
        key_pressed = keys[3][0];
        break;
      case '0':
        key_pressed = keys[3][1];
        break;
      case '#':
        key_pressed = keys[3][2];
        break;
      case 'D':
        key_pressed = keys[3][3];
        break;
      default:
        key_pressed = 0xFF;
    }
  }
  return key_pressed;
}

/**
 * @brief Sends a halfbyte to the LCD1602 display.
 *
 * The `cowpi_lcd1602` utility functions all make use of the
 * `cowpi_lcd1602_send_halfbyte()` function pointer.
 * Initially, `cowpi_lcd1602_send_halfbyte()` is one of two default
 * implementations.
 *
 * After implementing the `send_halfbyte()` function, re-assign the
 * `cowpi_lcd1602_send_halfbyte()` function pointer by calling:
 * ```
 * cowpi_lcd1602_set_send_halfbyte_function(send_halfbyte);
 * ```
 *
 * @param halfbyte the data to be sent to the display module
 * @param is_command indicates whether the data is part of a command (`true`)
 *      or part of a character (`false`)
 */
void send_halfbyte(uint8_t halfbyte, bool is_command) {
  const uint8_t peripheral_address = I2C_ADDRESS;
  // ...
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
  if ((this_key = get_keypress()) != key_pressed) {
    key_pressed = this_key;
    change_is_present = true;
  }
  
  // Show what we found
  if (change_is_present) {
    char key_character;
    if (key_pressed <= 9) {
      key_character = key_pressed + '0';
    } else if (0xA <= key_pressed && key_pressed <= 0xF) {
      key_character = key_pressed - 0xA + 'A';
    } else if (key_pressed == 0xFF) {
      key_character = '-';
    } else {
      key_character = '?';
    }
    set_left_led(left_button_position && right_button_position);
    set_right_led(left_switch_position && right_switch_position);

    static const char test_io_header[] = "KEY   BTN   SW  ";
    char test_io_data[17];

    // We can use sprintf to create the string
    sprintf(test_io_data, " %c    %c %c   %c %c ", 
              key_character, 
              left_button_position ? 'D' : 'U', right_button_position ? 'D' : 'U', 
              left_switch_position ? 'R' : 'L', right_switch_position ? 'R' : 'L');

    // Or we can directly edit the string
    /*
    test_io_data[1]  = key_character;
    test_io_data[6]  = left_button_position  ? 'D' : 'U';
    test_io_data[8]  = right_button_position ? 'D' : 'U';
    test_io_data[12] = left_switch_position  ? 'R' : 'L';
    test_io_data[14] = right_switch_position ? 'R' : 'L';
    test_io_data[16] = '\0';
    */

    // Then we send the string to the console and the display module
    printf("%s\n", test_io_header);
    printf("%s\n\n", test_io_data);
    display_string(test_io_header, TOP_ROW);
    display_string(test_io_data, BOTTOM_ROW);
  }
}
