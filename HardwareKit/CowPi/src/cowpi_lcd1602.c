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


#define ENTRY_MODE_MARKER 0x4
static uint8_t last_entry_mode = ENTRY_MODE_MARKER;
static bool is_backlit = false;


static void (*cowpi_lcd1602_send_halfbyte)(uint8_t halfbyte, bool is_command) = NULL;

static void cowpi_lcd1602_send_halfbyte_spi(uint8_t halfbyte, bool is_command);
static void cowpi_lcd1602_send_halfbyte_i2c(uint8_t halfbyte, bool is_command);


void cowpi_lcd1602_set_send_function(void (*send_halfbyte_function)(uint8_t halfbyte, bool is_command)) {
    cowpi_lcd1602_send_halfbyte = send_halfbyte_function;
}

void cowpi_lcd1602_place_character(uint8_t address, uint8_t data) {
    cowpi_lcd1602_place_cursor(address);
    cowpi_lcd1602_send_character(data);
}

void cowpi_lcd1602_place_cursor(uint8_t address) {
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
    cowpi_lcd1602_send_command(0x02);
    delayMicroseconds(2000);    // tom alby is silent; adafruit uses 2ms; datasheets agree on 1.52ms
}

void cowpi_lcd1602_set_backlight(bool backlight_on) {
    is_backlit = backlight_on;
    cowpi_lcd1602_send_command(last_entry_mode);
}

