/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

/******************************************************************************
 * Utility functions for peripherals driven by MAX7219.
 ******************************************************************************/

#ifndef COWPI_MAX7219_H
#define COWPI_MAX7219_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
void cowpi_max7219_send(uint8_t address, uint8_t data);
void cowpi_max7219_shutdown();
void cowpi_max7219_startup();
void cowpi_max7219_no_decode();
void cowpi_max7219_bcd_decode();
void cowpi_max7219_set_intensity(uint8_t intensity);
#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_MAX7219_H
