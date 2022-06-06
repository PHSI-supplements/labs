#include "cowpi.h"

const uint8_t H[]       = {0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00};
const uint8_t e[]       = {0x00, 0x00, 0x0E, 0x11, 0x1F, 0x10, 0x0E, 0x00};
const uint8_t l[]       = {0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x07, 0x00};
const uint8_t o[]       = {0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00};
const uint8_t comma[]   = {0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x02};
const uint8_t space[]   = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t w[]       = {0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0A, 0x00};
const uint8_t r[]       = {0x00, 0x00, 0x16, 0x19, 0x10, 0x10, 0x10, 0x00};
const uint8_t d[]       = {0x01, 0x01, 0x0D, 0x13, 0x11, 0x11, 0x0F, 0x00};
const uint8_t bang[]    = {0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00};

const uint8_t *hello_world[]  = {H, e, l, l, o, comma, space, w, o, r, l, d, bang, space};
const int8_t widths[]         = {5, 5, 3, 3, 5, 2, 2, 5, 5, 5, 3, 5, 1, 4};
const int8_t length = 14;

void setup() {
    cowpi_setup(MAX7219 | SPI);
}

void loop() {
    static int8_t letter = 0;
    static uint8_t matrix[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int column = 0; column < widths[letter]; column++) {
        for (int row = 0; row < 8; row++) {
            matrix[row] <<= 1;
            matrix[row] |= (hello_world[letter][row] >> (widths[letter] - column - 1)) & 0x1;
            cowpi_max7219_send(row + 1, matrix[row]);
        }
        delay(100);
    }
    for (int row = 0; row < 8; row++) {
        matrix[row] <<= 1;
        cowpi_max7219_send(row + 1, matrix[row]);
    }
    delay(100);
    letter++;
    if (letter == length) {
        letter = 0;
    }
}