/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

/******************************************************************************
 * Utility functions for 2x16 LCD display.
 ******************************************************************************/

#include <Arduino.h>
#include "cowpi.h"
#include "cowpi_lcd1602.h"
#include "cowpi_internal.h"


/* we'll need these when we incorporate backlight control */
static uint8_t last_command;
static bool backlit;


static void (*cowpi_lcd1602_send_halfbyte)(uint8_t halfbyte, bool is_command);  // hmm... if we expose this then students could simply implement send_halfbyte() and assign the function pointer
static void cowpi_lcd1602_send_halfbyte_spi(uint8_t halfbyte, bool is_command);
static void cowpi_lcd1602_send_halfbyte_i2c(uint8_t halfbyte, bool is_command);


void cowpi_lcd1602_place_character(uint8_t address, uint8_t data) {
    cowpi_lcd1602_spi_place_cursor(address);
    cowpi_lcd1602_send_character(data);
}

void cowpi_lcd1602_spi_place_cursor(uint8_t address) {
    cowpi_lcd1602_send_command(address | 0x80);
}

void cowpi_lcd1602_send_command(uint8_t command) {
    cowpi_lcd1602_send_halfbyte((command >> 4) & 0xF, true);
    cowpi_lcd1602_send_halfbyte( command       & 0xF, true);
    delayMicroseconds(50);      // most commands require 37us-38us according to various datasheets
}

void cowpi_lcd1602_send_character(uint8_t data) {
    cowpi_lcd1602_send_halfbyte((data >> 4) & 0xF, false);
    cowpi_lcd1602_send_halfbyte( data       & 0xF, false);
}

void cowpi_lcd1602_clear_display() {
    cowpi_lcd1602_send_command(0x01);
    delayMicroseconds(5000);    // tom alby says 5ms; adafruit uses 2ms; HD44780U datasheet simply says that 0x20 is written to each position; SPLC780D datasheet says 1.52ms
}

void cowpi_lcd1602_return_home() {
    cowpi_lcd1602_send_command(0x10);
    delayMicroseconds(2000);    // tom alby is silent; adafruit uses 2ms; datasheets agree on 1.52ms
}

void cowpi_lcd1602_set_backlight(bool backlight_on) {
    ;   // not yet implemented; safe to ignore for now since some hardware configurations will ignore it always
}

void cowpi_lcd1602_spi_4bit_mode(unsigned int configuration) {
    if (configuration & SPI) {
        cowpi_lcd1602_send_halfbyte = cowpi_lcd1602_send_halfbyte_spi;
    } else if (configuration & I2C) {
        cowpi_lcd1602_send_halfbyte = cowpi_lcd1602_send_halfbyte_i2c;
    } else {
        cowpi_configuration_error;
    }
    /* If initial state is:     8-bit mode      4-bit mode interbyte    4-bit mode intrabyte
     *      then LCD sees...                                                                */
    cowpi_lcd1602_send_halfbyte(0x3, true);
    /*                                                                  0x3 finishes byte   */
    delayMicroseconds(5000);    // HD44780U datasheet says wait > 4.1ms -- worst case if display was intrabyte
    cowpi_lcd1602_send_halfbyte(0x3, true);
    /*                          0x33: 8-bit mode    0x33: 8-bit mode                        */
    delayMicroseconds(200);     // HD44780U datasheet says wait more than 100us
    cowpi_lcd1602_send_halfbyte(0x3, true);
    /*                          0x30: 8-bit mode    0x30: 8-bit mode    0x33: 8-bit mode    */
    cowpi_lcd1602_send_halfbyte(0x2, true);
    /*                          0x20: 4-bit mode    0x20: 4-bit mode    0x20: 4-bit mode    */
}

static void cowpi_lcd1602_send_halfbyte_spi(uint8_t halfbyte, bool is_command) {
    // we'll use the AdaFruit mapping
    uint8_t rs = is_command ? 0 : 1 << 6;
    uint8_t en = 1 << 5;
    uint8_t packet = rs | (halfbyte << 1);
    // place data on the line
    digitalWrite(10, LOW);
    shiftOut(MOSI, SCK, LSBFIRST, packet);
    digitalWrite(10, HIGH);
    // pulse
    delayMicroseconds(1); // lady ada's value -- tom alby doesn't have a delay here. Come to think of it, he doesn't send halfbyte then pulse. His comment: "there is a setup time for RS before the rising ede of EN which is easily met because RS is set before calling the function There is a setup time for the data before the falling edge of EN which is also met by setting up the data before the pulse
    digitalWrite(10, LOW);
    shiftOut(MOSI, SCK, LSBFIRST, packet | en);
    digitalWrite(10, HIGH);
//    delayMicroseconds(100); // lady ada notes that commands need > 37 us to settle -- 100us is overkill
                            // I took care of the 37-38us in send_command()
}

static void cowpi_lcd1602_send_halfbyte_i2c(uint8_t halfbyte, bool is_command) {
    // this mapping seems typical
    // except that we haven't implemented it yet
    cowpi_configuration_error;
}
