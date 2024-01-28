/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file array_list.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Functions for an array-backed list. Except when memory allocation is
 *      hobbled, these functions serve as functional references for the linked
 *      list functions that students need to write; that is, they have the same
 *      externally-observable behavior.
 *
 ******************************************************************************/

/*
 * LinkedListLab (c) 2021-24 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include <stdio.h>
#include "array_list.h"
#include "hobbled_alloc.h"

static int const MINIMUM_ALLOCATION = 8;

/**
 * Creates an initially-empty array-backed list.
 *
 * Initially, a minimum allocation for the array has been made, but the list's
 * length is 0, and the list's index is equal to the length (i.e., 0) because
 * the iterator points to a blank space
 *
 * @return a pointer to the list
 */
list_t *create_list(void) {
    list_t *list = hobbled_malloc(sizeof(list_t));
    if (list) {
        list->array = hobbled_calloc(MINIMUM_ALLOCATION, sizeof(word_entry_t *));
        if (!list->array) {
            free(list);
            list = NULL;
        } else {
            list->allocation = MINIMUM_ALLOCATION;
            list->length = 0;
            list->index = 0;
        }
    }
    if (!list) {
        fprintf(stderr, "Failed to allocate space for new list. Returning NULL!\n");
    }
    return list;
}

/**
 * Releases any memory held by an array-backed list.
 *
 * Optionally (and recommended), the caller can specify that the word entries in
 * the list should also be freed. If a use case requires that the word entries
 * not be freed, then the application programmer is responsible for eventually
 * calling `delete_word_entry()` for all word entries.
 *
 * @param list the list to be destroyed
 * @param free_word_entries a flag to indicate whether this function should free
 *      the list's word entries.
 */
void destroy_list(list_t *list, bool free_word_entries) {
    if (free_word_entries) {
        for (size_t i = 0; i < list->length; i++) {
            delete_word_entry(list->array[i]);
        }
    }
    free(list->array);
    free(list);
}

/**
 * Resets the array-backed list's iterator to the first word entry (i.e., sets
 * the array's index to 0).
 *
 * @param list the list whose iterator is to be reset
 * @return `true` if the iterator was successfully reset to the first element;
 *      `false` if the list does not have a first element
 */
bool reset_iterator(list_t *list) {
    list->index = 0;
    return (list->length > 0);
}

/**
 * Advances the array-backed list's iterator to the next word entry in the
 * sequence (i.e., increments the array's index).
 *
 * @param list the list whose iterator is to be advanced
 * @return `true` if the iterator was successfully advanced;
 *      `false` the iterator already pointed to the empty space at the
 *      end of the sequence (i.e., the index is equal to the length)
 */
bool iterate_forward(list_t *list) {
    if (list->index == list->length) {
        return false;
    } else {
        list->index++;
        return true;
    }
}

/**
 * Retreats the array-backed list's iterator to the previous word entry in the
 * sequence (i.e., decrements the array's index).
 *
 * @param list the list whose iterator is to be retreated
 * @return `true` if the iterator was successfully retreats;
 *      `false` the iterator already pointed to the first entry in the sequence
 *      (i.e., the index is 0)
 */
bool iterate_backward(list_t *list) {
    if (list->index == 0) {
        return false;
    } else {
        list->index--;
        return true;
    }
}

/**
 * Retrieves the word entry that is pointed to by the list's iterator, or NULL
 * if the iterator points to a blank space. That is, this function retrieves the
 * array-backed list's `array[index]` element.
 * The word entry remains in the list.
 *
 * @param list the list with the desired word entry
 * @return a pointer to the desired word entry
 */
word_entry_t *get_word_entry(list_t const *list) {
    if (list->index == list->length) {
        return NULL;
    } else {
        return list->array[list->index];
    }
}

/**
 * Retrieves the first word entry in the sequence without moving the list's
 * iterator, or NULL if the sequence is empty. That is, this function retrieves
 * the array-backed list's `array[0]` element.
 * The word entry remains in the list, and the iterator remains unchanged.
 *
 * @param list the list with the desired word entry
 * @return a pointer to the first word entry
 */
word_entry_t *get_first_word_entry(list_t const *list) {
    if (list->length == 0) {
        return NULL;
    } else {
        return list->array[0];
    }
}

/**
 * Retrieves the last word entry in the sequence without moving the list's
 * iterator, or NULL if the sequence is empty. That is, this function retrieves
 * the array-backed list's `array[length - 1]` element.
 * The word entry remains in the list, and the iterator remains unchanged.
 *
 * @param list the list with the desired word entry
 * @return a pointer to the last word entry
 */
