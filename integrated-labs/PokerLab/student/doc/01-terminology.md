## Poker Terminology

In case you care not familiar with the game of Poker and/or the cards used to play Poker:

The standard 52-card deck of ["French" playing cards](https://en.wikipedia.org/wiki/Standard_52-card_deck) consists of 52 cards.
The cards are divided into 4 "suits," clubs (♣️), diamonds (♦️), hearts (♥️), and spades (♠️).
Each suit consists of 13 cards: the number cards 2--10, the "face cards" (Jack, Queen, King), and the Ace.
In most card games (including Poker), the Jack is greater in value than the 10, the Queen is greater in value than the Jack, and the King is greater in value than the Queen.
In some games, the Ace is lesser in value than the 2, in other games it is greater in value than the King, and in some games, it can be either.

[Poker](https://en.wikipedia.org/wiki/Poker) is a game of chance and skill played with a standard deck of 52 playing cards, in which players attempt to construct the best ``hand'' they can.
While there are many variations of the game, they all have this in common.
A hand is a set of five cards, and it can be categorized into types of hands, which are ranked according to the statistical likelihood of being able to construct such a hand.
When completed, the code in this assignment will generate a random hand and evaluate what type of hand it is.

### Types of Poker Hands

This list is for context. Information about each type of hand will be repeated in later sections when relevant.

In the game of poker, hands are characterized by the similarities of the cards within.
Traditionally, you characterize the hand by the "best" characterization (that is, the one that is least likely to occur);
for example, a hand that is a three of a kind also contains a pair, but you would only characterize the hand as a three of a kind.
The `is...()` functions in *poker.c* are intentionally simple;
they do not (and should not) check whether there is a better way to characterize the hand.
The types of hands (from most desirable to least desirable) are:

Royal Flush  
: This is an Ace, a King, a Queen, a Jack, and a 10, all the same suit.  
: There is no function in the starter code for a royal flush, nor do you need to write one, since a royal flush is essentially the best-possible straight flush.
  (Note also that a Royal Flush is not possible for this lab, based on our re-definition of a Straight, below.)

Straight Flush  
: This is five cards in a sequence, all the same suit;
  that is, five cards that are both a Straight and a Flush.  
: This characterization is checked by the function `is_straight_flush()`.

Four of a Kind  
: Four cards all have the same value.  
: This characterization is checked by the function `is_four_of_kind()`.

Full House  
: The hand contains a three of a kind and also contains a pair with a different value than that of the other three cards.  
: This characterization is checked by the function `is_full_house()`.

Flush  
: Five cards all the same suit.  
: In the interest of simplicity, for this assignment we changed the definition of a flush to "all cards are of the same suit" (this distinction only matters if the number of cards in the hand is not five).  
: This characterization is checked by the function `is_flush()`.

Straight  
: Five cards in a sequence.  
: In the interest of simplicity, for this assignment we changed the definition of a straight to "all cards are in a sequence" (this distinction only matters if the number of cards in the hand is not five).
  We further re-defined an Ace to be adjacent only to 2 (in traditional poker, an Ace can be adjacent to 2 or to King but not both at the same time).  
: This characterization is checked by the function `is_straight()`.

Three of a Kind  
: Three cards all have the same value.  
: This characterization is checked by the function `is_three_of_kind()`.

Two Pair  
: The hand holds two different pairs.  
: This characterization is checked by the function `is_two_pair()`.
  
Pair  
: Two cards with the same value.  
: This characterization is checked by the function `is_pair()`.

High Card  
: If the hand cannot be better characterized, it is characterized by the greatest-value card in the hand.  
: The starter code does not have a function to check for this since this is the characterization if all the other functions return `0`.

---

|                 |      [⬆️](../README.md)      |       [➡️](02-getting-started.md)        |
|:---------------:|:----------------------------:|:----------------------------------------:|
|                 | [Front Matter](../README.md) | [Getting Started](02-getting-started.md) |
