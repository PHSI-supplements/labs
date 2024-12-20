/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file unnormal.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Encapsulation of the "unnormal form" for FloatLab.
 *
 ******************************************************************************/

/*
 * FloatLab (c) 2019-23 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef UNNORMAL_H
#define UNNORMAL_H

#include <stdbool.h>
#include <stdint.h>

/**
 * Constants for various warnings that may be issued by the Unnonrmal code.
 */
typedef enum {
    NO_WARNING = 0,
    OTHER = 1,
    MULTIPLICATION_IS_NOT_RECOMMENDED = 2,
    MULTIPLICATION_IS_UNRELIABLE = 4,
    ADDITION_IS_UNRELIABLE = 8,
    SHIFT_OVERFLOWED = 16,
    SHIFT_UNDERFLOWED = 32,
    REQUESTED_OPERATION_COULD_NOT_BE_PERFORMED = 64,
    IMPROBABLE_VALUE = 128,
} unnormal_warning_t;

/**
 * Type definition for a floating point value that, while bit-limited, is not as bit-limited as IEEE~754 values.
 * Unlike IEEE~754 values, a non-infinite, Unnormal value that is a number is not limited to being in a normal
 * or subnormal form.
 */
typedef struct {
    uint64_t integer;
    uint64_t fraction;
    int32_t exponent;
    uint8_t sign: 1;
    uint8_t is_infinite: 1;
    uint8_t is_not_a_number: 1;
    unnormal_warning_t warnings;
} unnormal_t;

/*                                   *
 * The "constructor" and "to string" *
 *                                   */

/**
 * A convenience macro to create an Unnormal value. Evaluates to an <code>unnormal_t</code> variable (*not* return a
 * pointer). The parameter list is a series of <b>dot-prefixed named fields</b> to create the Unnormal value. If at
 * least one field is specified then all omitted fields will be treated as 0.
 * Example: <code>unnormal(.sign=0, .infinity=1)</code>
 *
 * @see _create_unnormal
 *
 * @param sign indicates whether the value is negative (1) or positive (0)
 * @param integer the integer portion of the value; that is, the portion to the left of the binary point;
 *      this value should not exceed the maximum unsigned integer value representable with 64 bits
 * @param fraction the fractional portion of the value; that is, the portion to the right of the binary point;
 *      this value should be treated as the numerator of a fraction whose denominator is 2**64.
 * @param exponent the two's complement representation of the floating point value's exponent of 2;
 *      this value should not exceed the range of signed integer values representable with 16 bits
 * @param is_infinite indicates whether the value is positive/negative infinity (1) or not (0)
 * @param is_not_a_number indicates whether the value is NaN (1) or a valid number (0)
 * @return an <code>unnormal_t</code> variable containing the specified value
 */
#define unnormal(...) _create_unnormal(&(unnormal_t){__VA_ARGS__})

/**
 * A function to create an Unnormal value. Returns an <code>unnormal_t</code> variable by value; it does *not* return
 * a pointer. This function should not be called directly.
 *
 * @see unnormal
 *
 * @param args a structure that holds the arguments to create the Unnormal value
 * @return an <code>unnormal_t</code> variable containing the specified value
 */
unnormal_t _create_unnormal(unnormal_t *args); // NOLINT(bugprone-reserved-identifier)

/**
 * Produces a string representation of an Unnormal value. Because of the number of bits available in the
 * <code>unnormal_t</code> fields, the significand is represented in base-16, though the exponent is the exponent of 2.
 * @param destination a pointer to buffer at least 53 bytes long in which to store the string representation
 * @param number the Unnormal value to be converted into a string
 * @return the <code>destination</code> pointer, with the string representation in the buffer it points to
 */
char *unnormal_to_string(char *destination, unnormal_t number);

/*           *
 * Accessors *
 *           */

/**
 * Indicates whether a value is positive or negative.
 * @param number the Unnormal value to be evaluated
 * @return 0 if the value is positive, 1 if the value is negative
 */
