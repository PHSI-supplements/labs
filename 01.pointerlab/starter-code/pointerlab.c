/*
 * STUDENT: (Type your name here)
 */

/*
 * PointerLab (c) 2021 Christopher A. Bohn
 */

/******************************************************************************
 * This program will implement the Pleistocene Petting Zoo's
 * challenge-and-response system.
 ******************************************************************************/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_WORD_LENGTH 60

char decapitalize(char character);      // linked from problem2.c
int is_even(int value);                 // linked from problem3.c
struct node *create_node(const char *word);
void insert_after(struct node *existing_node, struct node *new_node);
void insert_before(struct node *existing_node, struct node *new_node);
char *word_to_lowercase(const char *word);
int compare_words(const char *word1, const char *word2);
struct node *insert_word(struct node *head, const char *word);
struct node *build_list();
char *respond(const struct node *list, const char *challenge_word);
char *get_input(const char *prompt);


/*** THE DATA STRUCTURE AND ITS ALGORITHMS ***/

struct node {
    char word[MAXIMUM_WORD_LENGTH];
    int occurrences;
    struct node *next;
    struct node *previous;
};

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
    /* WRITE THIS FUNCTION */
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
 * original head is NULL). */
struct node *insert_word(struct node *head, const char *word) {
    /* WRITE THIS FUNCTION */
    return NULL;
}

/* Gets the name of the book file from the user and reads the file
 * line-by-line. Under the assumption that there is exactly one word per
 * line and that all punctuation has been removed, this function builds
 * a doubly-linked list of the words in alphabetical order, keeping
 * track (as part of a node's payload) how many times each word occurs
 * in the file. */
struct node *build_list() {
    const char *filename = get_input("Enter the name of the book file");
    /* WRITE THE REST OF THIS FUNCTION */
    return NULL;
}


/*** RESPOND TO A CHALLENGE ***/

/* Given an alphabetically sorted list of words with the number of
 * occurrences of each word, and given the challenge_word, will return
 * the response word based on the following rules:
 * - If the number of occurrences is an even number then the response
 *   word is that many places *before* challenge_word in the list
 *   - If the challenge_word is fewer than that number of places from
 *     the head of the list, then the response word is the word at the
 *     head of the list
 * - If the number of occurrences is an odd number then the response
 *   word is that many places *after* challenge_word in the list
 *   - If the challenge_word is fewer than that number of places from
 *     the tail of the list, then the response word is the word at the
 *     tail of the list
 * - If challenge_word is not present in the list, then the response is
 *   "<challenge_word> is not present!" */
char *respond(const struct node *list, const char *challenge_word) {
    /* WRITE THIS FUNCTION */
    return NULL;
}


/*** UTILITY FUNCTIONS ***/

/* A utility function to help with debugging.  Traverses the list, printing
 * each node's payload and the next/previous pointers. */
void print_list(const struct node *head) {
    const struct node *current_node;
    current_node = head;
    while (current_node != NULL) {
        printf("NODE %p -- %15s:%d\tprev:%p (%-15s) next:%p (%-15s)\n",
               current_node, current_node->word, current_node->occurrences,
               current_node->previous, current_node->previous == NULL ? " " : current_node->previous->word,
               current_node->next, current_node->next == NULL ? " " : current_node->next->word);
        current_node = current_node->next;
    }
}

/* Constructs short linked list for testing purposes. */
void test_linked_list_functions() {
    char word[MAXIMUM_WORD_LENGTH];
    strncpy(word, "first node", MAXIMUM_WORD_LENGTH);
    struct node *head = create_node(word);
    strncpy(word, "second node", MAXIMUM_WORD_LENGTH);
    struct node *another_node = create_node(word);
    insert_after(head, another_node);
    strncpy(word, "third node", MAXIMUM_WORD_LENGTH);
    another_node = create_node(word);
    insert_after(head->next, another_node);
    strncpy(word, "fourth node", MAXIMUM_WORD_LENGTH);
    another_node = create_node(word);
    insert_after(head, another_node);
    print_list(head);
}

/* Prompts the user and reads the user's input from stdin. */
char *get_input(const char *prompt) {
    char *input = malloc(MAXIMUM_WORD_LENGTH);
    printf("%s: ", prompt);
    fgets(input, MAXIMUM_WORD_LENGTH, stdin);
    input[strlen(input) - 1] = '\0';        // eliminates the undesired newline character
    return input;
}


/*** MAIN ***/

int main() {
//    test_linked_list_functions();
    struct node *list = build_list();
//    print_list(list);
    char *challenge_word = get_input("Enter the challenge word");
    printf("Response word: %s\n", respond(list, challenge_word));
    return 0;
}
