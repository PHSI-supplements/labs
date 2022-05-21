/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */


#ifndef COWPI_INTERNAL_H
#define COWPI_INTERNAL_H


/* Global variable declarations */

extern bool cowpi_lcd1602_adafruit;


/* Internal-facing function prototypes */

#ifdef __cplusplus
extern "C" {
#endif
void cowpi_lcd1602_spi_4bit_mode();
#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_INTERNAL_H
