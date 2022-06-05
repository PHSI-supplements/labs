/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

#ifndef COWPI_SETUP_H
#define COWPI_SETUP_H


/* Public-facing function prototypes */

#ifdef __cplusplus
extern "C" {
#endif
void cowpi_setup(unsigned int configuration);
void cowpi_set_display_dialect(unsigned int dialect);
unsigned int cowpi_get_display_dialect();
void cowpi_stdio_setup(unsigned long baud);
void cowpi_set_display_i2c_address(uint8_t peripheral_address);
uint8_t cowpi_get_display_i2c_address();
#ifdef __cplusplus
} // extern "C"
#endif


/* Use to create argument to cowpi_setup() */

#define SPI                     0x0001u
#define I2C                     0x0002u
#define IIC                     0x0002u
#define TWI                     0x0002u
#define MAX7219                 0x0080u
#define LCD1602                 0x0040u


/* Use as argument to cowpi_set_display_dialect() */

#define ADAFRUIT                0x8000u
#define WOKWI                   0x4000u


/* Masks to distinguish between configuration fields */

#define PROTOCOL_MASK           0x000Fu
#define DISPLAY_DEVICE_MASK     0x00F0u
#define DISPLAY_DIALECT_MASK    0xF000u


#endif //COWPI_SETUP_H
