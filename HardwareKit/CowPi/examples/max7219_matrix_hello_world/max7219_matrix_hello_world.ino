#include "CowPi.h"
#include "cowpi_font_dotmatrix.h"

void setup() {
    cowpi_setup(MAX7219 | SPI);
}

void loop() {
    static uint8_t hello_world[14 * 6];
    static int length = cowpi_string_to_horizontal_dotmatrix(hello_world, "Hello, world! ", true);
    static uint8_t matrix[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    static int column = 0;
    for (int i = 0; i < 8; i++) {
        matrix[i] <<= 1;
        matrix[i] |= (hello_world[column] >> i) & 0x1;
        cowpi_max7219_send(i + 1, matrix[i]);
    }
    column++;
    if (column == length) {
        column = 0;
    }
    delay(100);
}