uint8_t get_unnormal_sign(unnormal_t number);

/**
 * Provides the integer portion of the floating point number.
 * @param number the Unnormal value to be evaluated
 * @return a <code>uint64_t</code> storing the value's integer portion
 */
uint64_t get_unnormal_integer(unnormal_t number);

/**
 * Provides the fractional portion of the floating point number. This value should be treated as the numerator of a
 * fraction whose denominator is 2**64
 * @param number the Unnormal value to be evaluated
 * @return a <code>uint64_t</code> storing value's fractional portion
 */
uint64_t get_unnormal_fraction(unnormal_t number);

/**
 * Provides the two's complement exponent of the base-2 floating point number.
 * @param number the Unnormal value to be evaluated
 * @return a <code>int16_t</code> storing value's exponent of 2
 */
int16_t get_unnormal_exponent(unnormal_t number);

/**
 * Indicates whether a value is plus/minus infinity
 * @param number the Unnormal value to be evaluated
 * @return 0 if the value is finite (or NaN), 1 if the value is plus/minus infinity
 */
bool is_infinite(unnormal_t number);

/**
 * Indicates whether a value is NaN
 * @param number the Unnormal value to be evaluated
 * @return 0 if the value is a valid number, 1 if the value is not a number
 */
bool is_not_a_number(unnormal_t number);

/*          *
 * Warnings *
 *          */

bool has_no_warnings(unnormal_t number);
bool has_unspecified_warning(unnormal_t number);
bool multiplication_is_not_recommended(unnormal_t number);
bool multiplication_is_unreliable(unnormal_t number);
bool addition_is_unreliable(unnormal_t number);
bool shift_overflowed(unnormal_t number);
bool shift_underflowed(unnormal_t number);
bool operation_was_not_performed(unnormal_t number);
bool created_number_is_improbable(unnormal_t number);

/*                     *
 * Primitive functions *
 *                     */

/**
 * Shifts the significand's bits to the left by one position, having the effect of moving the binary point to the right
 * and decreasing the exponent by one. The argument is unmodified (pass-by-value), and the returned Unnormal value
 * has the same value as the argument but has a different integer, fraction, and exponent.
 *
 * @see decrement_exponent
 * @see move_binary_point_to_the_right
 *
 * @param number the value whose copy will have shifted bits
 * @return a copy of the argument but with its bits shifted
 */
unnormal_t shift_left_once(unnormal_t number);

/**
 * Shifts the significand's bits to the right by one position, having the effect of moving the binary point to the right
 * and decreasing the exponent by one. The argument is unmodified (pass-by-value), and the returned Unnormal value
 * has the same value as the argument but has a different integer, fraction, and exponent.
 *
 * @see increment_exponent
 * @see move_binary_point_to_the_left
 *
 * @param number the value whose copy will have shifted bits
 * @return a copy of the argument but with its bits shifted
 */
unnormal_t shift_right_once(unnormal_t number);

/*                              *
 * Higher-level shift functions *
 *                              */

/**
 * Shifts the significand's bits to the left by the specified amount, with corresponding effects on the binary point and
 * the exponent. The <code>number</code> argument is unmodified (pass-by-value), and the returned Unnormal value
 * has the same value as the argument but has a different integer, fraction, and exponent. If the <code>amount</code>
 * argument is negative, then the returned value will have the original significand, and the
 * <code>REQUESTED_OPERATION_COULD_NOT_BE_PERFORMED</code> warning flag will be set.
 *
 * @see shift_left_once
 *
 * @param number the value whose copy will have shifted bits
 * @param amount the amount to shift the bits by
 * @return a copy of the argument but with its bits shifted
 */
unnormal_t shift_left(unnormal_t number, int16_t amount);

