#include "cowpi.h"

const uint8_t H     = 0x37;
const uint8_t E     = 0x4F;
const uint8_t L     = 0x0E;
const uint8_t O     = 0x1D;
const uint8_t space = 0x00;
const uint8_t W     = 0x3F;
const uint8_t R     = 0x05;
const uint8_t D     = 0x3D;
const uint8_t bang  = 0xA0;

const uint8_t hello_world[] = {H, E, L, L, O, space, W, O, R, L, D, bang, space, space};
const int8_t length = 14;

void setup() {
    cowpi_setup(MAX7219 | SPI);
}

void loop() {
    static int8_t letter = 0;
    static uint8_t letters[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int i = 7; i > 0; i--) {
        letters[i] = letters[i - 1];
        cowpi_max7219_send(i + 1, letters[i]);
    }
    letters[0] = hello_world[letter++];
    cowpi_max7219_send(1, letters[0]);
    if (letter == length) {
        letter = 0;
    }
    delay(150);
}
