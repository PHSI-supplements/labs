/**************************************************************************//**
 *
 * @file fpu.c
 *
 * @author 1258 Sample Solution
 *
 * @brief Functions that students must implement for FloatLab to demonstrate
 * understanding of the IEEE 754 format and of floating point arithmetic.
 *
 ******************************************************************************/

/*
 * FloatLab assignment and starter code (c) 2019-25 Christopher A. Bohn
 * Floatlab solution (c) the above-named student(s)
 */

#include <assert.h>
#include <stdio.h>
#include "bits-to-string.h"
#include "unnormal.h"
#include "fpu.h"

/* BITMASKS TO EXTRACT SPECIFIC BITFIELDS */

[[maybe_unused]] constexpr uint32_t SIGN_BIT_MASK      = 0x8000'0000;
[[maybe_unused]] constexpr uint32_t EXPONENT_BITS_MASK = 0x7F80'0000;
[[maybe_unused]] constexpr uint32_t FRACTION_BITS_MASK = 0x007F'FFFF;

/* PROPERTIES OF 32-BIT FLOATING POINT NUMBERS */

[[maybe_unused]] constexpr int EXPONENT_BIAS = 127;
[[maybe_unused]] constexpr int NUMBER_OF_FRACTION_BITS = 23;

/* SPECIAL VALUES */

[[maybe_unused]] constexpr uint32_t NAN      = 0x7FC0'0000; // there are over 8 million other valid choices
[[maybe_unused]] constexpr uint32_t INFINITY = 0x7F80'0000;

/**
 * Reports whether a number is infinity.
 * @param number the number in question
 * @return `true` if the number is positive or negative infinity; `false` otherwise
 */
bool is_infinity(ieee754_t number) {
    return (number & (EXPONENT_BITS_MASK | FRACTION_BITS_MASK)) == EXPONENT_BITS_MASK;
}

/**
 * Reports whether a "number" is in fact Not-a-Number.
 * @param number the "number" in question
 * @return `true` if the argument is a legal NAN bit vector; `false` otherwise
 */
bool is_nan(ieee754_t number) {
    return ((number & EXPONENT_BITS_MASK) == EXPONENT_BITS_MASK) && (number & FRACTION_BITS_MASK);
}

/**
 * Reports whether a number is 0.
 * @param number the number in question
 * @return `true` if the number is positive or negative zero; `false` otherwise
 */
bool is_zero(ieee754_t number) {
    return (number & ~SIGN_BIT_MASK) == 0;
}

/**
 * Reports whether a number is negative.
 * @param number the number in question
 * @return `true` if the argument's sign bit is 1; `false` otherwise
 */
