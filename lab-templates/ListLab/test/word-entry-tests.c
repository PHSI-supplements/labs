/**************************************************************************//**
 *
 * @file word-entry-tests.c
 *
 * @author (TYPE YOUR NAME HERE)
 *
 * @brief Unit tests for word entries.
 *
 ******************************************************************************/

/*
 * ListLab assignment and starter code (c) 2021-26 Christopher A. Bohn
 * ListLab solution (c) the above-named student
 */

#include "unit-tests.h"
#include "../src/word-entry.h"

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

//TEST(test_timeout)
//    for (;;) {}
//END_TEST

//TEST(test_create_word_entry)
//    char foo[] = "foo";
//    word_entry_t *actual_word_entry = create_word_entry(foo);
//    ASSERT_TRUE(actual_word_entry != nullptr);
//    // you can compare the fields
//    ASSERT_EQUAL_STRINGS(foo, actual_word_entry->word);
//    ASSERT_EQUAL(0, actual_word_entry->occurrences);
//    // or you can compare the whole struct
//    word_entry_t expected_word_entry = {
//            .word = "foo",
//            .occurrences = 0
//    };
//    ASSERT_EQUAL_MEMORY(&expected_word_entry, actual_word_entry, sizeof(word_entry_t));
//    delete_word_entry(actual_word_entry);
//END_TEST
