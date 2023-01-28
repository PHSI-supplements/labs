/*
 * STUDENT: (Type your name here)
 */

/*
 * PointerLab (c) 2021-22 Christopher A. Bohn
 */

/******************************************************************************
 * This program will implement the Pleistocene Petting Zoo's
 * challenge-and-response system.
 ******************************************************************************/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "challenge-response.h"


/*** THE DATA STRUCTURE AND ITS ALGORITHMS ***/

/* Allocates memory for a new node to hold the word, and initializes the
 * node's fields. Returns a pointer to the new node. */
struct node *create_node(const char *word) {
    struct node *new_node = malloc(sizeof(struct node));
    /* WRITE THE REST OF THIS FUNCTION */
    return new_node;
}

/* Inserts new_node into the list after existing_node; that is, new_node
 * becomes existing_node's "next". If existing_node's original "next" is
 * non-NULL, then that will become new_node's "next". */
void insert_after(struct node *existing_node, struct node *new_node) {
    /* WRITE THIS FUNCTION */
}

/* Inserts new_node into the list before existing_node; that is, new_node
 * becomes existing_node's "previous". If existing_node's original "previous"
 * is non-NULL, then that will become new_node's "previous". */
void insert_before(struct node *existing_node, struct node *new_node) {
    /* YOU DO NOT NEED TO WRITE THIS FUNCTION */
}


/*** ALPHABETIZE WORDS ***/

/* Returns a copy of the word that has all uppercase letters replaced
 * with lowercase letters. The original string is unchanged. */
char *word_to_lowercase(const char *word) {
    /* WRITE THIS FUNCTION */
    return NULL;
}

/* Compares two words based on alphabetical order.
 * Returns a negative value if word1 occurs alphabetically before word2.
 * Returns a positive value if word1 occurs alphabetically after word2.
 * Returns 0 if the two words are identical.
 * This function is really just a wrapper around strncmp. */
int compare_words(const char *word1, const char *word2) {
    return strncmp(word1, word2, MAXIMUM_WORD_LENGTH);
}


/*** INSERTING WORDS ***/

/* Determines if the word is already in the list. If it is, then the
 * number of occurrences for that word is incremented. If it isn't, then
 * a new node is created for the word and inserted into the list at the
 * correct alphabetic location. Returns a pointer to the head of the
 * list, which is either the original head or a node containing the word
 * (if the word occurs before the original head's word or if the
 * original head is NULL).
 * NOTE: THIS FUNCTION ASSUMES THAT THE HEAD OF THE LIST IS THE NODE WITH
 * THE ALPHABETICALLY-EARLIEST WORD! */
struct node *insert_word(struct node *head, const char *word) {
    /* WRITE THIS FUNCTION */
    return NULL;
}

/* Given the name of the book file from the user, reads the file
 * line-by-line. Under the assumption that there is exactly one word per
 * line and that all punctuation has been removed, this function builds
 * a doubly-linked list of the words in alphabetical order, keeping
 * track (as part of a node's payload) how many times each word occurs
 * in the file. */
struct node *build_list(const char *filename) {
    /* WRITE THE REST OF THIS FUNCTION */
    return NULL;
}


/*** RESPOND TO A CHALLENGE ***/

/* Given an alphabetically sorted list of words with the number of
 * occurrences of each word, and given the challenge_word, will return
 * the response word based on the following rules:
 * - If the number of occurrences is an even number then the response
 *   word is 2*occurrences-1 *after* challenge_word in the list
 * - If the number of occurrences is an odd number then the response
 *   word is that many places *after* challenge_word in the list
 * - If the challenge_word is fewer than that number of places from
 *   the end of the list, then "wrap around" to the start of the list
 *   and resume counting
 * - If challenge_word is not present in the list, then the response is
 *   "<challenge_word> is not present!" */
char *respond(const struct node *list, const char *challenge_word) {
    /* WRITE THIS FUNCTION */
    return NULL;
}
