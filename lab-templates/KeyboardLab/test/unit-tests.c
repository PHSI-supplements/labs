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
    return true for passing test
    return false for failing test
END_TEST
*/

TEST(test_passing)
    return true;
END_TEST

//TEST(test_failing)
//    return false;
//END_TEST

//TEST(test_problem1)
//    char const expected_message[] =
//            {
//#embed "../data/problem1oracle.txt"
//                    , '\0'
//            };
//    int const buffer_length = 3 * sizeof(expected_message);
//    char *actual_message = calloc(buffer_length, sizeof(char));
//    generate_email(actual_message, buffer_length);
//    int is_different;
//    char *terminator = strchr(actual_message, '\0');        // strchr will eventually find a NUL character
//    if (terminator - actual_message >= buffer_length) {     // does the NUL appear within the actual_message?
//        is_different = true;
//    } else {
//        is_different = strcmp(expected_message, actual_message);
//    }
//    free(actual_message);
//    return !is_different;
//END_TEST
