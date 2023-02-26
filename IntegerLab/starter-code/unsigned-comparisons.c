/**************************************************************************//**
 *
 * @file unsigned-comparisons.c
 *
 * @author (STUDENT -- TYPE YOUR NAME HERE)
 *
 * @brief Functions that perform unsigned comparisons between integers.
 *
 ******************************************************************************/


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "alu.h"

/**
 * Determines whether the first value is below (unsigned less-than) the second.
 * @param value1 the value on the left side of the inequality comparison
 * @param value2 the value on the right side of the inequality comparison
 * @return 1 if the first argument is strictly less than the second; 0 otherwise
 */
bool below(uint16_t value1, uint16_t value2) {
    return 0;
}

/**
 * Determines whether the first value is above (unsigned greater-than) the second.
 * @param value1 the value on the left side of the inequality comparison
 * @param value2 the value on the right side of the inequality comparison
 * @return 1 if the first argument is strictly greater than the second; 0 otherwise
 */
bool above(uint16_t value1, uint16_t value2) {
    return 0;
}

/*               *
 *  DRIVER CODE  *
 * (do not edit) *
 *               */

uint16_t get_random(uint16_t lower_bound, uint16_t upper_bound) {
    return (uint16_t) (rand() % (upper_bound - lower_bound + 1)) + lower_bound; // NOLINT(cert-msc50-cpp)
}

struct test_case_t {
    char signed_description[32];
    char unsigned_description[32];
    bool expected_signed_result;
    bool actual_signed_result;
    bool expected_unsigned_result;
    bool actual_unsigned_result;
};

void create_test_case(struct test_case_t *test_case, char operator, uint16_t value1, uint16_t value2) {
    sprintf(test_case->signed_description, "%d %c %d", (int16_t) value1, operator, (int16_t) value2);
    sprintf(test_case->unsigned_description, "%u %c %u", value1, operator, value2);
    if (operator == '<') {
        test_case->expected_signed_result = (int16_t) value1 < (int16_t) value2;
        test_case->expected_unsigned_result = value1 < value2;
        test_case->actual_signed_result = less_than(value1, value2);
        test_case->actual_unsigned_result = below(value1, value2);
    } else if (operator == '>') {
        test_case->expected_signed_result = (int16_t) value1 > (int16_t) value2;
        test_case->expected_unsigned_result = value1 > value2;
        test_case->actual_signed_result = greater_than(value1, value2);
        test_case->actual_unsigned_result = above(value1, value2);
    } else {
        fprintf(stderr, "Unrecognized operator: %c\n", operator);
    }
}

int main() {
    srand((unsigned int) time(NULL)); // NOLINT(cert-msc51-cpp)
    uint16_t positive1 = get_random(10, UINT16_MAX / 2 - 20);
    uint16_t positive2 = get_random(positive1 + 1, UINT16_MAX / 2 - 10);
    uint16_t negative1 = get_random(UINT16_MAX / 2 + 10, -20);
    uint16_t negative2 = get_random(negative1, -10);
    char operators[] = {'<', '>'};
    const int NUMBER_OF_OPERATORS = 2;
    const int NUMBER_OF_CASES_PER_OPERATOR = 8;
    const int NUMBER_OF_TEST_CASES = NUMBER_OF_OPERATORS * NUMBER_OF_CASES_PER_OPERATOR;
    struct test_case_t *test_cases = calloc(NUMBER_OF_TEST_CASES, sizeof(struct test_case_t));
    for (int i = 0; i < NUMBER_OF_OPERATORS; i++) {
        struct test_case_t *first_case = test_cases + i * NUMBER_OF_CASES_PER_OPERATOR;
        char operator = operators[i];
        create_test_case(first_case + 0, operator, positive1, positive2);
        create_test_case(first_case + 1, operator, positive2, positive1);
        create_test_case(first_case + 2, operator, positive1, positive1);
        create_test_case(first_case + 3, operator, negative1, negative2);
        create_test_case(first_case + 4, operator, negative2, negative1);
        create_test_case(first_case + 5, operator, negative1, negative1);
        create_test_case(first_case + 6, operator, negative2, positive2);
        create_test_case(first_case + 7, operator, positive2, negative2);
    }
    printf("%-22s%10s%10s\n", "SIGNED COMPARISONS", "EXPECTED", "ACTUAL");
    for (int i = 0; i < NUMBER_OF_TEST_CASES; i++) {
        printf("  %-20s%7d   %7d\n", test_cases[i].signed_description,
               test_cases[i].expected_signed_result, test_cases[i].actual_signed_result);
    }
    printf("\n");
    printf("%-22s%10s%10s\n", "UNSIGNED COMPARISONS", "EXPECTED", "ACTUAL");
    for (int i = 0; i < NUMBER_OF_TEST_CASES; i++) {
        printf("  %-20s%7d   %7d\n", test_cases[i].unsigned_description,
               test_cases[i].expected_unsigned_result, test_cases[i].actual_unsigned_result);
    }
}