bool is_negative(ieee754_t number) {
    return !!(number & SIGN_BIT_MASK);
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
    return (number & EXPONENT_BITS_MASK) ? 1 : 0;
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
    return number & FRACTION_BITS_MASK;
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
    if (number & EXPONENT_BITS_MASK) {
        return (int8_t) (((number & EXPONENT_BITS_MASK) >> NUMBER_OF_FRACTION_BITS) - EXPONENT_BIAS);
    } else {
        return (int8_t) (1 - EXPONENT_BIAS);
    }
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
    int8_t exponent = get_754_exponent(number);
    /* ADJUST THE FRACTION BITS TO FIT UNNORMAL_T'S EXPECTATION */
    fraction = fraction << (64 - NUMBER_OF_FRACTION_BITS);
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
        /* GENERATE THE APPROPRIATE BIT VECTOR AND PLACE IT IN RESULT */
        uint32_t fraction, exponent;
        if (get_unnormal_exponent(number) > EXPONENT_BIAS) {
            result = INFINITY;
        } else {
            if (get_unnormal_exponent(number) > -EXPONENT_BIAS) {
                exponent = ((get_unnormal_exponent(number) + EXPONENT_BIAS) << NUMBER_OF_FRACTION_BITS);
            } else {
                number = set_exponent(number, (int16_t) (1 - EXPONENT_BIAS));
                exponent = 0;
            }
            fraction = (uint32_t) (get_unnormal_fraction(number) >> (64 - NUMBER_OF_FRACTION_BITS));
            result = exponent | fraction;
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
    uint64_t first_dropped_bit = truncated_portion & (1uLL << 63);
    uint64_t trailing_bits = truncated_portion & ~(1uLL << 63);
    if (first_dropped_bit) {    // at least halfway
        if (trailing_bits) {    // more than halfway
            should_round_up = true;
        } else {                // exactly halfway
            uint32_t least_significant_bit = unrounded_number & 0x1;
            if (least_significant_bit) {
                should_round_up = true;
            }
        }
    }
    if (should_round_up) {
        /* ROUND THE NUMBER UP */
        return unrounded_number + 1;
        // if carry stays within fraction, this is clearly correct
        // if carry goes beyond the fraction, then exponent increases by 1, just like we want
        // if that makes the exponent all 1s, then that makes the number infinity, just like we want

        //return -1;  // placeholder
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
    return number ^ SIGN_BIT_MASK;
}

/**
 * Multiplies two floating point values
 * @param multiplicand the first operand
 * @param multiplier the second operand
 * @return the product of the two operands
 */
ieee754_t multiply(ieee754_t multiplicand, ieee754_t multiplier) {
    if (is_nan(multiplicand) || is_nan(multiplier)) {
        return NAN;
    }
    if ((is_infinity(multiplicand) && is_zero(multiplier)) || (is_infinity(multiplier) && is_zero(multiplicand))) {
        return NAN;
    }
    if (is_infinity(multiplicand) || is_zero(multiplicand)) {
        return multiplicand ^ (multiplier & SIGN_BIT_MASK);
    }
    if (is_infinity(multiplier) || is_zero(multiplier)) {
        return multiplier ^ (multiplicand & SIGN_BIT_MASK);
    }
    // These variables are [[maybe_unused]] to suppress a compiler warning until students implement this function
    [[maybe_unused]] unnormal_t decoded_multiplicand = prepare_for_arithmetic(decode(multiplicand));
    [[maybe_unused]] unnormal_t decoded_multiplier = prepare_for_arithmetic(decode(multiplier));
    uint8_t sign = -1;      // throw-
    uint64_t integer = -1;  //      -away
    uint64_t fraction = -1; //            values
    int16_t exponent = -1;  // another throwaway value
    /* COMPUTE THE PRODUCT */
    sign = get_unnormal_sign(decoded_multiplicand) ^ get_unnormal_sign(decoded_multiplier);
    integer = get_unnormal_integer(decoded_multiplicand) * get_unnormal_integer(decoded_multiplier);
    fraction = 0;
    exponent = (int16_t) (get_unnormal_exponent(decoded_multiplicand) + get_unnormal_exponent(decoded_multiplier));
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
        return NAN;
    }
    if (is_infinity(dividend) && is_infinity(divisor)) {
        return NAN;
    }
    if (is_zero(dividend) && is_zero(divisor)) {
        return NAN;
    }
    if (is_zero(dividend) || is_infinity(divisor)) {
        return 0 | ((dividend & SIGN_BIT_MASK) ^ (divisor & SIGN_BIT_MASK));
    }
    if (is_infinity(dividend) || is_zero(divisor)) {
        return INFINITY | ((dividend & SIGN_BIT_MASK) ^ (divisor & SIGN_BIT_MASK));
    }
    // These variables are [[maybe_unused]] to suppress a compiler warning until students implement this function
    [[maybe_unused]] unnormal_t decoded_dividend = prepare_for_arithmetic(decode(dividend));
    [[maybe_unused]] unnormal_t decoded_divisor = prepare_for_arithmetic(decode(divisor));
    uint8_t sign = -1;      // throw-
    uint64_t integer = -1;  //      -away
    uint64_t fraction = -1; //            values
    int16_t exponent = -1;  // another throwaway value
    /* COMPUTE THE QUOTIENT */
    sign = get_unnormal_sign(decoded_dividend) ^ get_unnormal_sign(decoded_divisor);
    integer = get_unnormal_integer(decoded_dividend) / get_unnormal_integer(decoded_divisor);
    fraction = 0;
    exponent = (int16_t) (get_unnormal_exponent(decoded_dividend) - get_unnormal_exponent(decoded_divisor));
    /* The above handles not only single-bit divisors and dividends whose significand is a multiple of the divisor's
     * significand, but seemingly *any* integer that can be represented exactly -- for example, 21 / 12 = 1.75.
     * In a sense, that's because 21 / 12 = (3 * 7) / (3 * 4) = 7 / 4, which has a one-bit divisor.
     * Specifically, it ends up with 21 / 3 = 7 in the unnormal integer's integer portion, and -2 in the exponent. */

    /* if we want to do generalized division, then
     * the integer division remainder, divided by the integer, is the fraction */
    uint64_t numerator = get_unnormal_integer(decoded_dividend) % get_unnormal_integer(decoded_divisor);
    uint64_t denominator = get_unnormal_integer(decoded_divisor);
    if (numerator) {
        int shift = 64;
        while (shift--) {
            numerator <<= 1;
            if (numerator > denominator) {
                fraction |= (1L << shift);
                numerator -= denominator;
            }
            // I thought about shortcutting if we get to a numerator of 0, but 64 iterations isn't so bad,
            // and since exact-results are handled above, we shouldn't end up with a numerator of 0
        }
        // it will be the very rare edge case in which this will make a difference, but... rounding!
        // (again, no exact results need to be handled here, so there is no "exactly halfway" possible)
        // (also: handling rounding here is needed ONLY if working on generalized rounding -- and even then, it's such a rare edge case that students probably could get away without it)
        numerator <<= 1;
        if (numerator > denominator) {
            fraction += 1;
            if (fraction == 0) {
                integer += 1;
            }
        }
    }
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
        return NAN | (augend & SIGN_BIT_MASK);   // this seems to fit the "expected" behavior (except for -1-nan)
    }
    if (is_infinity(augend) && !is_infinity(addend)) {
        return augend;
    }
    if (!is_infinity(augend) && is_infinity(addend)) {
        return addend;
    }
    if (is_infinity(augend) && is_infinity(addend)) {
        if (augend == addend) {
            return augend;
        } else {
            return NAN | SIGN_BIT_MASK;         // this seems to fit the "expected" behavior
        }
    }
    if (is_zero(augend) && is_zero(addend)) {
        return (is_negative(augend) && is_negative((addend))) ? augend : 0;
    }
    if (is_zero(augend)) {
        return addend;
    }
    if (is_zero(addend)) {
        return augend;
    }
    // These variables are [[maybe_unused]] to suppress a compiler warning until students implement this function
    [[maybe_unused]] unnormal_t decoded_augend = prepare_for_arithmetic(decode(augend));
    [[maybe_unused]] unnormal_t decoded_addend = prepare_for_arithmetic(decode(addend));
    uint8_t sign = -1;      // throw-
    uint64_t integer = -1;  //      -away
    uint64_t fraction = -1; //            values
    int16_t exponent = -1;  // another throwaway value
    /* COMPUTE THE SUM */
    // rather than try to figure out which operand has the greater exponent, I'll just do both ¯\_(ツ)_/¯
    while (get_unnormal_exponent(decoded_augend) > get_unnormal_exponent(decoded_addend)) {
        if (!left_shift_will_make_addition_unreliable(decoded_augend)) {
            decoded_augend = decrement_exponent(decoded_augend);
        } else {
            decoded_addend = increment_exponent(decoded_addend);
        }
    }
    while (get_unnormal_exponent(decoded_addend) > get_unnormal_exponent(decoded_augend)) {
        if (!left_shift_will_make_addition_unreliable(decoded_addend)) {
            decoded_addend = decrement_exponent(decoded_addend);
        } else {
            decoded_augend = increment_exponent(decoded_augend);
        }
    }
    // Because one operand was placed (nearly) as far left as it can go before the other operand was shifted right,
    // the lesser operand will be entirely lost in rounding. (There will be at least 16 bits between the greater
    // operand's list significant bit and the lesser operand's most significant bit, all 0s.) Because of this, we don't
    // need to add the fractional portion.
    if (get_unnormal_sign(decoded_augend) == get_unnormal_sign(decoded_addend)) {
        integer = get_unnormal_integer(decoded_augend) + get_unnormal_integer(decoded_addend);
        sign = get_unnormal_sign(decoded_augend);
    } else {
        if (get_unnormal_integer(decoded_augend) > get_unnormal_integer(decoded_addend)) {
            integer = get_unnormal_integer(decoded_augend) - get_unnormal_integer(decoded_addend);
            sign = get_unnormal_sign(decoded_augend);
        } else if (get_unnormal_integer(decoded_addend) > get_unnormal_integer(decoded_augend)) {
            integer = get_unnormal_integer(decoded_addend) - get_unnormal_integer(decoded_augend);
            sign = get_unnormal_sign(decoded_addend);
        } else {
            integer = 0;
            sign = 0;
        }
    }
    fraction = 0;
    exponent = get_unnormal_exponent(decoded_augend);
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
