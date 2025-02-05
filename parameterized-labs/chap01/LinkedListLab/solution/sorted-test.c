/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file sorted-test.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Functions to test the "challenge/response" application.
 *
 ******************************************************************************/

/*
 * LinkedListLab (c) 2021-25 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "sorted-test.h"
#include "sorted_word_entries.h"

#ifdef NOTIMEOUT
#define timed_test(action) do { action; } while (0);
#else
#define timed_test(action) do { signal(SIGALRM, timeout_handler); alarm(1); action; alarm(0); } while(0);
#endif //NOTIMEOUT

static void timeout_handler(int signum) {
    fprintf(stderr, "[ERROR] Timeout after 10 seconds!\n");
    exit(EXIT_FAILURE);
}

static char *get_input(char *destination, const char *prompt) {
    printf("%s: ", prompt);
    fgets(destination, MAXIMUM_WORD_LENGTH, stdin);
    destination[strlen(destination) - 1] = '\0';    // eliminates the undesired newline character
    return destination;
}

void test_alphabetical_functions(void) {
    char word[MAXIMUM_WORD_LENGTH + 1];
    char word1[MAXIMUM_WORD_LENGTH + 1];
    get_input(word, "Enter the first word");
    word_to_lowercase(word1, word);
    printf("word_to_lowercase(%s) = %s\n", word, word1);
    char word2[MAXIMUM_WORD_LENGTH + 1];
    get_input(word, "Enter the second word");
    word_to_lowercase(word2, word);
    printf("word_to_lowercase(%s) = %s\n", word, word2);
    printf("words_are_equal(%s, %s) = %s\n",
           word1, word2, words_are_equal(word1, word2) ? "true" : "false");
    printf("word1_is_earlier_than_word2(%s, %s) = %s\n",
           word1, word2, word1_is_earlier_than_word2(word1, word2) ? "true" : "false");
    printf("word1_is_later_than_word2(%s, %s) = %s\n",
           word1, word2, word1_is_later_than_word2(word1, word2) ? "true" : "false");
}

void test_insert_word_empty_list(void) {
    printf("Creating an empty list for the test.\n");
    list_t *list = create_list();
    print(list);
    printf("\n");
    char word[MAXIMUM_WORD_LENGTH + 1];
    get_input(word, "Enter the word to be inserted into the list");
    timed_test(list = insert_word(list, word));
    printf("\n");
    print(list);
    destroy_list(list, true);
}

void test_insert_word_singleton_list(void) {
    printf("Creating and populating a singleton list for the test.\n");
    list_t *list = create_list();
    word_entry_t *word_entry = create_word_entry("thud");
    // I'm going to break encapsulation for the benefit of the test...
    word_entry->occurrences = 12;
    append(list, word_entry);
    print(list);
    printf("\n");
    char word[MAXIMUM_WORD_LENGTH + 1];
    get_input(word, "Enter the word to be inserted into the list");
    timed_test(list = insert_word(list, word));
    printf("\n");
    print(list);
    destroy_list(list, true);
}

void test_insert_word_populated_list(void) {
    printf("Creating and populating a list for the test.\n");
    list_t *list = create_list();
    word_entry_t *word_entry = create_word_entry("bar");
    // I'm going to break encapsulation for the benefit of the test...
    word_entry->occurrences = 2;
    append(list, word_entry);
    word_entry = create_word_entry("baz");
    word_entry->occurrences = 3;
    append(list, word_entry);
    word_entry = create_word_entry("foo");
    word_entry->occurrences = 1;
    append(list, word_entry);
    word_entry = create_word_entry("plugh");
    word_entry->occurrences = 6;
    append(list, word_entry);
    word_entry = create_word_entry("quux");
    word_entry->occurrences = 5;
    append(list, word_entry);
    word_entry = create_word_entry("xyzzy");
    word_entry->occurrences = 4;
    append(list, word_entry);
    print(list);
    printf("\n");
    char word[MAXIMUM_WORD_LENGTH + 1];
    get_input(word, "Enter the word to be inserted into the list");
    timed_test(list = insert_word(list, word));
    printf("\n");
    print(list);
    destroy_list(list, true);
}

void test_build_list(void) {
    char input[MAXIMUM_WORD_LENGTH + 1];
    get_input(input, "Enter the name of the book file");
    printf("Building the list.\n");
    list_t *list;
    timed_test(list = build_list(input));
    print(list);
    destroy_list(list, true);
}

void print_table(void) {
//    char input_file[MAXIMUM_WORD_LENGTH + 1];
//    get_input(input_file, "Enter the name of the book file");
//    printf("Building the list.\n");
//    // We're actually building two identical lists
//    // We'll traverse one to get the words, and use the other for the challenge-response
//    // Two lists because we really need two iterators (one for the words, one for the challenge-response)
//    list_t *challenge_list = build_list(input_file);
//    list_t *response_list = build_list(input_file);
//    printf("List built.\n");
//    char table_format[MAXIMUM_WORD_LENGTH + 1];
//    char delimiter;
//    do {
//        get_input(table_format, "Should this be a LaTeX table or a Markdown table? Type your choice");
//        // we'll assume anything starting with L is LaTeX, and anything starting with M is Markdown
//        switch (table_format[0]) {
//            case 'l':
//            case 'L':
//                delimiter = '&';
//                break;
//            case 'm':
//            case 'M':
//                delimiter = '|';
//                break;
//            default:
//                printf("Invalid choice: %s\n", table_format);
//                delimiter = 0;
//        }
//    } while (!delimiter);
//    FILE *file;
//    char output_file[MAXIMUM_WORD_LENGTH + 10];
//    get_input(output_file, "Enter the name of the output file (or stdout)");
//    if (!strcmp(output_file, "stdout")) {
//        file = stdout;
//    } else {
//        file = fopen(output_file, "w");
//    }
//    // table header
//    switch (delimiter) {
//        case '&':   // LaTeX
//            fprintf(file, "\\begin{tabular}{ccc}\n");
//            fprintf(file, "\\textit{challenge word} & \\textit{occurrences} & \\textit{response word} \\\\ \\hline\n");
//            break;
//        case '|':   // Markdown
//            fprintf(file, "| CHALLENGE WORD | OCCURRENCES | RESPONSE WORD |\n");
//            fprintf(file, "|:--------------:|:-----------:|:-------------:|\n");
//            break;
//        default:    // Unreachable
//            fprintf(file, "CHALLENGE WORD %c OCCURRENCES %c RESPONSE WORD\n", delimiter, delimiter);
//            fprintf(file, "-------------- %c ----------- %c -------------\n", delimiter, delimiter);
//    }
//    // table body
//    word_entry_t *challenge_word;
//    char response_word[MAXIMUM_WORD_LENGTH + 1];
//    reset_iterator(challenge_list);
//    do {
//        challenge_word = get_word_entry(challenge_list);
//        if (challenge_word) {
//            respond(response_list, response_word, get_word(challenge_word));
//            if (delimiter == '|')
//                fprintf(file, "%c ", delimiter);
//            fprintf(file, "%s %c %d %c %s",
//                    get_word(challenge_word), delimiter, get_count(challenge_word), delimiter, response_word);
//            switch (delimiter) {
//                case '&':
//                    fprintf(file, " \\\\\n");
//                    break;
//                case '|':
//                    fprintf(file, " %c\n", delimiter);
//                    break;
//                default:
//                    fprintf(file, "\n");
//            }
//        }
//    } while (iterate_forward(challenge_list));
//    // table footer
//    if (delimiter == '&') {
//        fprintf(file, "\\end{tabular}\n");
//    }
//    if (file != stdout) {
//        fclose(file);
//    }
}
