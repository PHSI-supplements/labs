/**************************************************************************//**
 *
 * @file unit_tests.c
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

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/keyboardlab.h"

typedef bool (*test_case)(char const **name);
#define TEST(test_name) bool test_name(char const **name) { *name = __FUNCTION__;
#define END_TEST        }


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

TEST(test_failing)
    return false;
END_TEST

TEST(test_problem1)
    *name = __FUNCTION__;
    char const expected_message[] =
            {
#embed "../data/problem1oracle.txt"
                    , '\0'
            };
    int const buffer_length = 3 * sizeof(expected_message);
    char *actual_message = calloc(buffer_length, sizeof(char));
    generate_email(actual_message, buffer_length);
    int is_different;
    char *terminator = strchr(actual_message, '\0');        // strchr will eventually find a NUL character
    if (terminator - actual_message >= buffer_length) {     // does the NUL appear within the actual_message?
        is_different = true;
    } else {
        is_different = strcmp(expected_message, actual_message);
    }
    free(actual_message);
    return !is_different;
END_TEST


/**********************/
/* REGISTER THE TESTS */
/**********************/

static test_case test_cases[] = {
        test_passing,
//        test_failing,
//        test_problem1,
};

constexpr size_t NUMBER_OF_TEST_CASES = sizeof(test_cases) / sizeof(test_cases[0]);


/***************/
/* TEST RUNNER */
/***************/

int main() {
    int exit_code = 0;
    char const *test_name;
    for (size_t i = 0; i < NUMBER_OF_TEST_CASES; i++) {
        if (test_cases[i](&test_name)) {
            printf("PASS: %s\n", test_name);
        } else {
            printf("FAIL: %s\n", test_name);
            exit_code = 1;
        }
    }
    return exit_code;
}