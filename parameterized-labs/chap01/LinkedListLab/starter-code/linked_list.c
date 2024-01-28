/**************************************************************************//**
 *
 * @file linked_list.c
 *
 * @author (TYPE YOUR NAME HERE)
 * @author (TYPE YOUR PARTNER'S NAME HERE, IF APPLICABLE)
 *
 * @brief Functions for a linked list.
 *
 ******************************************************************************/

/*
 * LinkedListLab assignment and starter code (c) 2021-24 Christopher A. Bohn
 * LinkedListLab solution (c) the above-named student(s)
 */

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/**
 * Creates an initially-blank `node_t` that has a word entry as its payload.
 *
 * Initially, the `next` and `previous` pointers are NULL.
 *
 * @param word_entry the node's payload
 * @return a pointer to the node
 */
static node_t *create_node(word_entry_t *word_entry) {
    node_t *node = malloc(sizeof(node_t));
    /* INITIALIZE NODE */

    return node;
}

/**
 * Releases any memory held by a `node_t`.
 *
 * Optionally (and recommended), the caller can specify that the node's word
 * entry should be freed. If a use case requires that the word entry not be
 * freed, then the application programmer is responsible for eventually
 * calling `delete_word_entry()` for the word entry.
 *
 * @param word_entry the word entry to be released
 */
static void delete_node(node_t *node, bool free_word_entry) {
    if (free_word_entry) {
        delete_word_entry(node->word_entry);
    }
    free(node);
}

/**
 * Creates an initially-empty linked list.
 *
 * Initially, the head and the tail are NULL (because there are no nodes),
 * and the current node is NULL (because the iterator points to a blank space).
 *
 * @return a pointer to the list
 */
list_t *create_list(void) {
    list_t *word_list = malloc(sizeof(list_t));
    /* INITIALIZE WORD_LIST */

    return word_list;
}

/**
 * Releases any memory held by a linked list.
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
    if (list->tail != NULL) {
        list->tail->next = NULL;    // just in case this is a circular linked list
    }
    node_t *node = list->head;
    while (node != NULL) {
        node_t *next_node = node->next;
        delete_node(node, free_word_entries);
        node = next_node;
    }
}

/**
 * Resets the linked list's iterator to the first word entry (i.e., sets
 * the current node to the head).
 *
 * @param list the list whose iterator is to be reset
 * @return `true` if the iterator was successfully reset to the first element;
 *      `false` if the list does not have a first element
 */
bool reset_iterator(list_t *word_list) {
    /* IMPLEMENT THIS FUNCTION */

    return false;
}

/**
 * Advances the linked list's iterator to the next word entry in the sequence
 * (i.e., follows the current node's `next` pointer).
 *
 * @param list the list whose iterator is to be advanced
 * @return `true` if the iterator was successfully advanced;
 *      `false` the iterator already pointed to the empty space at the
 *      end of the sequence (i.e., the current node points to NULL)
 */
bool iterate_forward(list_t *list) {
    /* IMPLEMENT THIS FUNCTION */

    return false;
}

/**
 * Retreats the linked list's iterator to the previous word entry in the
 * sequence (i.e., follows the current node's `previous` pointer).
 *
 * @param list the list whose iterator is to be retreated
 * @return `true` if the iterator was successfully retreats;
 *      `false` the iterator already pointed to the first entry in the sequence
 *      (i.e., the current node points to the head)
 */
bool iterate_backward(list_t *list) {
    /* IMPLEMENT THIS FUNCTION */

    return false;
}

/**
 * Retrieves the word entry that is pointed to by the list's iterator, or NULL
 * if the iterator points to a blank space. That is, this function retrieves the
 * word entry pointed to by the linked list's current node.
 * The word entry remains in the list.
 *
 * @param list the list with the desired word entry
 * @return a pointer to the desired word entry
 */
word_entry_t *get_word_entry(list_t const *list) {
    /* IMPLEMENT THIS FUNCTION */

    return false;
}

