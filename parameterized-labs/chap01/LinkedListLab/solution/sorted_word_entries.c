/**************************************************************************//**
 *
 * @file sorted_word_entries.c
 *
 * @author (TYPE YOUR NAME HERE)
 * @author (TYPE YOUR PARTNER'S NAME HERE, IF APPLICABLE)
 *
 * @brief Functions for a sorted list of word entries.
 *
 ******************************************************************************/

/*
 * LinkedListLab assignment and starter code (c) 2021-25 Christopher A. Bohn
 * LinkedListLab solution (c) the above-named student(s)
 */

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include "sorted_word_entries.h"


/*                   *
 * ALPHABETIZE WORDS *
 *                   */

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
    char *handle = destination;
    while ((*handle++ = (char) tolower(*word++))) {}
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
    return (word1 && word2 && (strncmp(word1, word2, MAXIMUM_WORD_LENGTH) == 0));
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
    return (word1 && word2 && (strncmp(word1, word2, MAXIMUM_WORD_LENGTH) < 0));
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
    return (word1 && word2 && (strncmp(word1, word2, MAXIMUM_WORD_LENGTH) > 0));
}


/*                *
 * INSERTION SORT *
 *                */


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
    word_entry_t *word_entry = create_word_entry(lowercase_word);
    increment_count(word_entry);    // if create_word_entry() sets count initially to 1 then this isn't necessary

    /* Starting with new word entries at the tail is the more efficient option, especially when working with pre-sorted files */
    iterator_t *iterator = append(list, word_entry);
#ifndef USE_ONLY_PRESORTED_FILES
    while (has_previous(iterator)
           && word1_is_earlier_than_word2(lowercase_word, get_word(get_previous_word_entry(iterator)))) {
        iterator = swap_previous(iterator);
    }
#endif //!USE_ONLY_PRESORTED_FILES
    if (has_previous(iterator)) {
        char const *previous_word = get_word(get_previous_word_entry(iterator));
        if (words_are_equal(lowercase_word, previous_word)) {
            merge_previous(iterator);
        }
    }

    /* Starting with new word entries at the start is inefficient with arraylists (increases execution time by about 50%) */
    /* It's also inefficient for linkedlists with pre-sorted files (O(n) vs O(1)) */
    /* It's probably a wash for linkedlists with unsorted files */
//    iterator_t *iterator = prepend(list, word_entry);
//    while (has_next(iterator) && word1_is_later_than_word2(lowercase_word, get_word(get_next_word_entry(iterator)))) {
//        iterator = swap_next(iterator);
//    }
//    if (has_next(iterator)) {
//        char const *next_word = get_word(get_next_word_entry(iterator));
//        if (words_are_equal(lowercase_word, next_word)) {
//            merge_next(iterator);
//        }
//    }

    return get_list(iterator);
}


/*                *
 * BUILD THE LIST *
 *                */


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
    clock_t start = clock();
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
    clock_t stop = clock();
    printf("List built in %f sec\n", (double) (stop - start) / CLOCKS_PER_SEC);
    return list;
}
