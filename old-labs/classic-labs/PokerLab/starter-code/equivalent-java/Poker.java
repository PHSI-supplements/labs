/*
 * PokerLab (c) 2018-21 Christopher A. Bohn
 */

import java.util.Arrays;
import java.util.Random;

/**
 * This simple program should populate a standard 52-card deck and then
 * randomly select five cards from the deck.  It will then print the
 * poker hand and report the best way it can be characterized (flush, full
 * house, one pair, high card, etc.)
 */
public class Poker {
    public static Card[] deck = new Card[52];  // a "deck" of 52 cards
    public static Random randomIntegerGenerator;

    /**
     * Places the 52 standard {@link Card}s in {@link #deck}.
     */
    public static void populateDeck() {
        /* IF THIS WERE THE C CODE, YOU WOULD ADD CODE TO PLACE THE 52 STANDARD CARDS IN DECK.
           BECAUSE THIS ISN'T THE C CODE, YOU DO NOT NEED TO DO SO UNLESS IT HELPS YOU. */
    }

    /**
     * Sorts an array of {@link Card}s in-place from least value to greatest value.
     *
     * @param subdeck the {@link Card}s to be sorted; it might not be the full deck
     * @return the sorted array of {@link Card}s, in the same array passed as {@code subdeck}
     */
    public static Card[] sort(Card[] subdeck) {
        /* If this were a real Java application, we'd use this code to sort the array:
           Arrays.sort(subdeck, Comparator.comparingInt(c -> c.value));
           But instead we'll use the same Bubble Sort that we see in the C code, for comparison. */
        int size = subdeck.length;
        Card temporaryCard;
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (subdeck[i].value > subdeck[j].value) {
                    temporaryCard = subdeck[i];
                    subdeck[i] = subdeck[j];
                    subdeck[j] = temporaryCard;
                }
            }
        }
        return subdeck;
    }

    /**
     * Randomly selects {@code sizeOfHand} cards and returns them.
     *
     * @param sizeOfHand the number of {@link Card}s to be placed in the hand
     * @return an array of randomly-selected {@link Card}s, of length {@code sizeOfHand}
     */
    public static Card[] getHand(int sizeOfHand) {
        Card[] emptyHand = new Card[sizeOfHand];
        int selection;
        for (int i = 0; i < sizeOfHand; i++) {
            selection = randomIntegerGenerator.nextInt(52);
            emptyHand[i] = deck[selection];     // if this were more robust, we'd check for duplicates
        }
        return sort(emptyHand);
    }

    /**
     * Returns {@code true} if the {@link Card}s in {@code hand} have the same value; returns {@code false} otherwise.
     * {@code hand} must be sorted from least value to greatest value.
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains a "pair"
     */
    public static boolean isPair(Card[] hand) {
        int sizeOfHand = hand.length;
        boolean pair = false;
        for (int i = 0; i < sizeOfHand - 1; i++) {
            pair = pair || (hand[i].value == hand[i + 1].value);    // because hand is sorted, a pair must be two
        }                                                           // adjacent cards
        return pair;
    }

    /**
     * Returns {@code true} if two of the {@link Card}s in {@code hand} are a pair and two other are also a pair;
     * returns {@code false} otherwise.
     * {@code hand} must be sorted from least value to greatest value.
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains "two pair"
     */
    public static boolean isTwoPair(Card[] hand) {
        int sizeOfHand = hand.length;
        int numberOfPairs = 0;
        Card[] partialHand;
        int i = 0;
        while (i < sizeOfHand - 1) {
            partialHand = Arrays.copyOfRange(hand, i, i + 2);   /* THIS IS MAKES A COPY OF PART OF THE ARRAY.
                                                                       THE C CODE DOES NOT MAKE A COPY BUT INSTEAD
                                                                       ALIASES PART OF THE EXISTING ARRAY. */
            if (isPair(partialHand)) {
                numberOfPairs++;
                i += 2;
            } else {
                i++;
            }
        }
        return (numberOfPairs == 2);
    }

    /**
     * Returns {@code true} if three of the {@link Card}s in {@code hand} have the same value; returns {@code false}
     * otherwise.
     * {@code hand} must be sorted from least value to greatest value.
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains "three of a kind"
     */
    public static boolean isThreeOfKind(Card[] hand) {
        /* IF THIS WERE THE C CODE, YOU WOULD WRITE THIS METHOD.
           BECAUSE THIS ISN'T THE C CODE, YOU DO NOT NEED TO DO SO UNLESS IT HELPS YOU. */
        return true;
    }

    /**
     * Returns {@code true} if the {@link Card}s have contiguous values; returns {@code false} otherwise.
     * {@code hand} must be sorted from least value to greatest value.
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains a "straight"
     */
    public static boolean isStraight(Card[] hand) {
        int sizeOfHand = hand.length;
        int not_straight = 0;
        for (int i = 0; i < sizeOfHand - 1; i++) {
            not_straight = not_straight + Math.abs(hand[i + 1].value - hand[i].value - 1);
        }
        return (not_straight == 0);
    }

    /**
     * Returns {@code true} if the {@link Card}s all have the same suit; returns {@code false} otherwise.
     * {@code hand} must be sorted from least value to greatest value.
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains a "flush"
     */
    public static boolean isFlush(Card[] hand) {
        int sizeOfHand = hand.length;
        boolean flush = true;
        Card.Suits suit = hand[0].suit;
        for (int i = 1; i < sizeOfHand; i++) {
            flush = flush && (hand[i].suit == suit);
        }
        return flush;
    }

    /**
     * Returns {@code true} if three of the {@link Card}s in {@code hand} are three of a kind and another two are a
     * pair; returns {@code false} otherwise.
     * {@code hand} must be sorted from least value to greatest value.
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains a "flush"
     */
    public static boolean isFullHouse(Card[] hand) {
        /* IF THIS WERE THE C CODE, YOU WOULD WRITE THIS METHOD.
           BECAUSE THIS ISN'T THE C CODE, YOU DO NOT NEED TO DO SO UNLESS IT HELPS YOU. */
        return true;
    }

    /**
     * Returns {@code true} if four of the {@link Card}s have the same value; returns {@code false} otherwise.
     * {@code hand} must be sorted from least value to greatest value.
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains "four of a kind"
     */
    public static boolean isFourOfKind(Card[] hand) {
        /* IF THIS WERE THE C CODE, YOU WOULD WRITE THIS METHOD.
           BECAUSE THIS ISN'T THE C CODE, YOU DO NOT NEED TO DO SO UNLESS IT HELPS YOU. */
        return true;
    }

    /**
     * Returns {@code true} the {@link Card}s in {@code hand} are both a straight and a flush; returns {@code false}
     * otherwise.
     * {@code hand} must be sorted from least value to greatest value.
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains "four of a kind"
     */
    public static boolean isStraightFlush(Card[] hand) {
        return isStraight(hand) && isFlush(hand);
    }

    public static void main(String[] args) {
        randomIntegerGenerator = new Random();
        populateDeck();
        int sizeOfHand = 5;
        /* IF THIS WERE THE C CODE, YOU WOULD ADD WHATEVER CODE HERE YOU NEED.
           BECAUSE THIS ISN'T THE C CODE, YOU DO NOT NEED TO DO SO UNLESS IT HELPS YOU. */

    }
}