/**
 * Retrieves the first word entry in the sequence without moving the list's
 * iterator, or NULL if the sequence is empty. That is, this function retrieves
 * the word entry pointed to by the linked list's head.
 * The word entry remains in the list, and the iterator remains unchanged.
 *
 * @param list the list with the desired word entry
 * @return a pointer to the first word entry
 */
word_entry_t *get_first_word_entry(list_t const *list) {
    /* IMPLEMENT THIS FUNCTION */

    return false;
}

/**
 * Retrieves the last word entry in the sequence without moving the list's
 * iterator, or NULL if the sequence is empty. That is, this function retrieves
 * the word entry pointed to by the linked list's tail.
 * The word entry remains in the list, and the iterator remains unchanged.
 *
 * @param list the list with the desired word entry
 * @return a pointer to the last word entry
 */
word_entry_t *get_last_word_entry(list_t const *list) {
    /* IMPLEMENT THIS FUNCTION */

    return false;
}

/**
 * Adds a word entry to the end of the sequence without moving the list's
 * iterator. That is, a new node for the word entry is created with its
 * `previous` pointer pointing to the linked list's tail, the tail's `next`
 * pointer is updated to point to the new node, and the new node becomes the
 * linked list's new tail.
 *
 * @param list the list to receive the word entry
 * @param word_entry the word entry to be added to the list
 * @return a pointer to the list
 */
list_t *append(list_t *list, word_entry_t *word_entry) {
    /* IMPLEMENT THIS FUNCTION */

    return list;
}

/**
 * Adds a word entry to the sequence at the iterator's current position.
 * The iterator points to the newly-added word entry. That is, a new node for
 * the word entry is created, various `next` and `previous` pointers are updated
 * such that the new node is positioned between the current node and its
 * previous node, and the new node becomes the linked list's current node.
 *
 * @param list the list to receive the word entry
 * @param word_entry the word entry to be added to the list
 * @return a pointer to the list
 */
list_t *insert(list_t *list, word_entry_t *word_entry) {
    /* IMPLEMENT THIS FUNCTION */

    return list;
}

/**
 * Removes a word entry from the sequence at the iterator's current position.
 * The iterator points to the word entry that followed the removed entry, or
 * to entry at the now at the end of the sequence if the removed entry was at
 * the end. (However, if the resulting list is an empty list, then and only then
 * will the iterator point to a blank space.)
 *
 * That is, the `next` and `previous` pointers at the current node's adjacent
 * nodes will be updated to bypass the current node, the current node's
 * resources will be freed, and the new current node will be
 * <ul>
 * <li> the original current node's next node, typically
 * <li> the original current node's previous node, if the original current node
 *      was the tail (the original current node's previous node must now be the
 *      tail)
 * <li> NULL, if the original current node had been the only node in the linked
 *      list
 * </ul>
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
    /* IMPLEMENT THIS FUNCTION */

    return list;
}

/**
 * Prints the contents of the linked list.
 *
 * Specifically, this function will print the address of the head, current, and
 * tail nodes. It will then print, in order, each node's address and word entry,
 * as well as the addresses held by its `previous` and `next` pointers.
 *
 * @param list the list to be printed
 */
void print(list_t *list) {
    char string[MAXIMUM_WORD_LENGTH + 15];
    printf("head: %p\tcurrent_node: %p\ttail: %p\n", list->head, list->current_node, list->tail);
    node_t *node = list->head;
    if (node != NULL) {
        printf("[%p] **head**\n", list->head);
        do {
            if (node == list->current_node) {
                printf("[%p] **current node**\n", list->current_node);
            }
            printf("[%p] %s\n", node, word_entry_to_string(string, node->word_entry));
            printf("\t\tprevious %-20pnext %p\n", node->previous, node->next);
            node = node->next;
        } while (node != NULL && node->previous != list->tail);
        printf("[%p] **tail**\n", list->tail);
    }
    if (list->current_node == NULL) {
        printf("[--NULL--] **current_node**\n");
    }
}
