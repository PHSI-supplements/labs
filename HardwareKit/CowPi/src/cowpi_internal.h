/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */


#ifndef COWPI_INTERNAL_H
#define COWPI_INTERNAL_H


/* Global variable declarations */

extern bool cowpi_spi_lsbfirst;


/* Internal-facing function prototypes */

#ifdef __cplusplus
extern "C" {
#endif
void cowpi_lcd1602_set_4bit_mode(unsigned int configuration);
#ifdef __cplusplus
} // extern "C"
#endif


/* Macros for internal use only */

#define cowpi_configuration_error do {                                                      \
    digitalWrite(12, HIGH);                                                                 \
    digitalWrite(13, HIGH);                                                                 \
    /* if interrupts are disabled then both LEDs lit is the best warning we can give */     \
    delay(1);                                                                               \
    digitalWrite(12, HIGH);                                                                 \
    digitalWrite(13, LOW);                                                                  \
    delay(500);                                                                             \
    digitalWrite(12, LOW);                                                                  \
    digitalWrite(13, HIGH);                                                                 \
    delay(500);                                                                             \
} while (1)     /* yes, I meant to do an infinite loop */


#endif //COWPI_INTERNAL_H
