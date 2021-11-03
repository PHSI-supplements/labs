#include "cowpi.h"

void setup_simple_io();
void setup_matrix_keypad();
void setup_display_module();
uint8_t get_key_pressed();
void display_data(uint8_t address, uint8_t value);

struct gpio_registers *gpio;
struct spi_registers *spi;
unsigned long last_left_button_press = 0;
unsigned long last_right_button_press = 0;
unsigned long last_left_switch_slide = 0;
unsigned long last_right_switch_slide = 0;
unsigned long last_keypad_press = 0;


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

// Seven Segment Display mapping between segments and bits
// Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
//  DP   A    B    C    D    E    F    G
// This array holds the bit patterns to display each hexadecimal numeral
const uint8_t seven_segments[16] = {
  
};

// #include "PollingLabTest.h"

void setup() {
  Serial.begin(9600);
  // gpio = ...
  // spi = ...
  setup_simple_io();
  setup_keypad();
  setup_display_module();
}

void loop() {
  test_simple_io();
  // if (...) {
  //   uint8_t keypress = get_key_pressed();
  //   if (keypress < 0x10) {
  //     Serial.print("Key pressed: ");
  //     Serial.println(keypress, HEX);
  //     // display_data(1, seven_segments[keypress]);
  //   } else {
  //     Serial.println("Error reading keypad.");
  //   }
  // }
}

void setup_simple_io() {
}

void setup_keypad() {
}

void setup_display_module() {
  // Set COPI, SCK, and CS to output
  // Enable SPI, Controller, set clock rate fck/16
  for (char i = 1; i <= 8; i++) {
    display_data(i, 0);     // clear all digit registers
  }
  display_data(0xA, 8);     // intensity at 17/32
  display_data(0xB, 7);     // scan all eight digits
  display_data(0xC, 1);     // take display out of shutdown mode
  display_data(0xF, 0);     // take display out of test mode, just in case
}

uint8_t get_key_pressed() {
  uint8_t key_pressed = 0xFF;
  unsigned long now = millis();
  if (now - last_keypad_press > 500) {
    last_keypad_press = now;
    // ...
  }
  return key_pressed;
}

void display_data(uint8_t address, uint8_t value) {
  // address is MAX7219's register address (1-8 for digits; otherwise see MAX7219 datasheet Table 2)
  // value is the bit pattern to place in the register
}

uint8_t left_switch_last_position = 0;
uint8_t right_switch_last_position = 0;

void test_simple_io() {
  uint8_t printed_this_time = 0;
  uint8_t left_switch_current_position = digitalRead(A4);
  uint8_t right_switch_current_position = digitalRead(A5);
  uint8_t left_button_current_position = digitalRead(8);
  uint8_t right_button_current_position = digitalRead(9);
  unsigned long now = millis();
  if ((left_switch_current_position != left_switch_last_position) && (now - last_left_switch_slide > 500)) {
    Serial.print(now);
    Serial.print("\tLeft switch changed: ");
    Serial.print(left_switch_current_position);
    left_switch_last_position = left_switch_current_position;
    printed_this_time = 1;
    last_left_switch_slide = now;
  }
  if ((right_switch_current_position != right_switch_last_position) && (now - last_right_switch_slide > 500)) {
    if (!printed_this_time) {
      Serial.print(now);
    }
    Serial.print("\tRight switch changed: ");
    Serial.print(right_switch_current_position);
    right_switch_last_position = right_switch_current_position;
    printed_this_time = 1;
    last_right_switch_slide = now;
  }
  if (!left_button_current_position && (now - last_left_button_press > 500)) {
    if (!printed_this_time) {
      Serial.print(now);
    }
    Serial.print("\tLeft button pressed");
    printed_this_time = 1;
    last_left_button_press = now;
  }
  if (!right_button_current_position && (now - last_right_button_press > 500)) {
    if (!printed_this_time) {
      Serial.print(now);
    }
    Serial.print("\tRight button pressed");
    printed_this_time = 1;
    last_right_button_press = now;
  }
  if(printed_this_time) {
    Serial.println();
  }
  digitalWrite(12, left_switch_current_position && right_switch_current_position);
}