void cowpi_lcd1602_set_4bit_mode(unsigned int configuration) {
    uint8_t i2c_address = cowpi_get_display_i2c_address();
    if (!cowpi_lcd1602_send_halfbyte) {
        if (configuration & SPI) {
            cowpi_lcd1602_set_send_function(cowpi_lcd1602_send_halfbyte_spi);
        } else if (configuration & I2C) {
            if ((i2c_address < 8) || (i2c_address > 127)) {
                char s[61];
                cowpi_error(strcpy_P(s, PSTR("I2C Peripheral address must be between 8 and 127, inclusive.")));
            }
            cowpi_lcd1602_set_send_function(cowpi_lcd1602_send_halfbyte_i2c);
        } else {
            char s[115];
            cowpi_error(strcpy_P(s, PSTR("CowPi must use a serial protocol with LCD1602. "
                                         "Use `cowpi_setup(LCD1602 | SPI);` or `cowpi_setup(LCD1602 | I2C);`.")));
            // That may not always be the case -- for example, Arduino Mega 2560, Raspberry Pi, or Raspberry Pi Pico
        }
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
    delayMicroseconds(200);     // not in the datasheets, but we determined experimentally that 100us is needed
    cowpi_lcd1602_send_halfbyte(0x2, true);
    /*                          0x20: 4-bit mode    0x20: 4-bit mode    0x20: 4-bit mode    */
    delayMicroseconds(200);     // doesn't seem to be needed ¯\_(ツ)_/¯
}

static void cowpi_lcd1602_send_halfbyte_spi(uint8_t halfbyte, bool is_command) {
    // we'll use the AdaFruit mapping for its SPI+I2C interface -- probably will add other dialect(s) later
    /* LSB    QH  QG  QF  QE  QD  QC  QB  QA  MSB *
     * LSB  LITE  D4  D5  D6  D7  EN  RS  xx  MSB */
    uint8_t rs = is_command ? 0 : 1 << 6;
    uint8_t en = 1 << 5;
    uint8_t packet = rs | (halfbyte << 1) | (is_backlit ? 1 : 0);
    // place data on the line
    digitalWrite(SPI_CHIP_SELECT, LOW);
    shiftOut(MOSI, SCK, cowpi_is_spi_lsbfirst() ? LSBFIRST : MSBFIRST, packet);
    digitalWrite(SPI_CHIP_SELECT, HIGH);
    // pulse
    digitalWrite(SPI_CHIP_SELECT, LOW);
    shiftOut(MOSI, SCK, cowpi_is_spi_lsbfirst() ? LSBFIRST : MSBFIRST, packet | en);
    digitalWrite(SPI_CHIP_SELECT, HIGH);
    // Tom Alby uses NOPs to get to create an exact 0.5us pulse (6 NOPs (6 cycles) + 1 memory write (2 cycles) = 0.5us)
    // but that isn't portable (also: AVR docs say to use _delay_ms() or _delay_us(), which also aren't portable)
    // However, since we're only doing a half-byte at a time, function calls, etc., will provide sufficient delay
    delayMicroseconds(1);
    // end the pulse
    digitalWrite(SPI_CHIP_SELECT, LOW);
    shiftOut(MOSI, SCK, cowpi_is_spi_lsbfirst() ? LSBFIRST : MSBFIRST, packet);
    digitalWrite(SPI_CHIP_SELECT, HIGH);
}

static inline void shift_out(uint8_t data_pin, uint8_t clock_pin, uint8_t bit_order, uint8_t value, uint8_t us_hold) {
    // On a 16MHz ATMega328P, `shiftOut` should give us 77-91MHz clock, but in practice seems to be too fast for I2C
    // Might be even faster on Arduino Nano Every
    // Will definitely be too fast on Arduino's ARM microcontrollers
    for (int i = 0; i < 8; i++) {
        digitalWrite(data_pin, !!(value & (1 << (bit_order == LSBFIRST ? i : 7 - i))));
        delayMicroseconds(us_hold / 2);
        digitalWrite(clock_pin, HIGH);
        delayMicroseconds(us_hold);
        digitalWrite(clock_pin, LOW);
        delayMicroseconds(us_hold / 2);
    }
}

static inline uint8_t get_ack(uint8_t data_pin, uint8_t clock_pin, uint8_t us_hold) {
    // Take the line low, so we can listen for ACK (but we won't actually listen)
//    digitalWrite(SDA, LOW);
//    delayMicroseconds(5);
//    digitalWrite(SCL, HIGH);
//    delayMicroseconds(4);
//    digitalWrite(SCL, LOW);
    digitalWrite(SDA, LOW);
    pinMode(SDA, INPUT);
    delayMicroseconds(us_hold);
    digitalWrite(SCL, HIGH);
    delayMicroseconds(us_hold / 2);
    uint8_t nack = digitalRead(SDA);
    digitalWrite(SCL, LOW);
    delayMicroseconds(us_hold / 2);
    pinMode(SDA, OUTPUT);
    return !nack;
}

static void cowpi_lcd1602_send_halfbyte_i2c(uint8_t halfbyte, bool is_command) {
    uint8_t packet = 0, rs = 0, en = 0;
    unsigned int dialect = cowpi_get_display_dialect();
    if (dialect == STANDARD) {
        // this mapping is used with most I2C interfaces and libraries
        // https://github.com/johnrickman/LiquidCrystal_I2C
        // https://github.com/blackhack/LCD_I2C
        /* MSB  P7  P6  P5  P4  P3  P2  P1  P0  LSB *
         * MSB  D7  D6  D5  D4 LITE EN  RW  RS  LSB */
        rs = is_command ? 0 : 1;
        en = 1 << 2;
        packet = rs | (halfbyte << 4) | (is_backlit ? 1 << 3 : 0);
    } else if (dialect == ADAFRUIT) {
        // this mapping is used with AdaFruit's SPI+I2C interface
        // https://github.com/adafruit/Adafruit_LiquidCrystal
        /* MSB   GP7 GP6 GP5 GP4 GP3 GP2 GP1 GP0  LSB *
         * MSB  LITE  D7  D6  D5  D4  EN  RS  xx  LSB */
        rs = is_command ? 0 : 1 << 1;
        en = 1 << 2;
        packet = rs | (halfbyte << 3) | (is_backlit ? 1 << 7 : 0);
    } else {
        char s[73];
        cowpi_error(strcpy_P(s, PSTR("CowPi only knows STANDARD and ADAFRUIT dialects for I2C-to-LCD1602 mapping.")));
    }
    // start bit
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x08) printf("did not receive start!\n");
    // I2C address + /w
    TWDR = cowpi_get_display_i2c_address() << 1;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) != 0x18) printf("did not receive address!\n");
    // place data on the line
    TWDR = packet;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8)!= 0x28) printf("did not receive data!\n");
    // pulse
    TWDR = packet | en;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8)!= 0x28) printf("did not receive leading edge of the pulse!\n");
    delayMicroseconds(1);
    // end the pulse
    TWDR = packet;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8)!= 0x28) printf("did not receive the trailing edge of the pulse!\n");
    // stop bit
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
/*
    // start bit
    digitalWrite(SDA, HIGH);
    digitalWrite(SCL, HIGH);    // should already be HIGH, but let's go with it
    delayMicroseconds(15);       // just to be sure
    // Start
    digitalWrite(SDA, LOW);
    delayMicroseconds(15);       // various hold times all seem to be shorter than 5us
    digitalWrite(SCL, LOW);
    // I2C address + /w
    shift_out(SDA, SCL, MSBFIRST, cowpi_get_display_i2c_address() << 1, 14);
//    // Take the line low, so we can listen for ACK (but we won't actually listen)
//    digitalWrite(SDA, LOW);
//    delayMicroseconds(5);
//    digitalWrite(SCL, HIGH);
//    delayMicroseconds(4);
//    digitalWrite(SCL, LOW);
    if (!get_ack(SDA, SCL, 14)) printf("did not receive address!\n"); else printf("received address\n");
    // place data on the line
    shift_out(SDA, SCL, MSBFIRST, packet, 4);
    // Take the line low, so we can listen for ACK (but we won't actually listen)
    digitalWrite(SDA, LOW);
    delayMicroseconds(5);
    digitalWrite(SCL, HIGH);
    delayMicroseconds(4);
    digitalWrite(SCL, LOW);
    // pulse
    shift_out(SDA, SCL, MSBFIRST, packet | en, 4);
    // Take the line low, so we can listen for ACK (but we won't actually listen)
    digitalWrite(SDA, LOW);
    delayMicroseconds(5);
    digitalWrite(SCL, HIGH);
    delayMicroseconds(4);
    digitalWrite(SCL, LOW);
    delayMicroseconds(1);
    // end the pulse
    shift_out(SDA, SCL, MSBFIRST, packet, 4);
    // Take the line low, so we can listen for ACK (but we won't actually listen)
    digitalWrite(SDA, LOW);
    delayMicroseconds(5);
    digitalWrite(SCL, HIGH);
    delayMicroseconds(4);
    digitalWrite(SCL, LOW);
    delayMicroseconds(5);
    // stop bit
    digitalWrite(SCL, HIGH);
    delayMicroseconds(5);
    digitalWrite(SDA, HIGH);
*/
}
