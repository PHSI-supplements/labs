/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file challenge-response.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Functions prototypes for the "challenge/response" application.
 *
 ******************************************************************************/

/*
 * LinkedListLab (c) 2021-24 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef CHALLENGE_RESPONSE_H
#define CHALLENGE_RESPONSE_H

#include <string.h>
#include "list.h"

char *word_to_lowercase(char *destination, const char *word);
bool words_are_equal(const char *word1, const char *word2);
bool word1_is_earlier_than_word2(const char *word1, const char *word2);
bool word1_is_later_than_word2(const char *word1, const char *word2);
list_t *insert_word(list_t *list, char const *word);
list_t *build_list(char const *filename);
char *respond(list_t *list, char *destination, char const *challenge_word);

#endif //CHALLENGE_RESPONSE_H
