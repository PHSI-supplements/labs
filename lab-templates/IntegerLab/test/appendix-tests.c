/**************************************************************************//**
 *
 * @file unit-tests.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Example tests for IntegerLab, from the write-up's appendix.
 *
 * These tests are not sufficient to establish correctness.
 *
 ******************************************************************************/

/*
 * IntegerLab assignment and starter code (c) 2021-26 Christopher A. Bohn
 */

#include <stdint.h>
#include "unit-tests.h"
#include "../src/alu.h"

int main() {
    return run_tests(5);
}

/*****************/
/* TESTS GO HERE */
/*****************/

//TEST(test_exponentiate)
//    unsigned int exponent = 10;
//    uint32_t expected_result = 1024;
//    uint32_t actual_result = exponentiate(exponent);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_lg)
//    uint32_t power_of_two = 32;
//    unsigned int expected_result = 5;
//    unsigned int actual_result = lg(power_of_two);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_is_negative_when_positive)
//    uint16_t value = 0x2000;
//    bool expected_result = false;
//    bool actual_result = is_negative(value);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_is_negative_when_negative)
//    uint16_t value = 0xA000;
//    bool expected_result = true;
//    bool actual_result = is_negative(value);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_equal_when_equal)
//    uint16_t value1 = 0x3000;
//    uint16_t value2 = 0x3000;
//    bool expected_result = true;
//    bool actual_result = equal(value1, value2);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_equal_when_not_equal)
//    uint16_t value1 = 0x3000;
//    uint16_t value2 = 0x5555;
//    bool expected_result = false;
//    bool actual_result = equal(value1, value2);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_not_equal_when_equal)
//    uint16_t value1 = 0x3000;
//    uint16_t value2 = 0x3000;
//    bool expected_result = false;
//    bool actual_result = not_equal(value1, value2);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_not_equal_when_not_equal)
//    uint16_t value1 = 0x3000;
//    uint16_t value2 = 0x5555;
//    bool expected_result = true;
//    bool actual_result = not_equal(value1, value2);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_logical_not_when_zero)
//    uint32_t value = 0;
//    bool expected_result = true;
//    bool actual_result = logical_not(value);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_logical_not_when_nonzero)
//    uint32_t value = 50;
//    bool expected_result = false;
//    bool actual_result = logical_not(value);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_logical_and)
//    uint32_t value1 = 0;
//    uint32_t value2 = 0;
//    bool expected_result = false;
//    bool actual_result = logical_and(value1, value2);
//    bool test_passes = (expected_result == actual_result);
//    value1 = 50;
//    expected_result = false;
//    actual_result = logical_and(value1, value2);
//    test_passes &= (expected_result == actual_result);
//    value2 = 50;
//    expected_result = true;
//    actual_result = logical_and(value1, value2);
//    test_passes &= (expected_result == actual_result);
//    value1 = 0;
//    expected_result = false;
//    actual_result = logical_and(value1, value2);
//    test_passes &= (expected_result == actual_result);
//    return test_passes;
//END_TEST
//
//TEST(test_logical_or)
//    uint32_t value1 = 0;
//    uint32_t value2 = 0;
//    bool expected_result = false;
//    bool actual_result = logical_or(value1, value2);
//    bool test_passes = (expected_result == actual_result);
//    value1 = 50;
//    expected_result = true;
//    actual_result = logical_or(value1, value2);
//    test_passes &= (expected_result == actual_result);
//    value2 = 50;
//    expected_result = true;
//    actual_result = logical_or(value1, value2);
//    test_passes &= (expected_result == actual_result);
//    value1 = 0;
//    expected_result = true;
//    actual_result = logical_or(value1, value2);
//    test_passes &= (expected_result == actual_result);
//    return test_passes;
//END_TEST
//
//TEST(test_one_bit_full_addition)
//    // Assignment constraint: You may not use arrays as truth tables.
//    // but: You *may* violate the assignment's constraints in unit tests, because these files will not be graded.
//    one_bit_adder_t truth_table[] = {
//            (one_bit_adder_t) { .a = 0, .b = 0, .c_in = 0, .sum = 0, .c_out = 0 },
//            (one_bit_adder_t) { .a = 0, .b = 0, .c_in = 1, .sum = 1, .c_out = 0 },
//            (one_bit_adder_t) { .a = 0, .b = 1, .c_in = 0, .sum = 1, .c_out = 0 },
//            (one_bit_adder_t) { .a = 0, .b = 1, .c_in = 1, .sum = 0, .c_out = 1 },
//            (one_bit_adder_t) { .a = 1, .b = 0, .c_in = 0, .sum = 1, .c_out = 0 },
//            (one_bit_adder_t) { .a = 1, .b = 0, .c_in = 1, .sum = 0, .c_out = 1 },
//            (one_bit_adder_t) { .a = 1, .b = 1, .c_in = 0, .sum = 0, .c_out = 1 },
//            (one_bit_adder_t) { .a = 1, .b = 1, .c_in = 1, .sum = 1, .c_out = 1 },
//    };
//    size_t number_of_entries = sizeof(truth_table) / sizeof(truth_table[0]);
//    bool test_passes = true;
//    for (size_t i = 0; i < number_of_entries; i++) {
//        one_bit_adder_t bits = truth_table[i];
//        bits.sum = 0;
//        bits.c_out = 0;   // make sure the function computes the results
//        one_bit_adder_t result = one_bit_full_addition(bits);
//        test_passes &= (
//                   result.sum   == truth_table[i].sum
//                && result.c_out == truth_table[i].c_out
//        );
//    }
//    return test_passes;
//END_TEST
//
//TEST(test_ripple_carry_addition_simple)
//    uint32_t value1 = 0x12345678;
//    uint32_t value2 = 0x0;
//    uint8_t carry_in = 0;
//    uint32_t expected_result = 0x12345678;
//    uint32_t actual_result = ripple_carry_addition(value1, value2, carry_in);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_ripple_carry_addition_overflows_32_bit_sum)
//    uint32_t value1 = 0x70000000;
//    uint32_t value2 = 0xA0000000;
//    uint8_t carry_in = 0;
//    uint32_t expected_result = 0x10000000;
//    uint32_t actual_result = ripple_carry_addition(value1, value2, carry_in);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_ripple_carry_addition_maximum_sum_without_overflow)
//    uint32_t value1 = 0x70000000;
//    uint32_t value2 = 0x8FFFFFFF;
//    uint8_t carry_in = 0;
//    uint32_t expected_result = 0xFFFFFFFF;
//    uint32_t actual_result = ripple_carry_addition(value1, value2, carry_in);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_ripple_carry_addition_with_initial_carry)
//    uint32_t value1 = 0x12345678;
//    uint32_t value2 = 0x0FEDCBA9;
//    uint8_t carry_in = 1;
//    uint32_t expected_result = 0x22222222;
//    uint32_t actual_result = ripple_carry_addition(value1, value2, carry_in);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_add_normal)
//    uint16_t augend = 0x1234;
//    uint16_t addend = 0x5678;
//    alu_result_t result = add(augend, addend);
//    return result.result == 0x68AC && !result.unsigned_overflow && !result.signed_overflow;
//END_TEST
//
//TEST(test_add_unsigned_overflow)
//    uint16_t augend = 0xE000;
//    uint16_t addend = 0x7000;
//    alu_result_t result = add(augend, addend);
//    return result.result == 0x5000 && result.unsigned_overflow && !result.signed_overflow;
//END_TEST
//
//TEST(test_add_signed_overflow)
//    uint16_t augend = 0x3000;
//    uint16_t addend = 0x7000;
//    alu_result_t result = add(augend, addend);
//    return result.result == 0xA000 && !result.unsigned_overflow && result.signed_overflow;
//END_TEST
//
//TEST(test_subtract_identity_result)
//    uint16_t menuend = 0xD000;
//    uint16_t subtrahend = 0;
//    alu_result_t result = subtract(menuend, subtrahend);
//    return result.result == 0xD000 && !result.unsigned_overflow && !result.signed_overflow;
//END_TEST
//
//TEST(test_subtract_zero_result)
//    uint16_t menuend = 0xD000;
//    uint16_t subtrahend = 0xD000;
//    alu_result_t result = subtract(menuend, subtrahend);
//    return result.result == 0x0000 && !result.unsigned_overflow && !result.signed_overflow;
//END_TEST
//
//TEST(test_subtract_signed_no_overflow)
//    uint16_t menuend = 0xD000;
//    uint16_t subtrahend = 0xA000;
//    alu_result_t result = subtract(menuend, subtrahend);
//    return result.result == 0x3000 && !result.unsigned_overflow && !result.signed_overflow;
//END_TEST
//
//TEST(test_subtract_unsigned_overflow)
//    uint16_t menuend = 0x4000;
//    uint16_t subtrahend = 0xD000;
//    alu_result_t result = subtract(menuend, subtrahend);
//    return result.result == 0x7000 && result.unsigned_overflow && !result.signed_overflow;
//END_TEST
//
//TEST(test_subtract_signed_overflow)
//    uint16_t menuend = 0x9000;
//    uint16_t subtrahend = 0x5000;
//    alu_result_t result = subtract(menuend, subtrahend);
//    return result.result == 0x4000 && !result.unsigned_overflow && result.signed_overflow;
//END_TEST
//
//TEST(test_multiply_by_power_of_two_zero_result)
//    uint16_t value = 15;
//    uint16_t power_of_two = 0x0;
//    uint32_t expected_result = 0;
//    uint32_t actual_result = multiply_by_power_of_two(value, power_of_two);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_multiply_by_power_of_two_identity_result)
//    uint16_t value = 15;
//    uint16_t power_of_two = 0x1;
//    uint32_t expected_result = 15;
//    uint32_t actual_result = multiply_by_power_of_two(value, power_of_two);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_multiply_by_power_of_two_large)
//    uint16_t value = 15;
//    uint16_t power_of_two = 0x200;
//    uint32_t expected_result = 15 * 0x200;
//    uint32_t actual_result = multiply_by_power_of_two(value, power_of_two);
//    return expected_result == actual_result;
//END_TEST
//
//TEST(test_unsigned_multiply_small)
//    uint16_t multiplicand = 9000;
//    uint16_t multiplier = 3;
//    alu_result_t expected = { .result = 27000, .supplemental_result = 0 };
//    alu_result_t actual = unsigned_multiply(multiplicand, multiplier);
//    return expected.result == actual.result && expected.supplemental_result == actual.supplemental_result;
//END_TEST
//
//TEST(test_unsigned_multiply_large)
//    uint16_t multiplicand = 30000;
//    uint16_t multiplier = 3;
//    uint32_t full_product = 30000uL * 3uL;
//    alu_result_t expected = {
//            .result              = (uint16_t)(full_product & 0xFFFF),
//            .supplemental_result = (uint16_t)(full_product >> 16)
//    };
//    alu_result_t actual = unsigned_multiply(multiplicand, multiplier);
//    return expected.result == actual.result && expected.supplemental_result == actual.supplemental_result;
//END_TEST
//
//TEST(test_unsigned_divide_by_zero)
//    uint16_t dividend = 500;
//    uint16_t divisor = 0;
//    alu_result_t expected = { .divide_by_zero = 1 };
//    alu_result_t actual = unsigned_divide(dividend, divisor);
//    return expected.divide_by_zero == actual.divide_by_zero;
//END_TEST
//
//TEST(test_unsigned_divide_exact)
//    uint16_t dividend = 256;
//    uint16_t divisor = 4;
//    alu_result_t expected = { .result = 64, .supplemental_result = 0, .divide_by_zero = 0 };
//    alu_result_t actual = unsigned_divide(dividend, divisor);
//    return expected.result == actual.result
//        && expected.supplemental_result == actual.supplemental_result
//        && expected.divide_by_zero      == actual.divide_by_zero;
//END_TEST
//
//TEST(test_unsigned_divide_non_exact)
//    uint16_t dividend = 500;
//    uint16_t divisor = 16;
//    alu_result_t expected = { .result = 31, .supplemental_result = 4, .divide_by_zero = 0 };
//    alu_result_t actual = unsigned_divide(dividend, divisor);
//    return expected.result              == actual.result
//        && expected.supplemental_result == actual.supplemental_result
//        && expected.divide_by_zero      == actual.divide_by_zero;
//END_TEST
//
//TEST(test_signed_multiply_positive)
//    int16_t multiplicand = 30000;
//    int16_t multiplier = 3;
//    int32_t full_product = (int32_t) multiplicand * (int32_t) multiplier;
//    alu_result_t expected = {
//            .result              = (uint16_t) ( full_product        & 0xFFFF),
//            .supplemental_result = (uint16_t) ((full_product >> 16) & 0xFFFF),
//    };
//    alu_result_t actual = signed_multiply((uint16_t) multiplicand, (uint16_t) multiplier);
//    return expected.result == actual.result && expected.supplemental_result == actual.supplemental_result;
//END_TEST
//
//TEST(test_signed_multiply_negative_times_positive)
//    int16_t multiplicand = -25633;
//    int16_t multiplier = 12;
//    int32_t full_product = (int32_t) multiplicand * (int32_t) multiplier;
//    alu_result_t expected = {
//            .result              = (uint16_t) ( full_product        & 0xFFFF),
//            .supplemental_result = (uint16_t) ((full_product >> 16) & 0xFFFF),
//    };
//    alu_result_t actual = signed_multiply((uint16_t) multiplicand, (uint16_t) multiplier);
//    return expected.result == actual.result && expected.supplemental_result == actual.supplemental_result;
//END_TEST
//
//TEST(test_signed_multiply_positive_times_negative)
//    int16_t multiplicand = 9;
//    int16_t multiplier = -25633;
//    int32_t full_product = (int32_t) multiplicand * (int32_t) multiplier;
//    alu_result_t expected = {
//            .result              = (uint16_t) ( full_product        & 0xFFFF),
//            .supplemental_result = (uint16_t) ((full_product >> 16) & 0xFFFF),
//    };
//    alu_result_t actual = signed_multiply((uint16_t) multiplicand, (uint16_t) multiplier);
//    return expected.result == actual.result && expected.supplemental_result == actual.supplemental_result;
//END_TEST
//
//TEST(test_signed_divide_positive)
//    int16_t dividend = 500;
//    int16_t divisor = 16;
//    alu_result_t expected = { .result = 31, .supplemental_result = 4, .divide_by_zero = 0 };
//    alu_result_t actual = signed_divide((uint16_t) dividend, (uint16_t) divisor);
//    return expected.result == actual.result
//        && expected.supplemental_result == actual.supplemental_result
//        && expected.divide_by_zero      == actual.divide_by_zero;
//END_TEST
//
//TEST(test_signed_divide_negative)
//    int16_t dividend = -24577;
//    int16_t divisor = 0x40;
//    alu_result_t expected = {
//            .result              = (uint16_t) (dividend / divisor),
//            .supplemental_result = (uint16_t) (dividend % divisor),
//            .divide_by_zero      = 0
//    };
//    alu_result_t actual = signed_divide((uint16_t) dividend, (uint16_t) divisor);
//    return expected.result              == actual.result
//        && expected.supplemental_result == actual.supplemental_result
//        && expected.divide_by_zero      == actual.divide_by_zero;
//END_TEST
