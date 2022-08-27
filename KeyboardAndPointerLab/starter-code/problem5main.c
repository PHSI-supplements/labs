/*                                                                                                   *
 * DO NOT EDIT THIS FILE EXCEPT TO UNCOMMENT / COMMENT-OUT TEST_LINKED_LIST_FUNCTIONS AND PRINT_LIST *
 *                                                                                                   */

/*
 * PointerLab (c) 2021-22 Christopher A. Bohn
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "challenge-response.h"

/* A utility function to help with debugging.  Traverses the list, printing
 * each node's payload and the next/previous pointers. */
void print_list(const struct node *head) {
    const struct node *current_node;
    current_node = head;
    if (current_node == NULL) {
        printf("Empty list\n");
    } else {
        do {
            printf("NODE %p -- %15s:%d\tprev:%p (%-15s) next:%p (%-15s)\n",
                   current_node, current_node->word, current_node->occurrences,
                   current_node->previous, current_node->previous == NULL ? " " : current_node->previous->word,
                   current_node->next, current_node->next == NULL ? " " : current_node->next->word);
            current_node = current_node->next;
        } while (current_node != head);
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

int main() {
//    test_linked_list_functions();
    const char *filename = get_input("Enter the name of the book file");
    struct node *list = build_list(filename);
//    print_list(list);
    char *challenge_word = get_input("Enter the challenge word");
    printf("Response word: %s\n", respond(list, challenge_word));
    return 0;
}