word_entry_t *get_last_word_entry(list_t const *list) {
    if (list->length == 0) {
        return NULL;
    } else {
        return list->array[list->length - 1];
    }
}

/**
 * Adds a word entry to the end of the sequence without moving the list's
 * iterator. That is, the array-backed list's length increases by one
 * (reallocating a larger array if necessary), and the word entry is placed at
 * `array[length - 1]`.
 *
 * @param list the list to receive the word entry
 * @param word_entry the word entry to be added to the list
 * @return a pointer to the list
 */
list_t *append(list_t *list, word_entry_t *word_entry) {
    size_t index = list->index;
    list->index = list->length;
    list = insert(list, word_entry);
    list->index = index;
    return list;
}

/**
 * Adds a word entry to the sequence at the iterator's current position.
 * The iterator points to the newly-added word entry. That is, the array-backed
 * list's length increases by one (reallocating a larger array if necessary),
 * all elements from `array[index]` through `array[length - 2]` are shifted
 * to `array[index + 1]` through `array[length - 1]`, and the word entry is
 * placed at `array[index]`.
 *
 * @param list the list to receive the word entry
 * @param word_entry the word entry to be added to the list
 * @return a pointer to the list
 */
list_t *insert(list_t *list, word_entry_t *word_entry) {
    // make sure there's room for another element
    if (list->allocation == list->length) {
        void *larger_array = hobbled_realloc(list->array, sizeof(word_entry_t *) * list->allocation * 2);
        if (!larger_array) {
            fprintf(stderr,
                    "Failed to allocate additional space for new element (%s). Aborting insertion!\n",
                    get_word(word_entry));
            return list;
        } else {
            list->array = larger_array;
            list->allocation *= 2;
        }
    }
    // move the elements at `index` and later to the right
    for (size_t i = list->length; i > list->index; i--) {
        list->array[i] = list->array[i - 1];
    }
    list->array[list->index] = word_entry;
    list->length++;
    return list;
}

/**
 * Removes a word entry from the sequence at the iterator's current position.
 * The iterator points to the word entry that followed the removed entry, or
 * to entry at the now at the end of the sequence if the removed entry was at
 * the end. (However, if the resulting list is an empty list, then and only then
 * will the iterator point to a blank space.)
 *
 * That is, the array-backed list's elements at `array[index + 1]` through
 * `array[length - 1]` are shifted to `array[index]` through
 * `array[length - 2]`, and the length is decreased by 1. The index is typically
 * left unchanged; however, if the index is equal to the new length (and the new
 * length is not 0) then the index will decrease by 1.
 *
 * Optionally (and recommended), the caller can specify that the word entry that
 * gets removed should be freed. If a use case requires that the word entry not
 * be freed, then the application programmer is responsible for eventually
 * calling `delete_word_entry()` for the word entry.
 *
 * @param list the list to discard the word entry
 * @param free_word_entry a flag to indicate whether this function should free
 *      the word entry that has been removed from the list
 * @return a pointer to the list
 */
list_t *delete(list_t *list, bool free_word_entry) {
    if (list->index < list->length) {
        if (free_word_entry) {
            word_entry_t *word_entry = list->array[list->index];
            delete_word_entry(word_entry);
        }
        // move the elements at `index`+1 and later to the left
        for (size_t i = list->index + 1; i < list->length; i++) {
            list->array[i - 1] = list->array[i];
        }
        list->length--;
    }
    if (list->index == list->length && list->length > 0) {
        list->index--;
    }
    // free up unneeded space
    if (list->length * 2 > MINIMUM_ALLOCATION && list->length * 2 < list->allocation) {
        void *smaller_array = hobbled_realloc(list->array, sizeof(word_entry_t *) * list->allocation / 2);
        if (!smaller_array) {
            fprintf(stderr, "Failed to reallocate to a smaller array. This is VERY surprising!\n");
            // it may be surprising (if not impossible) but it's not a show-stopper
        } else {
            list->array = smaller_array;
            list->allocation /= 2;
        }
    }
    return list;
}

/**
 * Prints the contents of the array-backed list.
 *
 * Specifically, this function will print the index, length, and number of
 * elements allocated, and it will print the word entry in each position in the
 * array.
 *
 * @param list the list to be printed
 */
void print(list_t *list) {
    char string[MAXIMUM_WORD_LENGTH + 15];
    printf("index: %zu\tlength: %zu (%zu elements allocated)\n", list->index, list->length, list->allocation);
    for (size_t i = 0; i < list->length; i++) {
        printf("[%5zu] ", i);
        fflush(stdout);
        printf("%s\n", word_entry_to_string(string, list->array[i]));
    }
}
