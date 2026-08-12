/**************************************************************************/ /**
 *
 * @file unit-tests.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Example tests for PokerLab, from the write-up's example test cases.
 *
 * These tests are not sufficient to establish correctness.
 *
 ******************************************************************************/

/*
 * PokerLab assignment and starter code (c) 2018-26 Christopher A. Bohn
 */

#include "unit-tests.h"
#include "../src/card.h"
#include "../src/poker.h"
#include <stdint.h>

int main() {
    return run_tests(5);
}

/*****************/
/* TESTS GO HERE */
/*****************/

void populate_deck(void);
int is_two_pair(card_t const* hand, int size_of_hand);
int is_four_of_kind(card_t const* hand, int size_of_hand);

// TEST(test_create_card)
//     card_t expected_card = {.suit = HEARTS, .value = 9};
//     card_t actual_card;
//     create_card(9, HEARTS, &actual_card);
//     ASSERT_EQUAL_MEMORY(&expected_card, &actual_card, sizeof(card_t));
// END_TEST
//
// TEST(test_populate_deck)
//     uint16_t suit_bitsets[] = {0xC001, 0xC001, 0xC001, 0xC001};
//     populate_deck();
//     for (int i = 0; i < SIZE_OF_DECK; i++) {
//         extern card_t deck[];
//         card_t card = deck[i];
//         suit_bitsets[card.suit] |= 1 << card.value;
//     }
//     ASSERT_FALSE((~(suit_bitsets[0] & suit_bitsets[1] & suit_bitsets[2] & suit_bitsets[3])) & 0xFFFF);
// END_TEST
//
// TEST(test_is_four_of_kind)
//     card_t test_hand[] = {
//         {.suit = CLUBS, .value = 2},
//         {.suit = DIAMONDS, .value = 2},
//         {.suit = SPADES, .value = 2},
//         {.suit = HEARTS, .value = 2},
//         {.suit = CLUBS, .value = 6},
//     };
//     ASSERT_TRUE(is_four_of_kind(test_hand, sizeof(test_hand)/sizeof(test_hand[0])));
// END_TEST
//
// TEST(test_is_not_four_of_kind)
//     card_t test_hand[] = {
//         {.suit = CLUBS, .value = 2},
//         {.suit = DIAMONDS, .value = 3},
//         {.suit = SPADES, .value = 4},
//         {.suit = HEARTS, .value = 5},
//         {.suit = CLUBS, .value = 6},
//     };
//     ASSERT_FALSE(is_four_of_kind(test_hand, sizeof(test_hand)/sizeof(test_hand[0])));
// END_TEST
//
// TEST(test_is_two_pair)
//     card_t test_hand[] = {
//         {.suit = CLUBS, .value = 2},
//         {.suit = DIAMONDS, .value = 2},
//         {.suit = SPADES, .value = 4},
//         {.suit = HEARTS, .value = 5},
//         {.suit = CLUBS, .value = 5},
//     };
//     ASSERT_TRUE(is_two_pair(test_hand, sizeof(test_hand)/sizeof(test_hand[0])));
// END_TEST
//
// TEST(test_is_not_two_pair)
//     card_t test_hand[] = {
//         {.suit = CLUBS, .value = 2},
//         {.suit = DIAMONDS, .value = 3},
//         {.suit = SPADES, .value = 4},
//         {.suit = HEARTS, .value = 5},
//         {.suit = CLUBS, .value = 6},
//     };
//     ASSERT_FALSE(is_two_pair(test_hand, sizeof(test_hand)/sizeof(test_hand[0])));
// END_TEST
