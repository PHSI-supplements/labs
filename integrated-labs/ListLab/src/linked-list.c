/**************************************************************************//**
 *
 * @file linked-list.c
 *
 * @author (TYPE YOUR NAME HERE)
 * @author (TYPE YOUR PARTNER'S NAME HERE, IF APPLICABLE)
 *
 * @brief Functions for a linked list.
 *
 ******************************************************************************/

/*
 * LinkedListLab assignment and starter code (c) 2021-25 Christopher A. Bohn
 * LinkedListLab solution (c) the above-named student(s)
 */

#include <stdio.h>
#include <stdlib.h>
#include "linked-list.h"

char const *const LIST_TYPE = "Linked List";


/*                                        *
 * NODE CREATION, DESTRUCTION             *
 * (not for use outside of linked-list.c) *
 *                                        */


/**
 * @brief Creates an initially-blank `node_t` that has a word entry as its payload.
 *
 * Initially, the `next` and `previous` pointers are `nullptr`.
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
 * @brief Releases any memory held by a `node_t`.
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


/*                       *
 * CREATION, DESTRUCTION *
 *                       */


/**
 * @brief Creates an initially-empty linked list.
 *
 * Initially, the head and the tail are `nullptr` (because there are no nodes),
 * and the current node is `nullptr` (because the iterator points to a blank space).
 *
 * @return a pointer to the list
 */
list_t *create_list(void) {
    list_t *word_list = malloc(sizeof(list_t));
    /* INITIALIZE WORD_LIST */

    return word_list;
}

/**
 * @brief Releases any memory held by a linked list.
 *
 * Optionally (and recommended), the caller can specify that the word entries in
 * the list should also be freed. If a use case requires that the word entries
 * not be freed, then the application programmer is responsible for eventually
 * calling `delete_word_entry()` for all word entries.
 *
 * @warning If the word entry is not freed, and if the the application does not
 * have pointers to the word entries, then the word entries cannot be deleted,
 * causing a memory leak.
 *
 * @param list the list to be destroyed
 * @param free_word_entries a flag to indicate whether this function should free
 *      the list's word entries.
 */
void destroy_list(list_t *list, bool free_word_entries) {
    if (list->tail != nullptr) {
        list->tail->next = nullptr;    // just in case this is a circular linked list
    }
    node_t *node = list->head;
    while (node != nullptr) {
        node_t *next_node = node->next;
        delete_node(node, free_word_entries);
        node = next_node;
    }
    free(list->iterator);
    free(list);
}


/*           *
 * ITERATION *
 *           */


/**
 * @brief Provides an iterator over the elements in the list, invalidating all
 * previous iterators.
 *
 * If the list is empty, the iterator is valid <i>only</i> for inserting a word
 * entry into the empty list; the behavior is undefined for all other uses.
 *
 * @param list the list to be iterated over
 * @return a pointer to an iterator for the list, positioned at the head element
 */
iterator_t *get_iterator(list_t *list) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}

/**
 * Provides the iterator's list, invalidating the iterator.
 *
 * @param iterator
 * @return a pointer to the iterator's list
 */
list_t *get_list(iterator_t *iterator) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}

/**
 * Indicates whether forward iteration has more elements; that is, indicates
 * whether the iterator would remain valid if <code>iterate_next()</code> is called.
 * Specifically, if the current node's `next` pointer is not `nullptr`, then there is a
 * next element.
 *
 * @param iterator the iterator to be examined
 * @return <code>true</code> if forward iteration has more elements;
 *      <code>false</code> if the iterator points to the tail element
 */
bool has_next(iterator_t const *iterator) {
    /* IMPLEMENT THIS FUNCTION */

    return false;
}

/**
 * Indicates whether backwards iteration has more elements; that is, indicates
 * whether the iterator would remain valid if <code>iterate_previous()</code> is called.
 * Specifically, if the current node's `previous` pointer is not `nullptr`, then there is a
 * previous element.
 *
 * @param iterator the iterator to be examined
 * @return <code>true</code> if backwards iteration has more elements;
 *      <code>false</code> if the iterator points to the head element
 */
