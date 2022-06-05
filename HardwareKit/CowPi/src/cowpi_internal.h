/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */


#ifndef COWPI_INTERNAL_H
#define COWPI_INTERNAL_H

#include <stdio.h>


/* Global variable declarations */

// none


/* Internal-facing function prototypes */

#ifdef __cplusplus
extern "C" {
#endif
void cowpi_lcd1602_set_4bit_mode(unsigned int configuration);
bool cowpi_is_spi_lsbfirst();
void cowpi_error(const char *message);
#ifdef __cplusplus
} // extern "C"
#endif


/* Macros for internal use only */

// none


#endif //COWPI_INTERNAL_H
