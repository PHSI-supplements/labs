/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

/******************************************************************************
 * This header defines dummy functions & macros to replace those in
 * avr/pgmspace.h for non-AVR architectures (or that don't need avr/pgmspace.h,
 * in the case of the ATMega4809).
 ******************************************************************************/

#ifndef COWPI_DUMMY_PGMSPACE_H
#define COWPI_DUMMY_PGMSPACE_H

// One last protection against accidental misuse
#ifndef ARDUINO_ARCH_AVR

#ifdef __cplusplus
extern "C" {
#endif

#define PROGMEM

__attribute__((__always_inline__)) static __inline__ char *strcpy_P(const char *destination, char *source);
static __inline__ char *strcpy_P(const char *destination, char *source) {
    return source;
}

__attribute__((__always_inline__)) static __inline__ const char *PSTR(const char *s);
static __inline__ const char *PSTR(const char *s) {
    return s;
}

#ifdef __cplusplus
}
#endif

#endif //GUARD

#endif //COWPI_DUMMY_PGMSPACE_H
