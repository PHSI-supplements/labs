/**************************************************************************//**
 *
 * @file fpu.c
 *
 * @author (STUDENT -- TYPE YOUR NAME HERE)
 *
 * @brief Functions that students must implement for FloatLab to demonstrate
 * understanding of the IEEE 754 format and of floating point arithmetic.
 *
 ******************************************************************************/

/*
 * FloatLab assignment and starter code (c) 2019-22 Christopher A. Bohn
 * Floatlab solution (c) the above-named student
 */

#include <stdio.h>
#include <stdbool.h>
#include "fpu.h"

/* BITMASKS TO EXTRACT SPECIFIC BITFIELDS */

const uint32_t SIGN_BIT_MASK = 0x00000000;
const uint32_t EXPONENT_BITS_MASK = 0x00000000;
const uint32_t FRACTION_BITS_MASK = 0x00000000;

/* PROPERTIES OF 32-BIT FLOATING POINT NUMBERS */

const int EXPONENT_BIAS = 0;
const int NUMBER_OF_FRACTION_BITS = 0;

/* SPECIAL VALUES */

const uint32_t NAN = 0x00000000;
const uint32_t INFINITY = 0x00000000;

/**
 * Reports whether a number is infinity.
 * @param number the number in question
 * @return `true` if the number is positive or negative infinity; `false` otherwise
 */
bool is_infinity(ieee754_t number) {
    return false;
}

/**
 * Reports whether a "number" is in fact Not-a-Number.
 * @param number the "number" in question
 * @return `true` if the argument is a legal NAN bit vector; `false` otherwise
 */
bool is_nan(ieee754_t number) {
    return false;
}

/**
 * Reports whether a number is 0.
 * @param number the number in question
 * @return `true` if the number is positive or negative zero; `false` otherwise
 */
bool is_zero(ieee754_t number) {
    return false;
}

/**
 * Reports whether a number is negative.
 * @param number the number in question
 * @return `true` if the argument's sign bit is 1; `false` otherwise
 */
bool is_negative(ieee754_t number) { return false; }

/**
 * @brief Converts an IEEE 754-compliant number to a string depicting the
 * number's value as a base-2 floating point number.
 *
 * Unless the number is infinity, NaN, or zero, the expected string consists of
 * the sign (+ or -), then single bit, then a binary point, then the fractional
 * bits, followed by "_{2} x 2^{exponent}" where the exponent is expressed in
 * decimal.
 *
 * The caller is responsible for providing a buffer of sufficient size to hold
 * the string (57 bytes is sufficient).
 *
 * @param destination a buffer to hold the string
 * @param number the value to be converted into a string
 * @return the destination buffer containing the number's string representation
 */
char *ieee754_to_string(char *destination, ieee754_t number) {
    sprintf(destination, "%#010x\t", number);
    sprintf(destination + 11, "%c", is_negative(number) ? '-' : '+');
    if (is_nan(number)) {
        sprintf(destination + 12, "Not a Number");
    } else if (is_infinity(number)) {
        sprintf(destination + 12, "Infinity");
    } else if (is_zero(number)) {
        sprintf(destination + 12, "0.0");
    } else {
        // The number is either Normal or Subnormal
        int integer_portion;
        uint32_t fraction;
        int exponent;
        char fraction_string[40];   // Do not directly edit `fraction_string`
        /* DETERMINE THE INTEGER PORTION, THE FRACTION, AND THE EXPONENT */


        sprintf(destination + 12, "%d.%s_{2} x 2^{%d}",
               integer_portion,
               bits_to_string(fraction_string, fraction, NUMBER_OF_FRACTION_BITS - 1, 0, FROM_LEFT),
               exponent);
    }
    return destination;
}

/**
 * Converts an IEEE 754-compliant number into an `unnormal_t` representation.
 * @param number The number to be made "unnormal"
 * @return an `unnormal_t` representation of the number's value
 */
unnormal_t denormalize(ieee754_t number) {
    unnormal_t result;
    result.sign = number & SIGN_BIT_MASK ? 1 : 0;
    result.is_infinite = 0;
    result.is_nan = 0;
    if (is_infinity(number)) {
        result.is_infinite = 1;
    } else if (is_nan(number)) {
        result.is_nan = 1;
    } else {
        /* DETERMINE THE INTEGER PORTION, THE FRACTION, AND THE EXPONENT */
        result.fractional_portion = (uint64_t) (0);


    }
    return result;
}

/**
 * Adjusts the virtual binary point in an `unnormal_t` number by changing the
 * exponent and moving bits between the integer portion and the fractional
 * portion.
 *
 * @param number the number to be adjusted
 * @param amount the positive or negative amount by which the exponent should
 *      be adjusted
 * @return an `unnormal_t` variable that represents the number's value but with
 *      a different exponent and position of the virtual binary point
 */
