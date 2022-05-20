/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

//#include <stdio.h>    // Arduino.h brings this in
#include "cowpi.h"

static FILE *serial_monitor;

static int cowpi_getc(FILE *stream);
static int cowpi_putc(char c, FILE *stream);

void cowpi_stdio_setup(unsigned long baud) {
    Serial.begin(baud);
    fdev_setup_stream(serial_monitor, cowpi_putc, cowpi_getc, _FDEV_SETUP_RW);
    stdin = serial_monitor;
    stdout = serial_monitor;
}

static int cowpi_getc(FILE *stream) {
    while(!Serial.available()) {}
    return Serial.read();
}

static int cowpi_putc(char c, FILE *stream) {
    Serial.write(c);
    return c;
}