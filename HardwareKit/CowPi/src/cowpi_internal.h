/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */


#ifndef COWPI_INTERNAL_H
#define COWPI_INTERNAL_H

#include <stdio.h>


/* Constants */

    // buttons
static const uint8_t PUSHBUTTON_NAND        = 2;
static const uint8_t LEFT_BUTTON            = 8;
static const uint8_t RIGHT_BUTTON           = 9;
    // switches
#ifdef ARDUINO_AVR_MEGA2560
static const uint8_t LEFT_SWITCH_DEFAULT    = 58;   // aka A4
static const uint8_t RIGHT_SWITCH_DEFAULT   = 59;   // aka A5
#else
static const uint8_t LEFT_SWITCH_DEFAULT    = 18;   // aka A4
static const uint8_t RIGHT_SWITCH_DEFAULT   = 19;   // aka A5
#endif //ARDUINO_AVR_MEGA2560
static const uint8_t LEFT_SWITCH_ALTERNATE  = 11;
static const uint8_t RIGHT_SWITCH_ALTERNATE = 10;
    // keypad
static const uint8_t KEYPAD_NAND            = 3;
static const uint8_t KEYPAD_ROW_1           = 4;
static const uint8_t KEYPAD_ROW_4           = 5;
static const uint8_t KEYPAD_ROW_7           = 6;
static const uint8_t KEYPAD_ROW_STAR        = 7;
#ifdef ARDUINO_AVR_MEGA2560
static const uint8_t KEYPAD_COLUMN_1        = 54;   // aka A0
static const uint8_t KEYPAD_COLUMN_2        = 55;   // aka A1
static const uint8_t KEYPAD_COLUMN_3        = 56;   // aka A2
static const uint8_t KEYPAD_COLUMN_A        = 57;   // aka A3
#else
static const uint8_t KEYPAD_COLUMN_1        = 14;   // aka A0
static const uint8_t KEYPAD_COLUMN_2        = 15;   // aka A1
static const uint8_t KEYPAD_COLUMN_3        = 16;   // aka A2
static const uint8_t KEYPAD_COLUMN_A        = 17;   // aka A3
#endif //ARDUINO_AVR_MEGA2560
    // LEDs
static const uint8_t LED_EXTERNAL           = 12;
// Arduino Defined   LED_BUILTIN            = 13
    // SPI
static const uint8_t SPI_CHIP_SELECT        = 10;
// Arduino Defined   MOSI                   = 11                (D51 on Arduino Mega 2560)
// Arduino Defined   SCK                    = 13                (D52 on Arduino Mega 2560)
    // I2C
// Arduino Defined   SDA                    = 18       aka A4   (D20 on Arduino Mega 2560)
// Arduino Defined   SCL                    = 19       aka A5   (D21 on Arduino Mega 2560)


/* Global variable declarations */

// none


/* Internal-facing function prototypes */

#ifdef __cplusplus
extern "C" {
#endif
void cowpi_lcd1602_set_4bit_mode(unsigned int configuration);
bool cowpi_is_spi_lsbfirst();
void cowpi_error(const char *message);
#ifdef __cplusplus
} // extern "C"
#endif


/* Macros for internal use only */

// none


#endif //COWPI_INTERNAL_H
