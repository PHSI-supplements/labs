/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

/******************************************************************************
 * This header organizes the other headers.
 ******************************************************************************/

#ifndef COWPI_H
#define COWPI_H

#include <Arduino.h>
#include "cowpi_setup.h"
#include "cowpi_max7219.h"
#include "cowpi_lcd1602.h"

/* Public-facing function prototypes */

#ifdef __cplusplus
extern "C" {
#endif
char cowpi_get_keypress();
bool cowpi_left_button_is_pressed();
bool cowpi_right_button_is_pressed();
bool cowpi_left_switch_in_left_position();
bool cowpi_right_switch_in_left_position();
bool cowpi_left_switch_in_right_position();
bool cowpi_right_switch_in_right_position();
void cowpi_illuminate_external_led();
void cowpi_illuminate_internal_led();
void cowpi_deluminate_external_led();
void cowpi_deluminate_internal_led();
#ifdef __cplusplus
} // extern "C"
#endif


/* Board-specific definitions */

#if defined ARDUINO_AVR_UNO || defined ARDUINO_AVR_NANO
#include "cowpi_atmega328p.h"
#elif defined ARDUINO_AVR_NANO_EVERY
uint8_t * const cowpi_io_base = (uint8_t *)0x0;
#error Arduino Nano Every is not yet supported for CowPi
#elif defined ARDUINO_NANO33BLE
// TODO: double-check whether Nano 33 BLE Sense is a distinct board wrt IDE
#error Arduino Nano 33 BLE is not yet supported for CowPi
#elif defined ARDUINO_SAMD_NANO_33_IOT
#error Arduino Nano 33 IOT is not yet supported for CowPi
#elif defined ARDUINO_NANO_RP2040_CONNECT
#error Arduino Nano RP2040 is not yet supported for CowPi
#elif defined ARDUINO_AVR_MEGA2560
#error Arduino Mega 2560 is not yet supported for CowPi
#elif defined ARDUINO_RASPBERRY_PI_PICO
#error Raspberry Pi Pico Arduino core is not yet supported for CowPi
#else
#error Your microcontroller board is not yet supported for CowPi.
#endif //MICROCONTROLLER BOARD

#endif //COWPI_H
