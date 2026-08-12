/**************************************************************************//**
 *
 * @file unit-tests.c
 *
 * @author (TYPE YOUR NAME HERE)
 *
 * @brief Unit tests for PokerLab.
 *
 ******************************************************************************/

/*
 * PokerLab assignment and starter code (c) 2018-26 Christopher A. Bohn
 * PokerLab solution (c) the above-named student
 */

#include "unit-tests.h"
#include "../src/card.h"
#include "../src/poker.h"

int main() {
    return run_tests(5);
}

/*****************/
/* TESTS GO HERE */
/*****************/

void populate_deck(void);
int is_two_pair(card_t const* hand, int size_of_hand);
int is_four_of_kind(card_t const* hand, int size_of_hand);

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