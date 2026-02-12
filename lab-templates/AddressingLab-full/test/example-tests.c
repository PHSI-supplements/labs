/**************************************************************************//**
 *
 * @file unit-tests.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Example tests for AddressingLab, from the write-up's example test cases.
 *
 * These tests are not sufficient to establish correctness.
 *
 ******************************************************************************/

/*
 * AddressingLab assignment and starter code (c) 2019-26 Christopher A. Bohn
 */

#include <string.h>
#include "unit-tests.h"
#include "../src/caesarcipher.h"

int main() {
    return run_tests(5);
}

/*****************/
/* TESTS GO HERE */
/*****************/

//// 02-caesar-cipher.md
//
//TEST(test_caesar_cipher_with_capitalized_plaintext)
//    char plaintext[] = "ZEBRA";
//    int key = 1;
//    char expected_ciphertext[] = "AFCSB";
//    char actual_ciphertext[MAXIMUM_INPUT_LENGTH];
//    caesar_cipher(actual_ciphertext, plaintext, key);
//    ASSERT_EQUAL_STRINGS(expected_ciphertext, actual_ciphertext);
//END_TEST
//
//// 03-capitalization.md
//
//TEST(test_sentence_to_uppercase)
//    char plaintext[] = "ZebrA";
//    char expected_uppercase_plaintext[] = "ZEBRA";
//    char actual_uppercase_plaintext[MAXIMUM_INPUT_LENGTH];
//    sentence_to_uppercase(actual_uppercase_plaintext, plaintext);
//    ASSERT_EQUAL_STRINGS(expected_uppercase_plaintext, actual_uppercase_plaintext);
//END_TEST
//
//TEST(test_caesar_cipher_with_arbitrary_plaintext)
//    char plaintext[] = "ZebrA";
//    int key = 1;
//    char expected_ciphertext[] = "AFCSB";
//    char uppercase_plaintext[MAXIMUM_INPUT_LENGTH];
//    char actual_ciphertext[MAXIMUM_INPUT_LENGTH];
//    caesar_cipher(actual_ciphertext, sentence_to_uppercase(uppercase_plaintext, plaintext), key);
//    ASSERT_EQUAL_STRINGS(expected_ciphertext, actual_ciphertext);
//END_TEST
//
//// 04-cipher-validation.md
//
//TEST(test_validate_valid_cipher)
//    struct cipher_package package = {
//        .plaintext = "ZEBRA",
//        .ciphertext = "AFCSB",
//        .sentence_length = 5,
//        .key = 1
//    };
//    ASSERT_TRUE(validate_cipher(&package));
//END_TEST
//
//TEST(test_validate_invalid_cipher_sentence_length)
//    struct cipher_package package = {
//            .plaintext = "ZEBRA",
//            .ciphertext = "AFCSB",
//            .sentence_length = 4,
//            .key = 1
//    };
//    ASSERT_FALSE(validate_cipher(&package));
//END_TEST
//
//TEST(test_validate_invalid_cipher_ciphertext)
//    struct cipher_package package = {
//            .plaintext = "ZEBRA",
//            .ciphertext = "ZEBRA",
//            .sentence_length = 5,
//            .key = 1
//    };
//    ASSERT_FALSE(validate_cipher(&package));
//END_TEST
//
//TEST(test_validate_invalid_cipher_key)
//    struct cipher_package package = {
//            .plaintext = "ZEBRA",
//            .ciphertext = "AFCSB",
//            .sentence_length = 5,
//            .key = 2
//    };
//    ASSERT_FALSE(validate_cipher(&package));
//END_TEST
//
//TEST(test_end_to_end)
//    char plaintext[] = "ZebrA";
//    char uppercase_plaintext[] = "ZEBRA";
//    int key = 1;
//    char uppercase_plaintext_buffer[MAXIMUM_INPUT_LENGTH];
//    char ciphertext[MAXIMUM_INPUT_LENGTH];
//        struct cipher_package package = {
//            .plaintext = uppercase_plaintext,
//            .ciphertext = caesar_cipher(ciphertext, sentence_to_uppercase(uppercase_plaintext_buffer, plaintext), key),
//            .sentence_length = (int) strlen(plaintext),
//            .key = key
//    };
//    ASSERT_TRUE(validate_cipher(&package));
//END_TEST
