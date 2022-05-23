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
void cowpi_stdio_setup(unsigned long baud);
#ifdef __cplusplus
} // extern "C"
#endif


/* Use to create argument to cowpi_setup() */

#define SPI                     0x01u
#define I2C                     0x02u
#define IIC                     0x02u
#define TWI                     0x02u
#define MAX7219                 0x80u
#define LCD1602                 0x40u


#endif //COWPI_SETUP_H