bool has_previous(iterator_t const *iterator) {
    /* IMPLEMENT THIS FUNCTION */

    return false;
}

/**
 * @brief Advances the linked list's iterator to the next element in the list.
 *
 * Specifically, the current node's `next` pointer is followed.
 *
 * The iterator is invalidated, and the subsequent behavior is undefined, if
 * there is no next element.
 *
 * @param iterator the iterator to be advanced
 * @return a pointer to the iterator
 */
iterator_t *iterate_next(iterator_t *iterator) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}

/**
 * @brief Retreats the iterator to the previous element in the list.
 *
 * Specifically, the current node's `previous` pointer is followed.
 *
 * The iterator is invalidated, and the subsequent behavior is undefined, if
 * there is no previous element.
 *
 * @param iterator the iterator to be retreated
 * @return a pointer to the iterator
 */
iterator_t *iterate_previous(iterator_t *iterator) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}


/*                   *
 * ADDITION, REMOVAL *
 *                   */


/**
 * @brief Adds a word entry to the head of the list and generates an iterator
 * pointing to the new head.
 *
 * Specifically, the old head's `previous` pointer will point to the new node.
 *
 * @param list the list to receive the word entry
 * @param word_entry the word entry to be added to the list
 * @return an iterator to the list, positioned at the newly-added entry
 */
iterator_t *prepend(list_t *list, word_entry_t *word_entry) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}

/**
 * @brief Adds a word entry to the tail of the list and generates an iterator
 * pointing to the new tail.
 *
 * Specifically, the old tail's `next` pointer will point to the new node.
 *
 * @param list the list to receive the word entry
 * @param word_entry the word entry to be added to the list
 * @return an iterator to the list, positioned at the newly-added entry
 */
iterator_t *append(list_t *list, word_entry_t *word_entry) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}

/**
 * Adds a word entry to the list at the iterator's current position,
 * invalidating the iterator.
 *
 * Specifically, a new node will be inserted between the current node
 * and the current node's `previous` node. The three affected nodes'
 * `next` and `previous` pointers will be updated accordingly.
 *
 * @param iterator the iterator pointing to the insertion position
 * @param word_entry the word entry to be added to the list
 * @return a pointer to the list
 */
list_t *insert(iterator_t *iterator, word_entry_t *word_entry) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}

/**
 * @brief Removes the word entry from the list at the iterator's current
 * position, invalidating the iterator.
 *
 * That is, the `next` and `previous` pointers at the current node's adjacent
 * nodes will be updated to bypass the current node, the current node's
 * resources will be freed.
 *
 * Optionally (and recommended), the caller can specify that the word entry that
 * gets removed should be freed. If a use case requires that the word entry not
 * be freed, then the application programmer is responsible for eventually
 * calling `delete_word_entry()` for the word entry.
 *
 * @param iterator the iterator pointing to the element to be removed
 * @param free_word_entry a flag to indicate whether this function should free
 *      the word entry that has been removed from the list
 * @return a pointer to the list
 */
list_t *delete(iterator_t *iterator, bool free_word_entry) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}


/*             *
 * EXAMINATION *
 *             */


/**
 * @brief Retrieves the word entry that is pointed to by the iterator.
 *
 * Specifically, this function retrieves the word entry pointed to by the
 * linked list's current node.
 *
 * The iterator remains valid and unchanged, and the word entry remains in the
 * list.
 *
 * @param iterator the iterator pointing to the word entry
 * @return a pointer to the desired word entry
 */
word_entry_t const *get_word_entry(iterator_t const *iterator) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}