unnormal_t adjust_exponent(unnormal_t number, int32_t amount) {
    /* IMPLEMENT THIS FUNCTION */


    return number;
}

/**
 * Converts an `unnormal_t` number into an IEEE 754-compliant representation.
 * @param number the number to be made IEEE 754-compliant
 * @return an `ieee754_t` bit vector representing the number's value
 */
ieee754_t normalize(unnormal_t number) {
    ieee754_t result;
    if (number.is_infinite) {
        result = INFINITY;
    } else if (number.is_nan) {
        result = NAN;
    } else if ((number.integer_portion == 0) && (number.fractional_portion == 0)) {
        result = 0;
    } else {
        /* GENERATE THE APPROPRIATE BIT VECTOR */


    }
    return result | (number.sign ? SIGN_BIT_MASK : 0);
}

/**
 * Adds two floating point values.
 * @param augend the first operand
 * @param addend the second operand
 * @return the sum of the two operands
 */
ieee754_t add(ieee754_t augend, ieee754_t addend) {
    if (is_nan(augend) || is_nan(addend)) {
        return 0;
    }
    if (is_infinity(augend) && !is_infinity(addend)) {
        return 0;
    }
    if (!is_infinity(augend) && is_infinity(addend)) {
        return 0;
    }
    if (is_infinity(augend) && is_infinity(addend)) {
        if (augend == addend) {
            return 0;
        } else {
            return 0;
        }
    }
    if (is_zero(augend) && is_zero(addend)) {
        return 0;
    }
    if (is_zero(augend)) {
        return 0;
    }
    if (is_zero(addend)) {
        return 0;
    }
    unnormal_t denormalized_augend = denormalize(augend);
    unnormal_t denormalized_addend = denormalize(addend);
    unnormal_t sum = {
            .sign = 0,
            .integer_portion =0,
            .fractional_portion = 0,
            .exponent = 0,
            .is_infinite = 0,
            .is_nan = 0
    };
    /* COMPUTE THE SUM */


    return normalize(sum);
}

/**
 * Changes the sign of a floating point number
 * @param number the number to be negated
 * @return `-number`
 */
ieee754_t negate(ieee754_t number) {
    return 0;
}

/**
 * Subtracts a floating point value from another.
 * @param menuend the first operand
 * @param subtrahend the second operand
 * @return the difference of the two operands
 */
ieee754_t subtract(ieee754_t menuend, ieee754_t subtrahend) {
    return add(menuend, negate(subtrahend));
}

/**
 * Multiplies two floating point values
 * @param multiplicand the first operand
 * @param multiplier the second operand
 * @return the product of the two operands
 */
ieee754_t multiply(ieee754_t multiplicand, ieee754_t multiplier) {
    if (is_nan(multiplicand) || is_nan(multiplier)) {
        return 0;
    }
    if ((is_infinity(multiplicand) && is_zero(multiplier)) || (is_infinity(multiplier && is_zero(multiplicand)))) {
        return 0;
    }
    if (is_infinity(multiplicand) || is_zero(multiplicand)) {
        return 0;
    }
    if (is_infinity(multiplier) || is_zero(multiplier)) {
        return 0;
    }
    unnormal_t denormalized_multiplicand = denormalize(multiplicand);
    unnormal_t denormalized_multiplier = denormalize(multiplier);
    unnormal_t product = {
            .sign = 0,
            .integer_portion =0,
            .fractional_portion = 0,
            .exponent = 0,
            .is_infinite = 0,
            .is_nan = 0
    };
    /* COMPUTE THE PRODUCT */


    return normalize(product);
}

/**
 * Divides a floating point value by another
 * @param dividend the first operand
 * @param divisor the second operand
 * @return the quotient of the two operands
 */
ieee754_t divide(ieee754_t dividend, ieee754_t divisor) {
    if (is_nan(dividend) || is_nan(divisor)) {
        return 0;
    }
    if (is_infinity(dividend) && is_infinity(divisor)) {
        return 0;
    }
    if (is_zero(dividend) && is_zero(divisor)) {
        return 0;
    }
    if (is_zero(dividend) || is_infinity(divisor)) {
        return 0;
    }
    if (is_infinity(dividend) || is_zero(divisor)) {
        return 0;
    }
    unnormal_t denormalized_dividend = denormalize(dividend);
    unnormal_t denormalized_divisor = denormalize(divisor);
    unnormal_t quotient = {
            .sign = denormalized_dividend.sign ^ denormalized_divisor.sign,
            .integer_portion = denormalized_dividend.integer_portion / denormalized_divisor.integer_portion,
            .fractional_portion = 0,
            .exponent = denormalized_dividend.exponent - denormalized_divisor.exponent,
            .is_nan = 0,
            .is_infinite = 0};
    /* COMPUTE THE QUOTIENT */


    return normalize(quotient);
}