/**
 * Shifts the significand's bits to the right by the specified amount, with corresponding effects on the binary point
 * and the exponent. The <code>number</code> argument is unmodified (pass-by-value), and the returned Unnormal value
 * has the same value as the argument but has a different integer, fraction, and exponent. If the <code>amount</code>
 * argument is negative, then the returned value will have the original significand, and the
 * <code>REQUESTED_OPERATION_COULD_NOT_BE_PERFORMED</code> warning flag will be set.
 *
 * @see shift_right_once
 *
 * @param number the value whose copy will have shifted bits
 * @param amount the amount to shift the bits by
 * @return a copy of the argument but with its bits shifted
 */
unnormal_t shift_right(unnormal_t number, int16_t amount);

/*                     *
 * Alignment functions *
 *                     */

/**
 * Shifts the significand such that the least-significant `1` bit is in the $2^0$ position, with a
 * corresponding change in the exponent (the fraction, of course, will be 0). The argument is unmodified
 * (pass-by-value), and the returned Unnormal value has the same value as the argument but has a different integer,
 * fraction, and exponent.
 *
 * @see prepare_for_arithmetic
 *
 * @param number the value whose copy will have shifted bits
 * @return a copy of the argument but with its non-zero bits to the left of the binary point
 */
unnormal_t place_all_bits_in_integer(unnormal_t number);

/**
 * If possible, shifts the significand such that the resulting integer portion is the specified value, with a
 * corresponding changes in the fraction and exponent. The argument is unmodified (pass-by-value), and the returned
 * Unnormal value has the same value as the argument but has a different integer, fraction, and exponent. If the integer
 * portion cannot be set to the specified value, then the returned value will have the original significand, and the
 * <code>REQUESTED_OPERATION_COULD_NOT_BE_PERFORMED</code> warning flag will be set.
 *
 * @param number the value whose copy will have shifted bits
 * @param integer the desired integer portion of the significand
 * @return a copy of the argument with the specified integer or with the original integer if the specified integer
 *      cannot be set
 */
unnormal_t set_integer(unnormal_t number, unsigned int integer);

/**
 * Shifts the significand, with a corresponding change in the exponent, such that the resulting exponent is the
 * specified value with a corresponding changes in the fraction and exponent. The argument is unmodified
 * (pass-by-value), and the returned Unnormal value has the same value as the argument but has a different integer,
 * fraction, and exponent.
 *
 * @param number the value whose copy will have shifted bits
 * @param exponent the desired exponent of 2
 * @return a copy of the argument with the specified exponent
 */
unnormal_t set_exponent(unnormal_t number, int16_t exponent);

/*                      *
 * Prediction functions *
 *                      */

/**
 * Indicates that if the next operation is addition with the specified values, then adding the fractions will carry into
 * the integer portion, requiring you to add 1 to the sum's integer.
 * @param addend one of the values potentially being added to the other
 * @param augend the other value potentially being added to the first
 * @return <code>true</code> if adding the fractions to each other will overflow, <code>false</code> otherwise
 */
bool fraction_will_carry_into_integer_on_addition(unnormal_t addend, unnormal_t augend);

/**
 * Indicates that if the next operation is subtraction with the specified values, then subtracting the fractions will
 * require ``borrowing'' from the integer portion, requiring you to subtract 1 to the difference's integer.
 * @param menuend the value potentially being subject to subtraction
 * @param subtrahend the value potentially being subtracted from the first
 * @return <code>true</code> if the subtrahend's fraction is greater than the menuend's fraction,
 *      <code>false</code> otherwise
 */
bool fraction_will_borrow_from_integer_on_subtraction(unnormal_t menuend, unnormal_t subtrahend);

/**
 * Indicates that if the next function is #left_shift_once (or one of its aliases) then after that function
 * call, #multiplication_is_unreliable() will return <code>true</code>
 * @param number the Unnormal value to be evaluated
 * @return <code>true</code> if the value's integer portion has a `1` bit just to the right of the median,
 *      <code>false</code> otherwise
 */
bool left_shift_will_make_multiplication_unreliable(unnormal_t number);