/**
 * @brief Retrieve's the next element's word entry, if `has_next(iterator)`, or
 * `nullptr` otherwise.
 *
 * Specifically, this function retrieves the word entry pointed to by the next node.
 *
 * The iterator remains valid and unchanged, and the word entry remains in the
 * list.
 *
 * @param iterator the iterator pointing to a valid word entry
 * @returna pointer to the next word entry
 */
word_entry_t const *get_next_word_entry(iterator_t const *iterator) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}

/**
 * @brief Retrieve's the previous element's word entry, if
 * `has_previous(iterator)`, or `nullptr` otherwise.
 *
 * Specifically, this function retrieves the word entry pointed to by the previous node.
 *
 * The iterator remains valid and unchanged, and the word entry remains in the
 * list.
 *
 * @param iterator the iterator pointing to a valid word entry
 * @returna pointer to the previous word entry
 */
word_entry_t const *get_previous_word_entry(iterator_t const *iterator) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}


/*                   *
 * SWAPPING, MERGING *
 *                   */


/**
 * @brief Swaps the positions of the element pointed to by the iterator,
 * and its next element.
 *
 * After the operation is complete, the iterator will point to the same element
 * as before, but in its new position.
 *
 * If <code>has_next(iterator)</code> is <code>false</code> then the behavior
 * is undefined.
 *
 * @param iterator the iterator pointing to the first of the two elements to be
 *      swapped, in its new position
 * @return a pointer to the iterator
 */
iterator_t *swap_next(iterator_t *iterator) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}

/**
 * @brief Swaps the positions of the element pointed to by the iterator,
 * and its previous element.
 *
 * After the operation is complete, the iterator will point to the same element
 * as before, but in its new position.
 *
 * If <code>has_previous(iterator)</code> is <code>false</code> then the
 * behavior is undefined.
 *
 * @param iterator the iterator pointing to the latter of the two elements to be
 *      swapped, in its new position
 * @return a pointer to the iterator
 */
iterator_t *swap_previous(iterator_t *iterator) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}

/**
 * @brief Combines the word entry pointed to by the iterator, and its next
 * element, forming a single word entry.
 *
 * The two word entries should have the same word; the behavior is undefined if
 * the words differ. After the operation is complete, the combined word entry's
 * count will be the sum of the two original word entries' counts, and the
 * iterator will point to the combined word entry.
 *
 * If <code>has_next(iterator)</code> is <code>false</code> then the behavior
 * is undefined.
 *
 * @param iterator the iterator pointing to merged element
 * @return a pointer to the iterator
 */
iterator_t *merge_next(iterator_t *iterator) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}

/**
 * @brief Combines the word entry pointed to by the iterator, and its previous
 * element, forming a single word entry.
 *
 * The two word entries should have the same word; the behavior is undefined if
 * the words differ. After the operation is complete, the combined word entry's
 * count will be the sum of the two original word entries' counts, and the
 * iterator will point to the combined word entry.
 *
 * If <code>has_previous(iterator)</code> is <code>false</code> then the behavior
 * is undefined.
 *
 * @param iterator the iterator pointing to merged element
 * @return a pointer to the iterator
 */
iterator_t *merge_previous(iterator_t *iterator) {
    /* IMPLEMENT THIS FUNCTION */

    return nullptr;
}


/*          *
 * PRINTING *
 *          */


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
    printf("head: %p\tcurrent_node: %p\ttail: %p\n", list->head, list->iterator->current_node, list->tail);
    node_t *node = list->head;
    if (node != nullptr) {
        printf("[%p] **head**\n", list->head);
        do {
            if (node == list->iterator->current_node) {
                printf("[%p] **current node**\n", list->iterator->current_node);
            }
            printf("[%p] %s\n", node, word_entry_to_string(string, node->word_entry));
            printf("\t\tprevious %-20pnext %p\n", node->previous, node->next);
            node = node->next;
        } while (node != nullptr && node->previous != list->tail);
        printf("[%p] **tail**\n", list->tail);
    }
    if (list->iterator->current_node == nullptr) {
        printf("[--nullptr--] **current_node**\n");
    }
}
