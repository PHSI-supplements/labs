/**************************************************************************//**
 *
 * @file unit-tests.c
 *
 * @author (TYPE YOUR NAME HERE)
 *
 * @brief Unit tests for KeyboardLab.
 *
 ******************************************************************************/

/*
 * KeyboardLab assignment and starter code (c) 2021-26 Christopher A. Bohn
 * KeyboardLab solution (c) the above-named student
 */

#include "unit-tests.h"
#include <stdlib.h>
#include "../src/keyboardlab.h"

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

TEST(test_passing)
    ASSERT_TRUE(true);
END_TEST

//TEST(test_failing)
//    ASSERT_FALSE(true);
//END_TEST

//TEST(test_problem1)
//    char const expected_message[] =
//            {
//#embed "../data/problem1oracle.txt"
//                    , '\0'
//            };
//    int const buffer_length = 3 * sizeof(expected_message);
//    char actual_message[buffer_length];     // VLA
//    generate_email(actual_message, buffer_length);
//    ASSERT_EQUAL_STRINGS(expected_message, actual_message);
//END_TEST
