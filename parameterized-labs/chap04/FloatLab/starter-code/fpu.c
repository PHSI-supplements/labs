/**************************************************************************//**
 *
 * @file fpu.c
 *
 * @author (TYPE YOUR NAME HERE)
 * @author (TYPE YOUR PARTNER'S NAME HERE, IF APPLICABLE)
 *
 * @brief Functions that students must implement for FloatLab to demonstrate
 * understanding of the IEEE 754 format and of floating point arithmetic.
 *
 ******************************************************************************/

/*
 * FloatLab assignment and starter code (c) 2019-24 Christopher A. Bohn
 * Floatlab solution (c) the above-named student(s)
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "fpu.h"
#include "unnormal.h"

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
bool is_negative(ieee754_t number) {
    return false;
}

/**
 * Returns the integer portion of an IEEE 754-compliant number.
 *
 * @note The number is assumed to be a finite number;
 *      it cannot be infinity, and it cannot be NaN.
 *
 * @param number the value whose integer portion is to be returned
 * @return the implicit integer portion of the number
 */
uint8_t get_754_integer(ieee754_t number) {
    assert(!is_nan(number));
    assert(!is_infinity(number));
    return 0;
}

/**
 * Returns the fractional portion of an IEEE 754-compliant number.
 *
 * @note The bits that are returned are not shifted; only the lower
 *      NUMBER_OF_FRACTION_BITS should be considered significant.
 *
 * @note The number is assumed to be a finite number;
 *      it cannot be infinity, and it cannot be NaN.
 *
 * @param number the value whose fraction portion is to be returned
 * @return the fraction bits of the number
 */
uint8_t get_754_fraction(ieee754_t number) {
    assert(!is_nan(number));
    assert(!is_infinity(number));
    return 0;
}

/**
 * Returns the two's complement representation of an IEEE 754-compliant number's
 *      exponent.
 *
 * @note This function converts the exponent to two's complement before returning
 *      it.
 *
 * @note The number is assumed to be a finite number;
 *      it cannot be infinity, and it cannot be NaN.
 *
 * @param number the number whose exponent is to be returned
 * @return the two's complement representation of the number's exponent
 */
int8_t get_754_exponent(ieee754_t number) {
    assert(!is_nan(number));
    assert(!is_infinity(number));
    return 0;
}

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
        uint8_t integer = get_754_integer(number);
        uint32_t fraction = get_754_fraction(number);
        int8_t exponent = get_754_exponent(number);
        char fraction_string[40];
        sprintf(destination + 12, "%u.%s_{2} x 2^{%d}",
                integer,
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
unnormal_t decode(ieee754_t number) {
    uint8_t sign = number & SIGN_BIT_MASK ? 1 : 0;
    if (is_infinity(number)) {
        return unnormal(.sign = sign, .is_infinite = true);
    }
    if (is_nan(number)) {
        return unnormal(.sign = sign, .is_not_a_number = true);
    }
    uint64_t integer = get_754_integer(number);
    uint64_t fraction = get_754_fraction(number);
    int16_t exponent = get_754_exponent(number);
    /* ADJUST THE FRACTION BITS TO FIT UNNORMAL_T'S EXPECTATION */

    unnormal_t value = unnormal(.sign = sign, .integer = integer, .fraction = fraction, .exponent = exponent);
    assert(!created_number_is_improbable(value));
    return value;
}

/**
 * Converts an `unnormal_t` number into an IEEE 754-compliant representation.
 * @param number the number to be made IEEE 754-compliant
 * @return an `ieee754_t` bit vector representing the number's value
 */
ieee754_t encode(unnormal_t number) {
    ieee754_t result = -1;  // throwaway value
    if (is_infinite(number)) {
        result = INFINITY;
    } else if (is_not_a_number(number)) {
        result = NAN;
    } else if ((get_unnormal_integer(number) == 0) && (get_unnormal_fraction(number) == 0)) {
        result = 0;
    } else {
        number = set_integer(number, 1);
        assert(!shift_underflowed(number));
        assert(!shift_overflowed(number));
        assert(!operation_was_not_performed(number));
        /* GENERATE THE APPROPRIATE BIT VECTOR AND PLACE IT IN RESULT */


    }
    return result | (get_unnormal_sign(number) ? SIGN_BIT_MASK : 0);
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
 * Multiplies two floating point values
 * @param multiplicand the first operand
 * @param multiplier the second operand
 * @return the product of the two operands
 */
ieee754_t multiply(ieee754_t multiplicand, ieee754_t multiplier) {
    if (is_nan(multiplicand) || is_nan(multiplier)) {
        return 0;
    }
    if ((is_infinity(multiplicand) && is_zero(multiplier)) || (is_infinity(multiplier) && is_zero(multiplicand))) {
        return 0;
    }
    if (is_infinity(multiplicand) || is_zero(multiplicand)) {
        return 0;
    }
    if (is_infinity(multiplier) || is_zero(multiplier)) {
        return 0;
    }
    unnormal_t decoded_multiplicand = prepare_for_arithmetic(decode(multiplicand));
    unnormal_t decoded_multiplier = prepare_for_arithmetic(decode(multiplier));
    uint8_t sign = -1;      // throw-
    uint64_t integer = -1;  //      -away
    uint64_t fraction = -1; //            values
    int16_t exponent = -1;  // another throwaway value
    /* COMPUTE THE PRODUCT */


    unnormal_t product = unnormal(.sign = sign, .integer = integer, .fraction = fraction, .exponent = exponent);
    return encode(product);
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
    unnormal_t decoded_dividend = prepare_for_arithmetic(decode(dividend));
    unnormal_t decoded_divisor = prepare_for_arithmetic(decode(divisor));
    uint8_t sign = -1;      // throw-
    uint64_t integer = -1;  //      -away
    uint64_t fraction = -1; //            values
    int16_t exponent = -1;  // another throwaway value
    /* COMPUTE THE QUOTIENT */


    unnormal_t quotient = unnormal(.sign = sign, .integer = integer, .fraction = fraction, .exponent = exponent);
    return encode(quotient);
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
    unnormal_t decoded_augend = prepare_for_arithmetic(decode(augend));
    unnormal_t decoded_addend = prepare_for_arithmetic(decode(addend));
    uint8_t sign = -1;      // throw-
    uint64_t integer = -1;  //      -away
    uint64_t fraction = -1; //            values
    int16_t exponent = -1;  // another throwaway value
    /* COMPUTE THE SUM */


    unnormal_t sum = unnormal(.sign = sign, .integer = integer, .fraction = fraction, .exponent = exponent);
    return encode(sum);
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
