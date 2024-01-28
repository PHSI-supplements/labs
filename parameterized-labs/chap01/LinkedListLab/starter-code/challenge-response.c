/**************************************************************************//**
 *
 * @file challenge-response.c
 *
 * @author (TYPE YOUR NAME HERE)
 * @author (TYPE YOUR PARTNER'S NAME HERE, IF APPLICABLE)
 *
 * @brief Functions for the "challenge/response" application.
 *
 ******************************************************************************/

/*
 * LinkedListLab assignment and starter code (c) 2021-24 Christopher A. Bohn
 * LinkedListLab solution (c) the above-named student(s)
 */

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include "challenge-response.h"

/* ALPHABETIZE WORDS */

/**
 * Makes a copy of a string, except that all uppercase letters in the original
 * word are lowercase in the copy. The original and copy are otherwise
 * identical.
 *
 * @param destination a character array with enough memory allocated to hold a
 *      copy of `word`
 * @param word the word to be copied
 * @return a pointer to `destination`
 */
char *word_to_lowercase(char *destination, char const *word) {
    /* IMPLEMENT THIS FUNCTION */

    return destination;
}

/**
 * Determines whether two strings are identical.
 *
 * @param word1 one of the strings to be compared
 * @param word2 the other sting to be compared
 * @return <code>true</code> if and only if every the two strings have the same
 *      length, and character in `word1` matches the corresponding character in
 *      `word2`
 */
bool words_are_equal(const char *word1, const char *word2) {
    bool are_equal = false;
    /* IMPLEMENT THIS FUNCTION */

    return are_equal;
}

/**
 * Determines whether a string occurs earlier than another string in an
 * alphabetic sort.
 *
 * @param word1 the first string to be compared
 * @param word2 the other sting to be compared
 * @return <code>true</code> if and only if `word1` occurs alphabetically
 * earlier than `word2`
 */
bool word1_is_earlier_than_word2(const char *word1, const char *word2) {
    bool is_earlier = false;
    /* IMPLEMENT THIS FUNCTION */

    return is_earlier;
}

/**
 * Determines whether a string occurs later than another string in an
 * alphabetic sort.
 *
 * @param word1 the first string to be compared
 * @param word2 the other sting to be compared
 * @return <code>true</code> if and only if `word1` occurs alphabetically
 * later than `word2`
 */
bool word1_is_later_than_word2(const char *word1, const char *word2) {
    bool is_later = false;
    /* IMPLEMENT THIS FUNCTION */

    return is_later;
}

/* INSERTION SORT */

/**
 * <p>
 * Places, or updates, a word in an alphabetically-sorted list or word entries.
 * </p><p>
 * If the word is already present in the list, then the number of occurrences
 * in its word entry is incremented. Otherwise, a word entry is created for the
 * word, and the word entry is inserted in the appropriate location in the list
 * such that alphabetic sorting is preserved.
 * </p>
 *
 * @param list the list of alphabetically-sorted words
 * @param word the word to be added or updated
 * @return a pointer to the list
 */
list_t *insert_word(list_t *list, char const *word) {
    assert(list != NULL);
    assert(word != NULL);
    char lowercase_word[MAXIMUM_WORD_LENGTH + 1];
    word_to_lowercase(lowercase_word, word);
    /* IMPLEMENT THIS FUNCTION */

    return list;
}

/* BUILD AND USE THE LIST */

/**
 * Given the name of the book file from the user, reads the file
 * line-by-line. Under the assumption that there is exactly one word per line
 * and that all punctuation has been removed, this function builds a list of the
 * words (converted to lowercase) in alphabetical order, keeping track of how
 * many times each word occurs in the file.
 *
 * @param filename the name of the file that contains the words for the list
 * @return a pointer to the list
 */
list_t *build_list(char const *filename) {
//    clock_t start = clock();
    list_t *list = create_list();
    FILE *book = fopen(filename, "r");
    if (!book) {
        fprintf(stderr, "No such file: %s\n", filename);
        list = NULL;
    } else {
        char word[MAXIMUM_WORD_LENGTH + 1];
        while (fgets(word, MAXIMUM_WORD_LENGTH + 1, book)) {
            word[strlen(word) - 1] = '\0';      // eliminates the undesired newline character
            list = insert_word(list, word);
        }
        fclose(book);
    }
//    clock_t stop = clock();
//    printf("List built in %f sec\n", (double) (stop - start) / CLOCKS_PER_SEC);
    return list;
}

/**
 * Given an alphabetically sorted list of words with the number of occurrences
 * of each word, and given the challenge_word, will return the response word
 * based on the following rules:
 * <ul>
 * <li> If the number of occurrences is an even number then the response word is
 *      that many places *before* `challenge_word` in the list
 * <li> If the number of occurrences is an odd number then the response word is
 *      that many places *after* `challenge_word` in the list
 * <li> If the `challenge_word` is fewer than that number of places from the
 *      start/end of the list, then the response is the word at the start/end of
 *      the list
 * <li> If `challenge_word` is not present in the list, then the response is
 *      "<challenge_word> is not present!"
 * </ul>
 *
 * @param list the list of words
 * @param destination a character array with at least 51 bytes allocated
 * @param challenge_word the word to search for in the list
 * @return the response word, as described above
 */
char *respond(list_t *list, char *destination, char const *challenge_word) {
//    clock_t start = clock();
    reset_iterator(list);
    destination[0] = '\0';
    // no matter how long or short the word is, that '\0' will be overwritten when we have a response
    while (!destination[0]) {
        word_entry_t *word_entry = get_word_entry(list);
        char const *word = get_word(word_entry);
        if (word_entry == NULL || word1_is_earlier_than_word2(challenge_word, word)) {
            // we're at the end of the list, or we've moved past where the word should be
            // we *could* ignore the second condition -- if the word isn't there, we'll eventually get to the end
            sprintf(destination, "%s is not present!", challenge_word);
        } else if (words_are_equal(challenge_word, word)) {
            int displacement = get_count(word_entry);
//            printf("%s has %d occurrences\n", challenge_word, displacement);
            if (displacement % 2 == 0) {
                while (displacement-- > 0 && iterate_forward(list)) {}
                if (get_word_entry(list) == NULL) {     // reached the end of the list
                    iterate_backward(list);
                }
            } else {
                while (displacement-- > 0 && iterate_backward(list)) {}
            }
            strncpy(destination, get_word(get_word_entry(list)), MAXIMUM_WORD_LENGTH);
        } else {
            iterate_forward(list);
        }
    }
//    clock_t stop = clock();
//    printf("Word found in %f sec\n", (double) (stop - start) / CLOCKS_PER_SEC);
    return destination;
}
