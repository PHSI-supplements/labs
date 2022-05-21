/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

/******************************************************************************
 * Utility functions for 2x16 LCD display.
 ******************************************************************************/

#include <Arduino.h>
#include "cowpi_lcd1602.h"
#include "cowpi_internal.h"


static void cowpi_lcd1602_spi_send_halfbyte(uint8_t halfbyte, bool is_command);


void cowpi_lcd1602_spi_place_character(uint8_t address, uint8_t data) {
    cowpi_lcd1602_spi_send_command(address | 0x80);
    cowpi_lcd1602_spi_send_character(data);
}

void cowpi_lcd1602_spi_send_command(uint8_t command) {
    cowpi_lcd1602_spi_send_halfbyte((command >> 4) & 0xF, true);
    cowpi_lcd1602_spi_send_halfbyte( command       & 0xF, true);
}

void cowpi_lcd1602_spi_send_character(uint8_t data) {
    cowpi_lcd1602_spi_send_halfbyte((data >> 4) & 0xF, false);
    cowpi_lcd1602_spi_send_halfbyte( data       & 0xF, false);
}

void cowpi_lcd1602_clear_display() {
    cowpi_lcd1602_spi_send_command(0x01);
    delayMicroseconds(5000);    // tom alby says 5ms; adafruit uses 2ms; datasheet doesn't indicate any
}

void cowpi_lcd1602_spi_4bit_mode() {
    /* If initial state is:     8-bit mode      4-bit mode interbyte    4-bit mode intrabyte
     *      then LCD sees...                                                                */
    cowpi_lcd1602_spi_send_halfbyte(0x3, true);
    /*                                                                  0x3 finishes byte   */
    delayMicroseconds(5000);    // HD44780U datasheet says wait more than 4.1ms
    cowpi_lcd1602_spi_send_halfbyte(0x3, true);
    /*                          0x33: 8-bit mode    0x33: 8-bit mode                        */
    delayMicroseconds(200);     // HD44780U datasheet says wait more than 100us
    cowpi_lcd1602_spi_send_halfbyte(0x3, true);
    /*                          0x30: 8-bit mode    0x30: 8-bit mode    0x33: 8-bit mode    */
    cowpi_lcd1602_spi_send_halfbyte(0x2, true);
    /*                          0x20: 4-bit mode    0x20: 4-bit mode    0x20: 4-bit mode    */
}

static void cowpi_lcd1602_spi_send_halfbyte(uint8_t halfbyte, bool is_command) {
    // for now, we'll use the AdaFruit mapping
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
    delayMicroseconds(100); // lady ada notes that commands need > 37 us to settle -- 100us is overkill
}
