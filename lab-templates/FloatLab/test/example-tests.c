/**************************************************************************//**
 *
 * @file unit-tests.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Example tests for FloatLab, from the write-up's example test cases.
 *
 * These tests are not sufficient to establish correctness.
 *
 ******************************************************************************/

/*
 * FloatLab assignment and starter code (c) 2019-26 Christopher A. Bohn
 */

#include <math.h>
#include <stdint.h>
#include "unit-tests.h"
#include "../src/fpu.h"
#include "../src/unnormal.h"

int main() {
    return run_tests(5);
}

/*****************/
/* TESTS GO HERE */
/*****************/

/* THIS VIOLATES THE ASSIGNMENT CODE'S CONSTRAINTS */
/* BUT YOU MAY USE IT IN YOUR TEST CODE */
union float_converter {
    ieee754_t bit_vector;
    float reference_value;
};

//// 03-constants-queries.md
//
//TEST(test_positive_zero)
//    ieee754_t value = ((union float_converter) {.reference_value = 0.0f}).bit_vector;
//    ASSERT_FALSE(is_nan(value));
//    ASSERT_FALSE(is_infinity(value));
//    ASSERT_TRUE(is_zero(value));
//    ASSERT_FALSE(is_negative(value));
//END_TEST
//
//TEST(test_negative_zero)
//    ieee754_t value = ((union float_converter) {.reference_value = -0.0f}).bit_vector;
//    ASSERT_FALSE(is_nan(value));
//    ASSERT_FALSE(is_infinity(value));
//    ASSERT_TRUE(is_zero(value));
//    ASSERT_TRUE(is_negative(value));
//END_TEST
//
//TEST(test_positive_infinity)
//    ieee754_t value = ((union float_converter) {.reference_value = INFINITY}).bit_vector;
//    ASSERT_FALSE(is_nan(value));
//    ASSERT_TRUE(is_infinity(value));
//    ASSERT_FALSE(is_zero(value));
//    ASSERT_FALSE(is_negative(value));
//END_TEST
//
//TEST(test_negative_infinity)
//    ieee754_t value = ((union float_converter) {.reference_value = -INFINITY}).bit_vector;
//    ASSERT_FALSE(is_nan(value));
//    ASSERT_TRUE(is_infinity(value));
//    ASSERT_FALSE(is_zero(value));
//    ASSERT_TRUE(is_negative(value));
//END_TEST
//
//TEST(test_positive_nan)
//    ieee754_t value = ((union float_converter) {.reference_value = NAN}).bit_vector;
//    ASSERT_TRUE(is_nan(value));
//    ASSERT_FALSE(is_infinity(value));
//    ASSERT_FALSE(is_zero(value));
//    ASSERT_FALSE(is_negative(value));
//END_TEST
//
//TEST(test_negative_nan)
//    ieee754_t value = ((union float_converter) {.reference_value = -NAN}).bit_vector;
//    ASSERT_TRUE(is_nan(value));
//    ASSERT_FALSE(is_infinity(value));
//    ASSERT_FALSE(is_zero(value));
//    ASSERT_TRUE(is_negative(value));
//END_TEST
//
//// 04-examining-numbers.md
//
//TEST(test_3f800000)
//    ieee754_t value = 0x3f80'0000;
//    uint8_t expected_integer = 1;
//    uint32_t expected_fraction = 0b0000'0000'0000'0000'0000'000;
//    int8_t expected_exponent = 0;
//    ASSERT_FALSE(is_negative(value));
//    ASSERT_EQUAL(expected_integer, get_754_integer(value));
//    ASSERT_EQUAL(expected_fraction, get_754_fraction(value));
//    ASSERT_EQUAL(expected_exponent, get_754_exponent(value));
//END_TEST
//
//TEST(test_3e800000)
//    ieee754_t value = 0x3e80'0000;
//    uint8_t expected_integer = 1;
//    uint32_t expected_fraction = 0b0000'0000'0000'0000'0000'000;
//    int8_t expected_exponent = -2;
//    ASSERT_FALSE(is_negative(value));
//    ASSERT_EQUAL(expected_integer, get_754_integer(value));
//    ASSERT_EQUAL(expected_fraction, get_754_fraction(value));
//    ASSERT_EQUAL(expected_exponent, get_754_exponent(value));
//END_TEST
//
//TEST(test_417a0000)
//    ieee754_t value = 0x417a'0000;
//    uint8_t expected_integer = 1;
//    uint32_t expected_fraction = 0b1111'0100'0000'0000'0000'000;
//    int8_t expected_exponent = 3;
//    ASSERT_FALSE(is_negative(value));
//    ASSERT_EQUAL(expected_integer, get_754_integer(value));
//    ASSERT_EQUAL(expected_fraction, get_754_fraction(value));
//    ASSERT_EQUAL(expected_exponent, get_754_exponent(value));
//END_TEST
//
//TEST(test_f22aaaaa)
//    ieee754_t value = 0xf22a'aaaa;
//    uint8_t expected_integer = 1;
//    uint32_t expected_fraction = 0b0101'0101'0101'0101'0101'010;
//    int8_t expected_exponent = 101;
//    ASSERT_TRUE(is_negative(value));
//    ASSERT_EQUAL(expected_integer, get_754_integer(value));
//    ASSERT_EQUAL(expected_fraction, get_754_fraction(value));
//    ASSERT_EQUAL(expected_exponent, get_754_exponent(value));
//END_TEST
//
//TEST(test_000571cc)
//    ieee754_t value = 0x0005'71cc;
//    uint8_t expected_integer = 0;
//    uint32_t expected_fraction = 0b0000'1010'1110'0011'1001'100;
//    int8_t expected_exponent = -126;
//    ASSERT_FALSE(is_negative(value));
//    ASSERT_EQUAL(expected_integer, get_754_integer(value));
//    ASSERT_EQUAL(expected_fraction, get_754_fraction(value));
//    ASSERT_EQUAL(expected_exponent, get_754_exponent(value));
//END_TEST
//
//TEST(test_decode_12_375)
//    ieee754_t value = (union float_converter){.reference_value = 12.375f}.bit_vector;
//    unnormal_t result = decode(value);
//    uint8_t expected_sign = 0;
//    uint64_t expected_integer = 0x1;
//    uint64_t expected_fraction = 0x8c00'0000'0000'0000;
//    int16_t expected_exponent = 3;
//    ASSERT_EQUAL(expected_sign, get_unnormal_sign(result));
//    ASSERT_EQUAL(expected_integer, get_unnormal_integer(result));
//    ASSERT_EQUAL(expected_fraction, get_unnormal_fraction(result));
//    ASSERT_EQUAL(expected_exponent, get_unnormal_exponent(result));
//END_TEST
//
//// 05-normalization.md
//
//TEST(test_encode_12_375)
//    unnormal_t value = unnormal(.sign = 0, .integer = 99, .fraction = 0, .exponent = -3);
//    ieee754_t expected_result = ((union float_converter){.reference_value = 12.375f}).bit_vector;
//    ieee754_t actual_result = encode(value);
//    ASSERT_EQUAL(expected_result, actual_result);
//END_TEST
//
//TEST(test_encode_00055000)
//    unnormal_t value = unnormal(.sign = 0, .integer = 0xA, .fraction = 0xA000'0000'0000'0000, .exponent = -134);
//    ieee754_t expected_result = 0x0005'5000;
//    ieee754_t actual_result = encode(value);
//    ASSERT_EQUAL(expected_result, actual_result);
//END_TEST
//
//TEST(test_recode_12_375)
//    ieee754_t initial_value = ((union float_converter){.reference_value = 12.375f}).bit_vector;
//    unnormal_t intermediate_value = decode(initial_value);
//    ieee754_t final_value = encode(intermediate_value);
//    ASSERT_EQUAL(initial_value, final_value);
//END_TEST
//
//TEST(test_recode_00055000)
//    ieee754_t initial_value = 0x0005'5000;
//    unnormal_t intermediate_value = decode(initial_value);
//    ieee754_t final_value = encode(intermediate_value);
//    ASSERT_EQUAL(initial_value, final_value);
//END_TEST
//
//// 06-multiply-divide.md
//// These test cases were selected to have no observable rounding error, so we'll use ASSERT_EQUAL
//
//TEST(test_multiplicative_identity)
//    float operand1_float = 5.0f;
//    float operand2_float = 1.0f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiplicative_zero)
//    float operand1_float = 5.0f;
//    float operand2_float = 0.0f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiplicative_commutation)
//    float operand1_float = 2.0f;
//    float operand2_float = 3.0f;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t result1 = multiply(operand1_bit_vector, operand2_bit_vector);
//    ieee754_t result2 = multiply(operand2_bit_vector, operand1_bit_vector);
//    ASSERT_EQUAL(result1, result2);
//END_TEST
//
//TEST(test_multiply_integer1)
//    float operand1_float = 75.0f;
//    float operand2_float = 7.0f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_integer2)
//    float operand1_float = 5.0f;
//    float operand2_float = 25.0f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_fraction1)
//    float operand1_float = 0.75f;
//    float operand2_float = 7.0f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_fraction2)
//    float operand1_float = 5.0f;
//    float operand2_float = 0.25f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_negative1)
//    float operand1_float = -5.0f;
//    float operand2_float = 2.0f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_negative2)
//    float operand1_float = 5.0f;
//    float operand2_float = -2.0f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_negative3)
//    float operand1_float = -5.0f;
//    float operand2_float = -2.0f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_negative4)
//    float operand1_float = 5.0f;
//    float operand2_float = -0.0f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_great)
//    float operand1_float = 1.35e25f;
//    float operand2_float = 2.39e11f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_small1)
//    float operand1_float = 1.35e-25f;
//    float operand2_float = 2.39e-11f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_small2)
//    float operand1_float = 1e-30f;
//    float operand2_float = 1e-8f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_great_and_small)
//    float operand1_float = 2e30f;
//    float operand2_float = 2e-30f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_overflow)
//    ieee754_t operand1_bit_vector = 0x7E00'0000;
//    ieee754_t operand2_bit_vector = 0x4100'0000;
//    float operand1_float = ((union float_converter) {.bit_vector = operand1_bit_vector}).reference_value;
//    float operand2_float = ((union float_converter) {.bit_vector = operand2_bit_vector}).reference_value;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_underflow)
//    ieee754_t operand1_bit_vector = 0x3C80'0000;
//    ieee754_t operand2_bit_vector = 0x0000'0020;
//    float operand1_float = ((union float_converter) {.bit_vector = operand1_bit_vector}).reference_value;
//    float operand2_float = ((union float_converter) {.bit_vector = operand2_bit_vector}).reference_value;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_sticky_nan)
//    float operand1_float = NAN;
//    float operand2_float = 1.0f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector & 0x7FFF'FFFF, actual_result & 0x7FFF'FFFF);
//END_TEST
//
//TEST(test_multiply_sticky_infinity)
//    float operand1_float = INFINITY;
//    float operand2_float = 2.0f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_multiply_produce_nan)
//    float operand1_float = INFINITY;
//    float operand2_float = 0.0f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector & 0x7FFF'FFFF, actual_result & 0x7FFF'FFFF);
//END_TEST
//
//TEST(test_divisive_identity)
//    float operand1_float = 5.0f;
//    float operand2_float = 1.0f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_divide_integer)
//    float operand1_float = 75.0f;
//    float operand2_float = 4.0f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_divide_fraction1)
//    float operand1_float = 0.75f;
//    float operand2_float = 4.0f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_divide_fraction2)
//    float operand1_float = 5.0f;
//    float operand2_float = 0.25f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_divide_fraction3)
//    float operand1_float = 0.75f;
//    float operand2_float = 0.25f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_divide_negative1)
//    float operand1_float = -4.0f;
//    float operand2_float = 2.0f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_divide_negative2)
//    float operand1_float = 4.0f;
//    float operand2_float = -2.0f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_divide_negative3)
//    float operand1_float = -4.0f;
//    float operand2_float = -2.0f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_divide_fractional_significand_divisor1)
//    float operand1_float = 30.0f;
//    float operand2_float = 5.0f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_divide_fractional_significand_divisor2)
//    float operand1_float = 25.0f;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = 0x3F20'0000;
//    float operand2_float = ((union float_converter) {.bit_vector = operand2_bit_vector}).reference_value;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_divide_fractional_significand_divisor3)
//    ieee754_t operand1_bit_vector = 0x3F48'0000;
//    float operand1_float = ((union float_converter) {.bit_vector = operand1_bit_vector}).reference_value;
//    float operand2_float = 5.0f;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST    // manually, expected/actual = 0x3E200000; here, actual=0x3F800000
//
//TEST(test_divide_special_cases1)
//    float operand1_float = NAN;
//    float operand2_float = 2.0f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector & 0x7FFF'FFFF, actual_result & 0x7FFF'FFFF);
//END_TEST
//
//TEST(test_divide_special_cases2)
//    float operand1_float = 2.0f;
//    float operand2_float = NAN;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector & 0x7FFF'FFFF, actual_result & 0x7FFF'FFFF);
//END_TEST
//
//TEST(test_divide_special_cases3)
//    float operand1_float = INFINITY;
//    float operand2_float = 2.0f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_divide_special_cases4)
//    float operand1_float = 0.0f;
//    float operand2_float = 2.0f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_divide_special_cases5)
//    float operand1_float = 2.0f;
//    float operand2_float = INFINITY;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_divide_special_cases6)
//    float operand1_float = 2.0f;
//    float operand2_float = 0.0f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_divide_special_cases7)
//    float operand1_float = INFINITY;
//    float operand2_float = INFINITY;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector & 0x7FFF'FFFF, actual_result & 0x7FFF'FFFF);
//END_TEST
//
//TEST(test_divide_special_cases8)
//    float operand1_float = 0.0f;
//    float operand2_float = 0.0f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector & 0x7FFF'FFFF, actual_result & 0x7FFF'FFFF);
//END_TEST
//
//// 07-add-subtract.md
//// These test cases were selected to have no observable rounding error, so we'll use ASSERT_EQUAL
//
//TEST(test_negate_positive)
//    float value_float = 5.0f;
//    ieee754_t value_bit_vector = ((union float_converter) {.reference_value = value_float}).bit_vector;
//    float expected_result_float = -value_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = negate(value_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_negate_negative)
//    float value_float = -5.0f;
//    ieee754_t value_bit_vector = ((union float_converter) {.reference_value = value_float}).bit_vector;
//    float expected_result_float = -value_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = negate(value_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_additive_identity)
//    float operand1_float = 5.0f;
//    float operand2_float = 0.0f;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_additive_commutation)
//    float operand1_float = 2.0f;
//    float operand2_float = 3.0f;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t result1 = add(operand1_bit_vector, operand2_bit_vector);
//    ieee754_t result2 = add(operand2_bit_vector, operand1_bit_vector);
//    ASSERT_EQUAL(result1, result2);
//END_TEST
//
//TEST(test_add_simple)
//    float operand1_float = 2.0f;
//    float operand2_float = 3.0f;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_add_exponent_increases)
//    float operand1_float = 3.0f;
//    float operand2_float = 3.0f;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_add_fractional_operands)
//    float operand1_float = 0.4f;
//    float operand2_float = 0.04f;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_add_negative)
//    float operand1_float = -5.0f;
//    float operand2_float = 2.0f;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_subtraction_simple)
//    float operand1_float = 2.0f;
//    float operand2_float = 5.0f;
//    float expected_result_float = operand1_float - operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = subtract(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_subtraction_negative)
//    float operand1_float = 3.0f;
//    float operand2_float = -3.0f;
//    float expected_result_float = operand1_float - operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = subtract(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_add_great)
//    float operand1_float = 1.65e35f;
//    float operand2_float = 2.39e29f;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_add_small)
//    float operand1_float = 1.65e-39f;
//    float operand2_float = 2.39e-33f;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_add_overflow)
//    ieee754_t operand1_bit_vector = 0x7F7F'FFFF;
//    ieee754_t operand2_bit_vector = 0x7380'0000;
//    float operand1_float = ((union float_converter) {.bit_vector = operand1_bit_vector}).reference_value;
//    float operand2_float = ((union float_converter) {.bit_vector = operand2_bit_vector}).reference_value;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_subtract_underflow)
//    ieee754_t operand1_bit_vector = 0x0100'0000;
//    ieee754_t operand2_bit_vector = 0x00C0'0000;
//    float operand1_float = ((union float_converter) {.bit_vector = operand1_bit_vector}).reference_value;
//    float operand2_float = ((union float_converter) {.bit_vector = operand2_bit_vector}).reference_value;
//    float expected_result_float = operand1_float - operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = subtract(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_subtractive_zero)
//    ieee754_t operand1_bit_vector = 0x0000'0001;
//    ieee754_t operand2_bit_vector = 0x0000'0001;
//    float operand1_float = ((union float_converter) {.bit_vector = operand1_bit_vector}).reference_value;
//    float operand2_float = ((union float_converter) {.bit_vector = operand2_bit_vector}).reference_value;
//    float expected_result_float = operand1_float - operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = subtract(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector & 0x7FFF'FFFF, actual_result & 0x7FFF'FFFF);
//END_TEST
//
//TEST(test_add_sticky_nan)
//    float operand1_float = NAN;
//    float operand2_float = 1.0f;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_subtract_sticky_infinity)
//    float operand1_float = INFINITY;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = 0x0000'0001;
//    float operand2_float = ((union float_converter) {.bit_vector = operand2_bit_vector}).reference_value;
//    float expected_result_float = operand1_float - operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = subtract(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_subtract_produce_nan)
//    float operand1_float = INFINITY;
//    float operand2_float = INFINITY;
//    float expected_result_float = operand1_float - operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = subtract(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector & 0x7FFF'FFFF, actual_result & 0x7FFF'FFFF);
//END_TEST
//
//// 08-rounding.md
//
//TEST(test_round_less_than_halfway_odd)
//    ieee754_t unrounded_number = 0x4000'0001;
//    uint64_t original_fraction = 0x0000'0201'0000'0000;
//    ieee754_t expected_result = 0x4000'0001;
//    ieee754_t actual_result = round_to_nearest_even(unrounded_number, original_fraction);
//    ASSERT_EQUAL(expected_result, actual_result);
//END_TEST
//
//TEST(test_round_less_than_halfway_even)
//    ieee754_t unrounded_number = 0x4000'0000;
//    uint64_t original_fraction = 0x0000'0001'0000'0000;
//    ieee754_t expected_result = 0x4000'0000;
//    ieee754_t actual_result = round_to_nearest_even(unrounded_number, original_fraction);
//    ASSERT_EQUAL(expected_result, actual_result);
//END_TEST
//
//TEST(test_round_more_than_halfway_odd)
//    ieee754_t unrounded_number = 0x4000'0001;
//    uint64_t original_fraction = 0x0000'0301'0000'0000;
//    ieee754_t expected_result = 0x4000'0002;
//    ieee754_t actual_result = round_to_nearest_even(unrounded_number, original_fraction);
//    ASSERT_EQUAL(expected_result, actual_result);
//END_TEST
//
//TEST(test_round_more_than_halfway_even)
//    ieee754_t unrounded_number = 0x4000'0000;
//    uint64_t original_fraction = 0x0000'0101'0000'0000;
//    ieee754_t expected_result = 0x4000'0001;
//    ieee754_t actual_result = round_to_nearest_even(unrounded_number, original_fraction);
//    ASSERT_EQUAL(expected_result, actual_result);
//END_TEST
//
//TEST(test_round_exactly_halfway_down)
//    ieee754_t unrounded_number = 0x4000'0000;
//    uint64_t original_fraction = 0x0000'0100'0000'0000;
//    ieee754_t expected_result = 0x4000'0000;
//    ieee754_t actual_result = round_to_nearest_even(unrounded_number, original_fraction);
//    ASSERT_EQUAL(expected_result, actual_result);
//END_TEST
//
//TEST(test_round_exactly_halfway_up)
//    ieee754_t unrounded_number = 0x4000'0001;
//    uint64_t original_fraction = 0x0000'0300'0000'0000;
//    ieee754_t expected_result = 0x4000'0002;
//    ieee754_t actual_result = round_to_nearest_even(unrounded_number, original_fraction);
//    ASSERT_EQUAL(expected_result, actual_result);
//END_TEST
//
//TEST(test_add_round_less_than_halfway_odd)
//    ieee754_t operand1_bit_vector = 0x4000'0000;
//    ieee754_t operand2_bit_vector = 0x33FF'FFFF;
//    float operand1_float = ((union float_converter) {.bit_vector = operand1_bit_vector}).reference_value;
//    float operand2_float = ((union float_converter) {.bit_vector = operand2_bit_vector}).reference_value;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_add_round_less_than_halfway_even)
//    ieee754_t operand1_bit_vector = 0x4000'0001;
//    ieee754_t operand2_bit_vector = 0x33FF'FFFF;
//    float operand1_float = ((union float_converter) {.bit_vector = operand1_bit_vector}).reference_value;
//    float operand2_float = ((union float_converter) {.bit_vector = operand2_bit_vector}).reference_value;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_add_round_more_than_halfway_odd)
//    ieee754_t operand1_bit_vector = 0x4000'0000;
//    ieee754_t operand2_bit_vector = 0x3400'0001;
//    float operand1_float = ((union float_converter) {.bit_vector = operand1_bit_vector}).reference_value;
//    float operand2_float = ((union float_converter) {.bit_vector = operand2_bit_vector}).reference_value;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_add_round_more_than_halfway_even)
//    ieee754_t operand1_bit_vector = 0x4000'0001;
//    ieee754_t operand2_bit_vector = 0x3400'0001;
//    float operand1_float = ((union float_converter) {.bit_vector = operand1_bit_vector}).reference_value;
//    float operand2_float = ((union float_converter) {.bit_vector = operand2_bit_vector}).reference_value;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_add_round_exactly_halfway_down)
//    ieee754_t operand1_bit_vector = 0x4000'0000;
//    ieee754_t operand2_bit_vector = 0x3400'0000;
//    float operand1_float = ((union float_converter) {.bit_vector = operand1_bit_vector}).reference_value;
//    float operand2_float = ((union float_converter) {.bit_vector = operand2_bit_vector}).reference_value;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_add_round_exactly_halfway_up)
//    ieee754_t operand1_bit_vector = 0x4000'0001;
//    ieee754_t operand2_bit_vector = 0x3400'0000;
//    float operand1_float = ((union float_converter) {.bit_vector = operand1_bit_vector}).reference_value;
//    float operand2_float = ((union float_converter) {.bit_vector = operand2_bit_vector}).reference_value;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//TEST(test_add_round_ripple)
//    ieee754_t operand1_bit_vector = 0x407F'FFFF;
//    ieee754_t operand2_bit_vector = 0x3400'0000;
//    float operand1_float = ((union float_converter) {.bit_vector = operand1_bit_vector}).reference_value;
//    float operand2_float = ((union float_converter) {.bit_vector = operand2_bit_vector}).reference_value;
//    float expected_result_float = operand1_float + operand2_float;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = add(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
//// 09-arbitrary-division.md
//
//TEST(test_divide_round_down)
//    float operand1_float = 1.0f;
//    float operand2_float = 11.0f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector & 0x7FFF'FFFF, actual_result & 0x7FFF'FFFF);
//END_TEST
//
//TEST(test_divide_round_up)
//    float operand1_float = 1.0f;
//    float operand2_float = 3.0f;
//    float expected_result_float = operand1_float / operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = divide(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector & 0x7FFF'FFFF, actual_result & 0x7FFF'FFFF);
//END_TEST
