/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file fpu.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Function prototypes and type declarations for FloatLab.
 *
 ******************************************************************************/

/*
 * FloatLab (c) 2019-22 Christopher A. Bohn
 *
 * Assignment and starter code licensed under the Apache License,
 * Version 2.0 (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef FPU_H
#define FPU_H

#include <stdint.h>

typedef struct {
    uint64_t integer_portion;
    uint64_t fractional_portion;
    int32_t exponent;
    uint8_t sign:1;
    uint8_t is_infinite:1;
    uint8_t is_nan:1;
} unnormal_t;

typedef uint32_t ieee754_t;

enum bit_divider_direction {
    NONE, FROM_LEFT, FROM_RIGHT
};

bool is_infinity(ieee754_t number);
bool is_nan(ieee754_t number);
bool is_zero(ieee754_t number);
bool is_negative(ieee754_t number);

char *bits_to_string(char *destination, uint64_t bits, int start_bit,
                     int end_bit, enum bit_divider_direction bit_dividers);
char *ieee754_to_string(char *destination, ieee754_t number);
char *unnormal_to_string(char *destination, unnormal_t number);

ieee754_t normalize(unnormal_t number);
unnormal_t denormalize(ieee754_t number);
unnormal_t adjust_exponent(unnormal_t number, int32_t amount);

ieee754_t negate(ieee754_t number);
ieee754_t add(ieee754_t augend, ieee754_t addend);
ieee754_t subtract(ieee754_t menuend, ieee754_t subtrahend);
ieee754_t multiply(ieee754_t multiplicand, ieee754_t multiplier);
ieee754_t divide(ieee754_t dividend, ieee754_t divisor);

#endif //FPU_H
