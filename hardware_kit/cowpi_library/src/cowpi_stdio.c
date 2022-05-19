/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

#include <stdio.h>
#include "cowpi.h"

static FILE serial_monitor;

void cowpi_stdio_setup(unsigned long baud) {
    fdev_setup_stream(serial_monitor, cowpi_putc, cowpi_getc, _FDEV_SETUP_RW);
    stdin = &serial_monitor;
    stdout = &serial_monitor;
}

char cowpi_getc(FILE *stream) {
    while(!Serial.available()) {};
    return Serial.read();
}

void cowpi_putc(char c, FILE *stream) {
    Serial.write(c);
}