/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file list.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Function prototypes and forward type declaration for lists.
 *
 ******************************************************************************/

/*
 * LinkedListLab (c) 2021-24 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include "word_entry.h"

/**
 * <p>
 * A generic list for word entries.
 * </p><p>
 * The underlying representation cannot be inferred except by the functions
 * in array_list.c and in linked_list.c When used in array_list.c, the list's
 * definition can be assumed to be that found in array_list.h. When used in
 * linked_list.c, the list's definition can be assumed to be that found in
 * linked_list.h.
 * </p><p>
 * The abstract model for a list is that it has:
 * <ul>
 * <li> A sequence of word entries
 * <li> An iterator that can be used as a handle to some part of the sequence;
 *      the iterator always points to exactly one word entry or to an empty
 *      space at the end of the sequence
 * </ul></p>
 */
typedef struct list_definition list_t;

/**
 * Creates an initially-empty list.
 *
 * @return a pointer to the list
 */
list_t *create_list(void);

/**
 * Releases any memory held by a list.
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
void destroy_list(list_t *list, bool free_word_entries);

/**
 * Resets the list's iterator to the first word entry.
 *
 * @param list the list whose iterator is to be reset
 * @return `true` if the iterator was successfully reset to the first element;
 *      `false` if the list does not have a first element
 */
bool reset_iterator(list_t *list);

/**
 * Advances the list's iterator to the next word entry in the sequence.
 *
 * @param list the list whose iterator is to be advanced
 * @return `true` if the iterator was successfully advanced;
 *      `false` the iterator already pointed to the empty space at the
 *      end of the sequence
 */
bool iterate_forward(list_t *list);

/**
 * Retreats the list's iterator to the previous word entry in the sequence.
 *
 * @param list the list whose iterator is to be retreated
 * @return `true` if the iterator was successfully retreats;
 *      `false` the iterator already pointed to the first entry in the sequence
 */
bool iterate_backward(list_t *list);

/**
 * Retrieves the word entry that is pointed to by the list's iterator, or NULL
 * if the iterator points to a blank space.
 * The word entry remains in the list.
 *
 * @param list the list with the desired word entry
 * @return a pointer to the desired word entry
 */
word_entry_t *get_word_entry(list_t const *list);

/**
 * Retrieves the first word entry in the sequence without moving the list's
 * iterator, or NULL if the sequence is empty.
 * The word entry remains in the list, and the iterator remains unchanged.
 *
 * @param list the list with the desired word entry
 * @return a pointer to the first word entry
 */
word_entry_t *get_first_word_entry(list_t const *list);

/**
 * Retrieves the last word entry in the sequence without moving the list's
 * iterator, or NULL if the sequence is empty.
 * The word entry remains in the list, and the iterator remains unchanged.
 *
 * @param list the list with the desired word entry
 * @return a pointer to the last word entry
 */
word_entry_t *get_last_word_entry(list_t const *list);

/**
 * Adds a word entry to the end of the sequence without moving the list's
 * iterator.
 *
 * @param list the list to receive the word entry
 * @param word_entry the word entry to be added to the list
 * @return a pointer to the list
 */
list_t *append(list_t *list, word_entry_t *word_entry);

/**
 * Adds a word entry to the sequence at the iterator's current position.
 * The iterator points to the newly-added word entry.
 *
 * @param list the list to receive the word entry
 * @param word_entry the word entry to be added to the list
 * @return a pointer to the list
 */
list_t *insert(list_t *list, word_entry_t *word_entry);

/**
 * Removes a word entry from the sequence at the iterator's current position.
 * The iterator points to the word entry that followed the removed entry, or
 * to entry at the now at the end of the sequence if the removed entry was at
 * the end. (However, if the resulting list is an empty list, then and only then
 * will the iterator point to a blank space.)
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
list_t *delete(list_t *list, bool free_word_entry);

/**
 * Prints the contents of the list.
 *
 * @param list the list to be printed
 */
void print(list_t *list);

#endif //LIST_H
