/**************************************************************************//**
 *
 * @file number_builder.ino
 *
 * @author (STUDENT -- TYPE YOUR NAME HERE)
 *
 * @brief Code to demonstrate "building" a number by polling inputs,
 *        and to demonstrate memory-mapped input/output.
 *
 ******************************************************************************/

/*
 * PollingLab assignment and starter code (c) 2021-22 Christopher A. Bohn
 * PollingLab solution (c) the above-named student
 */

#include "CowPi.h"
#include "io_functions.h"

#define BUTTON_NO_REPEAT_TIME 500u
#define ILLUMINATION_TIME 500u
#define NUMBER_ECHO_TIME 1000u

void build_number(void);

void setup() {
  cowpi_stdio_setup(9600);
  cowpi_set_display_i2c_address(0x27);
  cowpi_setup(LCD1602 | I2C);
  cowpi_lcd1602_set_backlight(true);
  initialize_io();
}

void loop() {
  test_io();
  // build_number();
}



/*******************************/
/***** NUMBER BUILDER CODE *****/
/*******************************/



void build_number(void) {
  ;
}



/********************/
/***** I/O CODE *****/
/********************/



// Layout of Matrix Keypad
//        1 2 3 A
//        4 5 6 B
//        7 8 9 C
//        * 0 # D
// This array holds the values we want each keypad button to correspond to
const uint8_t keys[4][4] = {
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
  // ioports = (cowpi_ioport_t *)(cowpi_io_base + 0);
  // i2c = (cowpi_i2c_t *)(cowpi_io_base + 0);
  // cowpi_lcd1602_set_send_halfbyte_function(send_halfbyte);
}

/**
 * @brief Reports whether the left button is pressed.
 *
 * A pressed button grounds a pulled-high input.
 *
 * @return `true` if the button is pressed, `false` otherwise
 */
bool left_button_is_pressed(void) {
  return cowpi_left_button_is_pressed();
}

/**
 * @brief Reports whether the right button is pressed.
 *
 * A pressed button grounds a pulled-high input.
 *
 * @return `true` if the button is pressed, `false` otherwise
 */
bool right_button_is_pressed(void) {
  return cowpi_right_button_is_pressed();
}

/**
 * @brief Reports whether the left switch is in the left position.
 *
 * A switch in the left position grounds a pulled-high input.
 *
 * @return `true` if the switch is in the left position, `false` otherwise
 */
bool left_switch_in_left_position(void) {
  return cowpi_left_switch_in_left_position();
}

/**
 * @brief Reports whether the left switch is in the right position.
 *
 * A switch in the right position floats, allowing pulled-high input to remain high.
 *
 * @return `true` if the switch is in the right position, `false` otherwise
 */
bool left_switch_in_right_position(void) {
  return cowpi_left_switch_in_right_position();
}

/**
 * @brief Reports whether the right switch is in the left position.
 *
 * A switch in the left position grounds a pulled-high input.
 *
 * @return `true` if the switch is in the left position, `false` otherwise
 */
bool right_switch_in_left_position(void) {
  return cowpi_right_switch_in_left_position();
}

/**
 * @brief Reports whether the right switch is in the right position.
 *
 * A switch in the right position floats, allowing pulled-high input to remain high.
 *
 * @return `true` if the switch is in the right position, `false` otherwise
 */
bool right_switch_in_right_position(void) {
  return cowpi_right_switch_in_right_position();
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
  static unsigned long last_keypress = 0uL;
  static uint8_t key_pressed = 0xFF;
  unsigned long now = millis();
  if (now - last_keypress > DEBOUNCE_TIME) {
    last_keypress = now;
    char key = cowpi_get_keypress();
    switch (key) {
      case '1':
        key_pressed = keys[0][0];
      case '2':
        key_pressed = keys[0][1];
      case '3':
        key_pressed = keys[0][2];
      case 'A':
        key_pressed = keys[0][3];
      case '4':
        key_pressed = keys[1][0];
      case '5':
        key_pressed = keys[1][1];
      case '6':
        key_pressed = keys[1][2];
      case 'B':
        key_pressed = keys[1][3];
      case '7':
        key_pressed = keys[2][0];
      case '8':
        key_pressed = keys[2][1];
      case '9':
        key_pressed = keys[2][2];
      case 'C':
        key_pressed = keys[2][3];
      case '*':
        key_pressed = keys[3][0];
      case '0':
        key_pressed = keys[3][1];
      case '#':
        key_pressed = keys[3][2];
      case 'D':
        key_pressed = keys[3][3];
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
  ;
}



/*********************/
/***** TEST CODE *****/
/*********************/



const char test_io_header[] = "KEY   BTN   SW";

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
  static unsigned long last_left_button_change = 0uL;
  static unsigned long last_right_button_change = 0uL;
  static unsigned long last_left_switch_change = 0uL;
  static unsigned long last_right_switch_change = 0uL;
  static unsigned long last_keypress = 0uL;
  // These variables do not
  bool change_is_present = false;
  unsigned long now = millis();
  // Poll the inputs
  if ((now - last_left_button_change > BUTTON_NO_REPEAT_TIME) &&
      (left_button_is_pressed() != left_button_position)) {
    last_left_button_change = now;
    left_button_position = !left_button_position;
    change_is_present = true;
  }
  if ((now - last_right_button_change > BUTTON_NO_REPEAT_TIME) &&
      (right_button_is_pressed() != right_button_position)) {
    last_right_button_change = now;
    right_button_position = !right_button_position;
    change_is_present = true;
  }
  if ((now - last_left_switch_change > DEBOUNCE_TIME) &&
      (left_switch_in_right_position() != left_switch_position)) {
    last_left_switch_change = now;
    left_switch_position = !left_switch_position;
    change_is_present = true;
  }
  if ((now - last_right_switch_change > DEBOUNCE_TIME) &&
      (right_switch_in_right_position() != right_switch_position)) {
    last_right_switch_change = now;
    right_switch_position = !right_switch_position;
    change_is_present = true;
  }
  uint8_t this_key;
  if ((now - last_keypress > BUTTON_NO_REPEAT_TIME) && 
      ((this_key = get_keypress()) != key_pressed)) {
    last_keypress = now;
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
    printf("%s\n", test_io_header);
    printf(" %c    %c %c   %c %c\n\n", 
            key_character, 
            left_button_position ? 'D' : 'U', right_button_position ? 'D' : 'U', 
            left_switch_position ? 'R' : 'L', right_switch_position ? 'R' : 'L');
    cowpi_lcd1602_return_home();
    const char *c = test_io_header;
    while (*c != '\0') {
      cowpi_lcd1602_send_character(*c++);
    }
    cowpi_lcd1602_place_character(0x41, key_character);
    cowpi_lcd1602_place_character(0x46, left_button_position ? 'D' : 'U');
    cowpi_lcd1602_place_character(0x48, right_button_position ? 'D' : 'U');
    cowpi_lcd1602_place_character(0x4C, left_switch_position ? 'R' : 'L');
    cowpi_lcd1602_place_character(0x4E, right_switch_position ? 'R' : 'L');
  }
}
