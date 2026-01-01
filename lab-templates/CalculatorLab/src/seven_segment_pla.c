/**************************************************************************//**
 *
 * @file seven_segment_pla.c
 *
 * @author (TYPE YOUR NAME HERE)
 * @author (TYPE YOUR PARTNER'S NAME HERE, IF APPLICABLE)
 *
 * @brief Code to simulate a seven-segment decoder implemented with a PLA.
 *
 ******************************************************************************/

/*
 * CalculatorLab assignment and starter code (c) 2020-25 Christopher A. Bohn
 * CalculatorLab solution (c) the above-named student(s)
 */

#include <stdbool.h>
#include "display.h"
#include "seven_segment_pla.h"

typedef struct {
    uint8_t B0 : 1;
    uint8_t B1 : 1;
    uint8_t B2 : 1;
    uint8_t B3 : 1;
    uint8_t    : 4;
} nybble_t;

static bool get_segment_A(nybble_t digit) {
    __attribute__ ((unused)) bool B0 = digit.B0;
    __attribute__ ((unused)) bool B1 = digit.B1;
    __attribute__ ((unused)) bool B2 = digit.B2;
    __attribute__ ((unused)) bool B3 = digit.B3;
    return 0;
}

static bool get_segment_B(nybble_t digit) {
    __attribute__ ((unused)) bool B0 = digit.B0;
    __attribute__ ((unused)) bool B1 = digit.B1;
    __attribute__ ((unused)) bool B2 = digit.B2;
    __attribute__ ((unused)) bool B3 = digit.B3;
    return 0;
}

static bool get_segment_C(nybble_t digit) {
    __attribute__ ((unused)) bool B0 = digit.B0;
    __attribute__ ((unused)) bool B1 = digit.B1;
    __attribute__ ((unused)) bool B2 = digit.B2;
    __attribute__ ((unused)) bool B3 = digit.B3;
    return 0;
}

static bool get_segment_D(nybble_t digit) {
    __attribute__ ((unused)) bool B0 = digit.B0;
    __attribute__ ((unused)) bool B1 = digit.B1;
    __attribute__ ((unused)) bool B2 = digit.B2;
    __attribute__ ((unused)) bool B3 = digit.B3;
    return 0;
}

static bool get_segment_E(nybble_t digit) {
    __attribute__ ((unused)) bool B0 = digit.B0;
    __attribute__ ((unused)) bool B1 = digit.B1;
    __attribute__ ((unused)) bool B2 = digit.B2;
    __attribute__ ((unused)) bool B3 = digit.B3;
    return 0;
}

static bool get_segment_F(nybble_t digit) {
    __attribute__ ((unused)) bool B0 = digit.B0;
    __attribute__ ((unused)) bool B1 = digit.B1;
    __attribute__ ((unused)) bool B2 = digit.B2;
    __attribute__ ((unused)) bool B3 = digit.B3;
    return 0;
}

static bool get_segment_G(nybble_t digit) {
    __attribute__ ((unused)) bool B0 = digit.B0;
    __attribute__ ((unused)) bool B1 = digit.B1;
    __attribute__ ((unused)) bool B2 = digit.B2;
    __attribute__ ((unused)) bool B3 = digit.B3;
    return 0;
}

uint8_t bcd_to_7segment_pla(uint8_t digit) {
    nybble_t bits = ((union {
        uint8_t byte;
        nybble_t nybble;
    }) {.byte = digit}).nybble;
    return get_segment_A(bits) << 6 |
           get_segment_B(bits) << 5 |
           get_segment_C(bits) << 4 |
           get_segment_D(bits) << 3 |
           get_segment_E(bits) << 2 |
           get_segment_F(bits) << 1 |
           get_segment_G(bits) << 0 ;
}
