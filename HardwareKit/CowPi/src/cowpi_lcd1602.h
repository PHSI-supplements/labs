/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

/******************************************************************************
 * Utility functions for 2x16 LCD display.
 ******************************************************************************/

#ifndef COWPI_LCD1602_H
#define COWPI_LCD1602_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
void cowpi_lcd1602_spi_place_character(uint8_t address, uint8_t data);
void cowpi_lcd1602_spi_send_command(uint8_t command);
void cowpi_lcd1602_spi_send_character(uint8_t data);
void cowpi_lcd1602_clear_display();
#ifdef __cplusplus
} // extern "C"
#endif


#endif //COWPI_LCD1602_H