/**
 * Indicates that if the next function is #left_shift_once (or one of its aliases) then after that function
 * call, #addition_is_unreliable() will return <code>true</code>
 * @param number the Unnormal value to be evaluated
 * @return <code>true</code> if the value's integer portion has a `1` bit in the second-most-significant position
 *      <code>false</code> otherwise
 */
bool left_shift_will_make_addition_unreliable(unnormal_t number);

/**
 * Indicates that if the next function is #left_shift_once (or one of its aliases) then after that function
 * call, #shift_overflowed() will return <code>true</code>
 * @param number the Unnormal value to be evaluated
 * @return <code>true</code> if the value's integer portion has a `1` bit in the most-significant position
 *      <code>false</code> otherwise
 */
bool left_shift_will_overflow(unnormal_t number);

/**
 * Indicates that if the next function is #right_shift_once (or one of its aliases) then after that function
 * call, #shift_underflowed() will return <code>true</code>
 * @param number the Unnormal value to be evaluated
 * @return <code>true</code> if the value's fraction portion has a `1` bit in the least-significant position
 *      <code>false</code> otherwise
 */
bool right_shift_will_underflow(unnormal_t number);

/*                  *
 * Function aliases *
 *                  */

/**
 * Shifts the significand's bits to the left by one position, having the effect of moving the binary point to the right
 * and decreasing the exponent by one. The argument is unmodified (pass-by-value), and the returned Unnormal value
 * has the same value as the argument but has a different integer, fraction, and exponent.
 *
 * @see shift_left_once
 * @see move_binary_point_to_the_right
 *
 * @param number the value whose copy will have a lesser exponent
 * @return a copy of the argument but with its exponent decremented
 */
static inline unnormal_t decrement_exponent(unnormal_t number) { return shift_left_once(number); }

/**
 * Shifts the significand's bits to the right by one position, having the effect of moving the binary point to the right
 * and decreasing the exponent by one. The argument is unmodified (pass-by-value), and the returned Unnormal value
 * has the same value as the argument but has a different integer, fraction, and exponent.
 *
 * @see shift_right_once
 * @see move_binary_point_to_the_left
 *
 * @param number the value whose copy will have a greater exponent
 * @return a copy of the argument but with its exponent incremented
 */
static inline unnormal_t increment_exponent(unnormal_t number) { return shift_right_once(number); }

/**
 * Shifts the significand's bits to the left by one position, having the effect of moving the binary point to the right
 * and decreasing the exponent by one. The argument is unmodified (pass-by-value), and the returned Unnormal value
 * has the same value as the argument but has a different integer, fraction, and exponent.
 *
 * @see shift_left_once
 * @see decrement_exponent
 *
 * @param number the value whose copy will have its binary point moved
 * @return a copy of the argument but with its binary point moved to the right
 */
static inline unnormal_t move_binary_point_to_the_right(unnormal_t number) { return shift_left_once(number); }

/**
 * Shifts the significand's bits to the right by one position, having the effect of moving the binary point to the right
 * and decreasing the exponent by one. The argument is unmodified (pass-by-value), and the returned Unnormal value
 * has the same value as the argument but has a different integer, fraction, and exponent.
 *
 * @see shift_right_once
 * @see increment_exponent
 *
 * @param number the value whose copy will have its binary point moved
 * @return a copy of the argument but with its binary point moved to the left
 */
static inline unnormal_t move_binary_point_to_the_left(unnormal_t number) { return shift_right_once(number); }

/**
 * Shifts the significand such that the least-significant `1` bit is in the 2**0 position, with a
 * corresponding change in the exponent (the fraction, of course, will be 0). The argument is unmodified
 * (pass-by-value), and the returned Unnormal value has the same value as the argument but has a different integer,
 * fraction, and exponent.
 *
 * @see place_all_bits_in_integer
 *
 * @param number the value whose copy will have shifted bits
 * @return a copy of the argument but with its non-zero bits to the left of the binary point
 */
static inline unnormal_t prepare_for_arithmetic(unnormal_t number) { return place_all_bits_in_integer(number); }

#endif //UNNORMAL_H
