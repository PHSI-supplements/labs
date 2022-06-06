/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

/******************************************************************************
 * Utility functions for peripherals driven by MAX7219.
 ******************************************************************************/

#include <Arduino.h>
#include "cowpi_max7219.h"
#include "cowpi_internal.h"


void cowpi_max7219_send(uint8_t address, uint8_t data) {
    digitalWrite(SPI_CHIP_SELECT, LOW);
    shiftOut(MOSI, SCK, MSBFIRST, address);
    shiftOut(MOSI, SCK, MSBFIRST, data);
    digitalWrite(SPI_CHIP_SELECT, HIGH);
}

void cowpi_max7219_no_decode() {
    cowpi_max7219_send(0x9, 0);
}

void cowpi_max7219_bcd_decode() {
    cowpi_max7219_send(0x9, 0xF);
}

void cowpi_max7219_set_intensity(uint8_t intensity) {
    cowpi_max7219_send(0xA, intensity & 0xF);
}

void cowpi_max7219_shutdown() {
    cowpi_max7219_send(0xC, 0);
}

void cowpi_max7219_startup() {
    cowpi_max7219_send(0xC, 1);
}
