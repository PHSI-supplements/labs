/**************************************************************************//**
 *
 * @file unit-tests.c
 *
 * @author (TYPE YOUR NAME HERE)
 *
 * @brief Unit tests for FloatLab.
 *
 ******************************************************************************/

/*
 * FloatLab assignment and starter code (c) 2019-26 Christopher A. Bohn
 * FloatLab solution (c) the above-named student
 */

#include "unit-tests.h"
#include "../src/fpu.h"
#include "../src/unnormal.h"

int main() {
    return run_tests(5);
}

/*****************/
/* TESTS GO HERE */
/*****************/

/*
TEST(test_name_must_be_a_valid_function_name)
    test function body goes here
    available assertions:
        ASSERT_TRUE(expression)
        ASSERT_FALSE(expression)
        ASSERT_EQUAL(expected, actual)
        ASSERT_ALMOST_EQUAL(expected, actual, delta)
        ASSERT_EQUAL_STRINGS(expected, actual)
        ASSERT_EQUAL_MEMORY(expected_ptr, actual_ptr, size_bytes)
    alternatively:
        return true for passing test
        return false for failing test
END_TEST
*/

/* THIS VIOLATES THE ASSIGNMENT CODE'S CONSTRAINTS */
/* BUT YOU MAY USE IT IN YOUR TEST CODE */
union float_converter {
    ieee754_t bit_vector;
    float reference_value;
};

/*                                    *
 * SEE doc/AA-unit-test-discussion.md *
 *                                    */

///* THE FIRST TWO TESTS ARE USEFUL TO DISPLAY EXPECTED/ACTUAL DIFFERENCES AS BIT VECTORS */
//
///* BEFORE YOU IMPLEMENT `round_to_nearest_even()`, YOUR ARITHMETIC FUNCTIONS MIGHT HAVE A ROUNDING ERROR */
//TEST(test_multiply_without_rounding)
//    float operand1_float = 1.3f;
//    float operand2_float = 2.1f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    // ASSERT_EQUAL(expected_result_bit_vector, actual_result);            // THIS MIGHT FAIL DUE TO ROUNDING ERROR
//    ASSERT_ALMOST_EQUAL(expected_result_bit_vector, actual_result, 1);  // THIS WON'T FAIL DUE TO ROUNDING ERROR
//END_TEST
//
///* AFTER YOU IMPLEMENT `round_to_nearest_even()`, YOUR ARITHMETIC FUNCTIONS WON'T HAVE A ROUNDING ERROR */
//TEST(test_multiply_with_rounding)
//    float operand1_float = 1.3f;
//    float operand2_float = 2.1f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t expected_result_bit_vector = ((union float_converter) {.reference_value = expected_result_float}).bit_vector;
//    ieee754_t actual_result = multiply(operand1_bit_vector, operand2_bit_vector);
//    ASSERT_EQUAL(expected_result_bit_vector, actual_result);
//END_TEST
//
///* THE NEXT TWO TESTS WILL DISPLAY EXPECTED/ACTUAL DIFFERENCES AS FLOATS */
//
///* BEFORE YOU IMPLEMENT `round_to_nearest_even()`, YOUR ARITHMETIC FUNCTIONS MIGHT HAVE A ROUNDING ERROR */
//TEST(test_multiply_without_rounding_float)
//    float operand1_float = 1.3f;
//    float operand2_float = 2.1f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t actual_result_bit_vector = multiply(operand1_bit_vector, operand2_bit_vector);
//    float actual_result_float = ((union float_converter) {.bit_vector = actual_result_bit_vector}).reference_value;
//    // float allowable_error = 0.0000001f;                                 // MOST HUMANS WILL EXPRESS THE ALLOWABLE ERROR IN DECIMAL
//    float allowable_error = 0x1.0p-22f;                                 // THE ALLOWABLE ERROR WILL DEPEND ON THE SPECIFIC TEST
//    // ASSERT_EQUAL(expected_result_float, actual_result_float);           // THIS MIGHT FAIL DUE TO ROUNDING ERROR
//    ASSERT_ALMOST_EQUAL(expected_result_float, actual_result_float, allowable_error);
//END_TEST
//
///* AFTER YOU IMPLEMENT `round_to_nearest_even()`, YOUR ARITHMETIC FUNCTIONS WON'T HAVE A ROUNDING ERROR */
//TEST(test_multiply_with_rounding_float)
//    float operand1_float = 1.3f;
//    float operand2_float = 2.1f;
//    float expected_result_float = operand1_float * operand2_float;
//    ieee754_t operand1_bit_vector = ((union float_converter) {.reference_value = operand1_float}).bit_vector;
//    ieee754_t operand2_bit_vector = ((union float_converter) {.reference_value = operand2_float}).bit_vector;
//    ieee754_t actual_result_bit_vector = multiply(operand1_bit_vector, operand2_bit_vector);
//    float actual_result_float = ((union float_converter) {.bit_vector = actual_result_bit_vector}).reference_value;
//    ASSERT_EQUAL(expected_result_float, actual_result_float);
//END_TEST
