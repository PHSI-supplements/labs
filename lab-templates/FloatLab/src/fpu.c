/**************************************************************************//**
 *
 * @file fpu.c
 *
 * @author (TYPE YOUR NAME HERE)
 *
 * @brief Functions that students must implement for FloatLab to demonstrate
 * understanding of the IEEE 754 format and of floating point arithmetic.
 *
 ******************************************************************************/

/*
 * FloatLab assignment and starter code (c) 2019-26 Christopher A. Bohn
 * FloatLab solution (c) the above-named student
 */

#include <assert.h>
#include <stdio.h>
#include "bits-to-string.h"
#include "fpu.h"
#include "unnormal.h"

/* BITMASKS TO EXTRACT SPECIFIC BITFIELDS */

[[maybe_unused]] constexpr uint32_t SIGN_BIT_MASK      = 0x0000'0000;
[[maybe_unused]] constexpr uint32_t EXPONENT_BITS_MASK = 0x0000'0000;
[[maybe_unused]] constexpr uint32_t FRACTION_BITS_MASK = 0x0000'0000;

/* PROPERTIES OF 32-BIT FLOATING POINT NUMBERS */

[[maybe_unused]] constexpr int EXPONENT_BIAS = 0;
[[maybe_unused]] constexpr int NUMBER_OF_FRACTION_BITS = 0;

/* SPECIAL VALUES */

[[maybe_unused]] constexpr uint32_t NAN      = 0x0000'0000;
[[maybe_unused]] constexpr uint32_t INFINITY = 0x0000'0000;

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
    return -1;
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
uint32_t get_754_fraction(ieee754_t number) {
    assert(!is_nan(number));
    assert(!is_infinity(number));
    return -1;
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
    return -1;
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
        assert(!operation_was_not_performed(number));
        /* There is a 1 in the integer portion of the "unnormal" number; all remaining bits are in the fraction portion. */
        /* GENERATE THE APPROPRIATE BIT VECTOR AND PLACE IT IN RESULT */
        if (false) {    /* NUMBER IS TOO GREAT TO BE A NORMAL NUMBER */


        } else {        /* ENCODE THE NUMBER IN THE NORMAL OR SUBNORMAL FORM, AS APPROPRIATE */



            /* AT THIS POINT, `result` SHOULD CONTAIN THE VALUE WITH THE EXCESS FRACTION BITS SIMPLY TRUNCATED OFF */
            result = round_to_nearest_even(result, get_unnormal_fraction(number));
        }
    }
    return result | (get_unnormal_sign(number) ? SIGN_BIT_MASK : 0);
}

/**
 * Applies the "round to nearest, ties to even" rounding strategy.
 * @param unrounded_number the number with the excess fraction bits truncated off
 * @param original_fraction the original fraction with the 2**(-1) bit in bit63
 * @return the number, either rounded up or down
 */
ieee754_t round_to_nearest_even(ieee754_t unrounded_number, uint64_t original_fraction) {
    if (is_nan(unrounded_number) || is_infinity(unrounded_number)) {
        return unrounded_number;
    }
    // This variable is [[maybe_unused]] to suppress a compiler warning until students implement this function
    [[maybe_unused]] uint64_t truncated_portion = original_fraction << NUMBER_OF_FRACTION_BITS;
    bool should_round_up = false;
    /* DETERMINE WHETHER TO ROUND UP OR ROUND DOWN */


    if (should_round_up) {
        /* ROUND THE NUMBER UP */

        return -1;  // placeholder
    } else {
        // if rounding down, nothing needs to be done
        return unrounded_number;
    }
}

/**
 * Changes the sign of a floating point number
 * @param number the number to be negated
 * @return `-number`
 */
ieee754_t negate(ieee754_t number) {
    return 0x8000'0000;
}

/**
 * Multiplies two floating point values
 * @param multiplicand the first operand
 * @param multiplier the second operand
 * @return the product of the two operands
 */
