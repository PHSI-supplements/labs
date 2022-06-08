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
void cowpi_lcd1602_set_send_function(void (*send_halfbyte_function)(uint8_t halfbyte, bool is_command));
void cowpi_lcd1602_place_character(uint8_t address, uint8_t data);
void cowpi_lcd1602_place_cursor(uint8_t address);
void cowpi_lcd1602_send_command(uint8_t command);
void cowpi_lcd1602_send_character(uint8_t data);
void cowpi_lcd1602_create_character(uint8_t encoding, const uint8_t pixel_vector[8]);
void cowpi_lcd1602_clear_display();
void cowpi_lcd1602_return_home();
void cowpi_lcd1602_set_backlight(bool backlight_on);
#ifdef __cplusplus
} // extern "C"
#endif


/* Entry Mode Commands */
#define LCDENTRY_CURSORMOVESRIGHT   0x06
#define LCDENTRY_CURSORMOVESLEFT    0x04    /* default */
#define LCDENTRY_TEXTSHIFTS         0x05
#define LCDENTRY_TEXTNOSHIFT        0x04    /* default */

/* Display On/Off Commands */
#define LCDONOFF_DISPLAYON          0x0C
#define LCDONOFF_DISPLAYOFF         0x08    /* default */
#define LCDONOFF_CURSORON           0x0A
#define LCDONOFF_CURSOROFF          0x08    /* default */
#define LCDONOFF_BLINKON            0x09
#define LCDONOFF_BLINKOFF           0x08    /* default */

/* Cursor or Display Shift Commands */
#define LCDSHIFT_DISPLAYLEFT        0x18
#define LCDSHIFT_DISPLAYRIGHT       0x1C
#define LCDSHIFT_CURSORLEFT         0x10
#define LCDSHIFT_CURSORRIGHT        0x14


#endif //COWPI_LCD1602_H
