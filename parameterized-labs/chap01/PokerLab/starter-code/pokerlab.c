/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file pokerlab.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Driver code for PokerLab.
 *
 ******************************************************************************/

/*
 * PokerLab Assignment and starter code (c) 2018-23 Christopher A. Bohn
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"
#include "poker.h"


void test_card(int value, suit_t suit) {
    card_t *card = malloc(sizeof(card_t));
    card = create_card(value, suit, card);
    char *s = malloc(21);
    printf("%s\n", card_to_string(card, s));
    free(s);
    free(card);
}

int get_value_input(void) {
    int value, result;
    do {
        printf("Enter card value: ");
        fflush(stdout);
        result = scanf("%d", &value);
        if (result == 0) {
            printf("Invalid input: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                putchar(c);
            }
            printf("\n");
        }
    } while (result == 0);
    return value;
}

suit_t get_suit_input(void) {
    printf("Available suits:\n");
    suit_t suit = -1;
    for (int i = 0; i < NUMBER_OF_SUITS; i++) {
        printf("\t%d. %s\n", i + 1, suit_to_string[i]);
    }
    do {
        printf("Select suit (1-%d): ", NUMBER_OF_SUITS);
        fflush(stdout);
        int result = scanf("%d", &suit);
        if (result == 0) {
            printf("Invalid input: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                putchar(c);
            }
            printf("\n");
        } else if (suit <= 0 || suit > NUMBER_OF_SUITS) {
            printf("Invalid option: %d. Select a number between 1 and %d.\n", suit, NUMBER_OF_SUITS);
        } else {
            suit -= 1;
        }
    } while (suit < 0 || suit >= NUMBER_OF_SUITS);
    return suit;
}


int main(void) {
    int const size_of_hand = 5;
    const char index_format_string[] = "%d %d %d %d %d";
    card_t hand[size_of_hand];
    int indices[size_of_hand];
    srand(time(NULL));
    int choice = -1;
    do {
        printf("Options:\n");
        printf("\t0. Quit\n");
        printf("\t1. Print one card\n");
        printf("\t2. Print the full deck of cards\n");
        printf("\t3. Characterize a specific %d-card hand\n", size_of_hand);
        printf("\t4. Characterize a random %d-card hand\n", size_of_hand);
        printf("Select your option: ");
        fflush(stdout);
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                printf("Goodbye\n");
                break;
            case 1:
                test_card(get_value_input(), get_suit_input());
                break;
            case 2:
                print_deck();
                break;
            case 3:
                printf("Enter %d indices (0-%d): ", size_of_hand, NUMBER_OF_SUITS * MAXIMUM_VALUE - 1);
                fflush(stdout);
                int result = scanf(index_format_string, indices, indices + 1, indices + 2, indices + 3, indices + 4);
                if (result != size_of_hand) {
                    printf("Bad input; only %d indices were parsed.\n", result);
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {}   // consume the rest of the input
                } else {
                    characterize_hand(get_specific_hand(hand, indices, size_of_hand), size_of_hand);
                }
                break;
            case 4:
                characterize_hand(get_random_hand(hand, size_of_hand), size_of_hand);
                break;
            default:
                printf("Invalid choice %d. Please select a choice between 0 and 4.\n", choice);
        }
        printf("\n");
    } while (choice);
    return 0;
}