ieee754_t multiply(ieee754_t multiplicand, ieee754_t multiplier) {
    if (is_nan(multiplicand) || is_nan(multiplier)) {
        return -1;
    }
    if ((is_infinity(multiplicand) && is_zero(multiplier)) || (is_infinity(multiplier) && is_zero(multiplicand))) {
        return -1;
    }
    if (is_infinity(multiplicand) || is_zero(multiplicand)) {
        return -1;
    }
    if (is_infinity(multiplier) || is_zero(multiplier)) {
        return -1;
    }
    // These variables are [[maybe_unused]] to suppress a compiler warning until students implement this function
    [[maybe_unused]] unnormal_t decoded_multiplicand = prepare_for_arithmetic(decode(multiplicand));
    [[maybe_unused]] unnormal_t decoded_multiplier = prepare_for_arithmetic(decode(multiplier));
    /* The operands are now guaranteed to be finite, non-zero numbers. */
    /* All significant bits are now in the integer portion of the "unnormal" operands. */
    uint8_t sign = -1;      // throw-
    uint64_t integer = -1;  //      -away
    uint64_t fraction = -1; //            values
    int16_t exponent = -1;  // another throwaway value
    /* COMPUTE THE PRODUCT */


    /* encode() takes care of re-normalization and rounding */
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
        return -1;
    }
    if (is_infinity(dividend) && is_infinity(divisor)) {
        return -1;
    }
    if (is_zero(dividend) && is_zero(divisor)) {
        return -1;
    }
    if (is_zero(dividend) || is_infinity(divisor)) {
        return -1;
    }
    if (is_infinity(dividend) || is_zero(divisor)) {
        return -1;
    }
    // These variables are [[maybe_unused]] to suppress a compiler warning until students implement this function
    [[maybe_unused]] unnormal_t decoded_dividend = prepare_for_arithmetic(decode(dividend));
    [[maybe_unused]] unnormal_t decoded_divisor = prepare_for_arithmetic(decode(divisor));
    /* The operands are now guaranteed to be finite, non-zero numbers. */
    /* All significant bits are now in the integer portion of the "unnormal" operands. */
    uint8_t sign = -1;      // throw-
    uint64_t integer = -1;  //      -away
    uint64_t fraction = -1; //            values
    int16_t exponent = -1;  // another throwaway value
    /* COMPUTE THE QUOTIENT */


    /* encode() takes care of re-normalization and rounding */
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
        return -1;
    }
    if (is_infinity(augend) && !is_infinity(addend)) {
        return -1;
    }
    if (!is_infinity(augend) && is_infinity(addend)) {
        return -1;
    }
    if (is_infinity(augend) && is_infinity(addend)) {
        if (augend == addend) {
            return -1;
        } else {
            return -1;
        }
    }
    if (is_zero(augend) && is_zero(addend)) {
        return -1;
    }
    if (is_zero(augend)) {
        return -1;
    }
    if (is_zero(addend)) {
        return -1;
    }
    // These variables are [[maybe_unused]] to suppress a compiler warning until students implement this function
    [[maybe_unused]] unnormal_t decoded_augend = prepare_for_arithmetic(decode(augend));
    [[maybe_unused]] unnormal_t decoded_addend = prepare_for_arithmetic(decode(addend));
    /* The operands are now guaranteed to be finite, non-zero numbers. */
    /* All significant bits are now in the integer portion of the "unnormal" operands. */
    uint8_t sign = -1;      // throw-
    uint64_t integer = -1;  //      -away
    uint64_t fraction = -1; //            values
    int16_t exponent = -1;  // another throwaway value
    /* COMPUTE THE SUM */


    /* encode() takes care of re-normalization and rounding */
    unnormal_t sum = unnormal(.sign = sign, .integer = integer, .fraction = fraction, .exponent = exponent);
    return encode(sum);
}

/**
 * Subtracts a floating point value from another.
 * @param minuend the first operand
 * @param subtrahend the second operand
 * @return the difference of the two operands
 */
ieee754_t subtract(ieee754_t minuend, ieee754_t subtrahend) {
    return add(minuend, negate(subtrahend));
}
