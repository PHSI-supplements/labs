/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

/******************************************************************************
 * Utility functions for 2x16 LCD display.
 ******************************************************************************/

#include <Arduino.h>
#include "cowpi_setup.h"
#include "cowpi_lcd1602.h"
#include "cowpi_internal.h"


/* we'll need these when we incorporate backlight control */
#define ENTRY_MODE_MARKER 0x4
static uint8_t last_entry_mode = ENTRY_MODE_MARKER;
static bool is_backlit = false;
static uint8_t i2c_address;


void (*cowpi_lcd1602_send_halfbyte)(uint8_t halfbyte, bool is_command) = NULL;


static void cowpi_lcd1602_send_halfbyte_spi(uint8_t halfbyte, bool is_command);
static void cowpi_lcd1602_send_halfbyte_i2c(uint8_t halfbyte, bool is_command);


void cowpi_initialize_i2c_lcd1602(uint8_t peripheral_address, void (*send_halfbyte_function)(uint8_t halfbyte, bool is_command)) {
    if ((peripheral_address < 8) || (peripheral_address > 127)) {
        cowpi_configuration_error;
    }
    i2c_address = peripheral_address;
    cowpi_lcd1602_send_halfbyte = send_halfbyte_function;
}

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
    if (command & ENTRY_MODE_MARKER) {
        last_entry_mode = command;
    }
    delayMicroseconds(50);      // most commands require 37us-38us according to various datasheets; the exceptions have their own functions
}

void cowpi_lcd1602_send_character(uint8_t data) {
    cowpi_lcd1602_send_halfbyte((data >> 4) & 0xF, false);
    cowpi_lcd1602_send_halfbyte( data       & 0xF, false);
    delayMicroseconds(50);      // HD44780U datasheet says 41us (37+4) needed until character is updated and ddram address is updated; SPLC780D simply says 38us
}

void cowpi_lcd1602_create_character(uint8_t encoding, uint8_t pixel_vector[8]) {
    uint8_t cgram_start = (encoding & 0x7) << 3;
    for (int row = 0; row < 8; row++) {
        cowpi_lcd1602_send_command((cgram_start + row) | 0x40);
        cowpi_lcd1602_send_character(pixel_vector[row]);
    }
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
    is_backlit = backlight_on;
    cowpi_lcd1602_send_command(last_entry_mode);
}

void cowpi_lcd1602_set_4bit_mode(unsigned int configuration) {
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
    /* LSB    QH  QG  QF  QE  QD  QC  QB  QA  MSB *
     * LSB  LITE  D4  D5  D6  D7  EN  RS  xx  MSB */
    uint8_t rs = is_command ? 0 : 1 << 6;
    uint8_t en = 1 << 5;
    uint8_t packet = rs | (halfbyte << 1) | (is_backlit ? 1 : 0);
    // place data on the line
    digitalWrite(10, LOW);
    shiftOut(MOSI, SCK, LSBFIRST, packet);
    digitalWrite(10, HIGH);
    // pulse
    digitalWrite(10, LOW);
    shiftOut(MOSI, SCK, LSBFIRST, packet | en);
    digitalWrite(10, HIGH);
    // Tom Alby uses NOPs to get to create an exact 0.5us pulse (6 NOPs (6 cycles) + 1 memory write (2 cycles) = 0.5us)
    // but that isn't portable (also: AVR docs say to use _delay_ms() or _delay_us(), which also aren't portable)
    delayMicroseconds(1);
    // I don't think we need to preserve the data, but no harm / no foul
    digitalWrite(10, LOW);
    shiftOut(MOSI, SCK, LSBFIRST, packet);
    digitalWrite(10, HIGH);
}

static void cowpi_lcd1602_send_halfbyte_i2c(uint8_t halfbyte, bool is_command) {
    // this mapping seems works with AdaFruit's I2C interfaces and with the EE Shop's cheaper I2C interface
    /* MSB   GP7 GP6 GP5 GP4 GP3 GP2 GP1 GP0  LSB *
     * MSB  LITE  D7  D6  D5  D4  EN  RS  xx  LSB */
//    cowpi_configuration_error;  // except that we haven't implemented it yet
    uint8_t mask;
    digitalWrite(SDA, HIGH);
    digitalWrite(SCL, HIGH);    // should already be HIGH, but let's go with it
    delayMicroseconds(10);      // just to be sure
    // Start
    digitalWrite(SDA, LOW);
    delayMicroseconds(5);      // various hold times all seem to be shorter than 5us
    digitalWrite(SCL, LOW);
    delayMicroseconds(10);
    // Place peripheral address on the line
    mask = 0x40;
    for (int i = 0; i < 7; i++) {
        digitalWrite(SDA, (i2c_address & mask) >> (7 - i));
        delayMicroseconds(5);
        digitalWrite(SCL, HIGH);
        delayMicroseconds(10);
        digitalWrite(SCL, LOW);
        delayMicroseconds(5);   // We're giving this the rough equivalent of a 50kHz clock
        mask >>= 1;
    }
    // R/W = write
    digitalWrite(SDA, LOW);
    delayMicroseconds(5);
    digitalWrite(SCL, HIGH);
    delayMicroseconds(10);
    digitalWrite(SCL, LOW);
    delayMicroseconds(5);
    // Take the line low, so we can listen for ACK (but we won't actually listen)
    digitalWrite(SDA, LOW);
    delayMicroseconds(5);
    digitalWrite(SCL, HIGH);
    delayMicroseconds(10);
    digitalWrite(SCL, LOW);
    delayMicroseconds(5);
    // Place data on the line
    mask = 0x80;
    for (int i = 0; i < 8; i++) {
        digitalWrite(SDA, (halfbyte & mask) >> (8 - i));
        delayMicroseconds(5);
        digitalWrite(SCL, HIGH);
        delayMicroseconds(10);
        digitalWrite(SCL, LOW);
        delayMicroseconds(5);
        mask >>= 1;
    }
    // Take the line low, so we can listen for ACK (but we won't actually listen)
    digitalWrite(SDA, LOW);
    delayMicroseconds(5);
    digitalWrite(SCL, HIGH);
    delayMicroseconds(10);
    digitalWrite(SCL, LOW);
    delayMicroseconds(5);
    // Stop (we probably should create a "send byte" function that has a Restart between the halfbytes)
    delayMicroseconds(5);
    digitalWrite(SCL, HIGH);
    delayMicroseconds(5);
    digitalWrite(SDA, HIGH);
}
