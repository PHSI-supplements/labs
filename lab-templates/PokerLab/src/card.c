/**************************************************************************//**
 *
 * @file card.c
 *
 * @author (STUDENT -- TYPE YOUR NAME HERE)
 *
 * @brief Functions to populate a card's fields and to create a printable
 *      representation of a card.
 *
 ******************************************************************************/

/*
 * PokerLab assignment and starter code (c) 2018-26 Christopher A. Bohn
 * PokerLab solution (c) the above-named student
 */

#include <stdio.h>
#include "card.h"


/**
 * Initializes a card_t.
 *
 * @param value the new card_t's value
 * @param suit  the new card_t's suit
 * @param destination a pointer to the card_t whose fields will be populated
 * @return the `destination` pointer
 */
card_t *create_card(int value, suit_t suit, card_t *destination) {
    /* ADD CODE HERE TO ASSIGN VALUE AND SUIT TO THE DESTINATION'S FIELDS */

    return destination;
}

/**
 * Returns the printable representation of a card_t.
 *
 * @pre The destination must have at least 21 bytes allocated.
 *
 * @param card a pointer to the card_t to be represented as a string
 * @param destination a pointer to a buffer with at least 21 bytes allocated for
 *      the string
 * @return the `destination` pointer
 */
char *card_to_string(card_t const *card, char *destination) {
    /* ASSIGN `CARD`'S VALUE TO THE `VALUE` VARIABLE */
    int value = -1;
    /* ASSIGN `CARD`'S SUIT TO THE `SUIT` VARIABLE */
    suit_t suit = -1;
    char *value_string;
    char *suit_string;
    if (suit >= 0 && suit < NUMBER_OF_SUITS) {
        suit_string = suit_to_string[suit];
    } else {
        suit_string = "UNKNOWN";
    }
    char buffer[3];
    if ((value < MINIMUM_VALUE) || (value > MAXIMUM_VALUE)) {                       // Illegal values
        value_string = "UNKNOWN";
    } else if ((value >= MINIMUM_NUMBER_VALUE) && (value <= MAXIMUM_NUMBER_VALUE)) {    // Number card
        value_string = buffer;
        /* THE SECOND ARGUMENT NEEDS THE CONVERSION SPECIFIER THAT YOU WOULD USE TO PRINT AN INTEGER */
        sprintf(value_string, "", value);
    } else {                                                                        // Ace or face card
        switch (value) {
            case ACE:
                value_string = "ACE";
                break;
            case JACK:
                value_string = "JACK";
                break;
            case QUEEN:
                value_string = "QUEEN";
                break;
            case KING:
                value_string = "KING";
                break;
            default:
                value_string = "DEADCODE";      // This line is unreachable
        }
    }
    sprintf(destination, "%s of %s", value_string, suit_string);
    return destination;
}
