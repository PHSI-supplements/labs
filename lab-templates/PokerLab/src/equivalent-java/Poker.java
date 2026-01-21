/*
 * PokerLab assignment and starter code (c) 2018-26 Christopher A. Bohn
 */

import java.util.Arrays;
import java.util.Random;

/* ************************************************************************//**
 *
 * Methods to populate a standard 52-card deck and to print that deck.
 *      Methods to characterize a poker hand.
 *
 * @author Christopher A. Bohn
 *
 ******************************************************************************/
public class Poker {
    public static Card[] deck = new Card[Card.SIZE_OF_DECK];  // a "deck" of 52 cards
    public static Random randomIntegerGenerator = new Random();

    /**
     * Places the 52 standard {@link Card}s in {@link #deck}.
     *
     * <ul>
     *     <li>There are 52 distinct non-null {@link Card}s in {@link #deck}.</li>
     * </ul>
     */
    public static void populateDeck() {
        /* IF THIS WERE THE C CODE, YOU WOULD ADD CODE TO PLACE THE 52 STANDARD CARDS IN DECK.
           BECAUSE THIS ISN'T THE C CODE, YOU DO NOT NEED TO DO SO UNLESS IT HELPS YOU. */

    }

    /**
     * Prints all 52 cars in the deck, in order.
     */
    public static void printDeck() {
        if (deck[0] == null) {
            populateDeck();
        }
        for (Card card : deck) {
            System.out.println(card);
        }
    }

    /**
     * Sorts an array of {@link Card}s in-place from the least value to the greatest value.
     *
     * <ul>
     *     <li>Postcondition: The subdeck has its initial `Card`s, sorted from the least value to the greatest value.</li>
     * </ul>
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
     * Randomly selects {@code sizeOfHand} {@link Card}s and returns them
     *      sorted from the least value to the greatest value.
     *
     * <ul>
     *     <li>Precondition:  The destination must have space for at least `sizeOfHand` `Card`s.</li>
     *     <li>Postcondition: The destination has `sizeOfHand` `Card`s, sorted from the least value to the greatest value.</li>
     * </ul>
     *
     * @param sizeOfHand the number of {@link Card}s to be placed in the hand
     * @return an array of randomly-selected {@link Card}s, of length {@code sizeOfHand}
     */
    public static Card[] getRandomHand(int sizeOfHand) {
        if (deck[0] == null) {
            populateDeck();
        }
        Card[] hand = new Card[sizeOfHand];
        for (int i = 0; i < sizeOfHand; i++) {
            int selection = randomIntegerGenerator.nextInt(52);
            hand[i] = deck[selection];      // if this were more robust, we'd check for duplicates
        }
        return sort(hand);
    }

    /**
     * Populates an array of {@link Card}s whose indices in {@link #deck}
     *      correspond to the elements in the `indices` argument, sorted from
     *      the least value to the greatest value.
     *
     * <ul>
     *     <li>Precondition:  The destination must have space for at least `sizeOfHand` `Card`s.</li>
     *     <li>Postcondition: The destination has `sizeOfHand` `Card`s, sorted from the least value to the greatest value.</li>
     * </ul>
     *
     * @param indices specifies which {@link Card}s from {@link #deck} are to be
     *               placed in the hand.
     * @return an array containing the specified {@link Card}s from the {@link #deck}
     */
    public static Card[] getSpecifiedHand(int[] indices) {
        if (deck[0] == null) {
            populateDeck();
        }
        Card[] hand = new Card[indices.length];
        for (int i = 0; i < indices.length; i++) {
            int selection = indices[i];
            hand[i] = deck[selection];
        }
        return sort(hand);
    }


    /**
     * Returns {@code true} if the {@link Card}s in {@code hand} have the same
     * value; returns {@code false} otherwise.
     *
     * <ul>
     *     <li>Precondition: {@code hand} must be sorted from the least value to the greatest value.</li>
     *     <li>Note: {@code hand.length} does <i>not</i> need to be 5.</li>
     * </ul>
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains a "pair"
     */
    public static boolean isPair(Card[] hand) {
        int sizeOfHand = hand.length;
        boolean pair = false;
        for (int i = 0; i < sizeOfHand - 1; i++) {
            pair += (hand[i].value == hand[i + 1].value);   // because hand is sorted, a pair must be two adjacent cards
        }
        return (pair != 0);
    }

    /**
     * Returns {@code true} if two of the {@link Card}s in {@code hand} are a
     * pair and two other are also a pair; returns {@code false} otherwise.
     *
     * <ul>
     *     <li>Precondition: {@code hand} must be sorted from the least value to the greatest value.</li>
     *     <li>Note: {@code hand.length} does <i>not</i> need to be 5.</li>
     * </ul>
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains "two pair"
     */
    public static boolean isTwoPair(Card[] hand) {
        /* IF THIS WERE THE C CODE, YOU WOULD WRITE THIS METHOD.
           BECAUSE THIS ISN'T THE C CODE, YOU DO NOT NEED TO DO SO UNLESS IT HELPS YOU. */
        return true;
    }

    /**
     * Returns {@code true} if three of the {@link Card}s in {@code hand} have
     * the same value; returns {@code false} otherwise.
     *
     * <ul>
     *     <li>Precondition: {@code hand} must be sorted from the least value to the greatest value.</li>
     *     <li>Note: {@code hand.length} does <i>not</i> need to be 5.</li>
     * </ul>
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains "three of a kind"
     */
    public static boolean isThreeOfKind(Card[] hand) {
        int sizeOfHand = hand.length;
        boolean trio = false;
        for (int i = 0; i < sizeOfHand - 2; i++) {
            trio = trio || ((hand[i].value == hand[i + 1].value) && (hand[i].value == hand[i + 2].value));
        }
        return trio;
    }

    /**
     * Returns {@code true} if the {@link Card}s have contiguous values; returns
     * {@code false} otherwise.
     *
     * <ul>
     *     <li>Precondition: {@code hand} must be sorted from the least value to the greatest value.</li>
     *     <li>Note: {@code hand.length} does <i>not</i> need to be 5.</li>
     * </ul>
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains a "straight"
     */
    public static boolean isStraight(Card[] hand) {
        int sizeOfHand = hand.length;
        int notStraight = 0;
        for (int i = 0; i < sizeOfHand - 1; i++) {
            notStraight = notStraight + Math.abs(hand[i + 1].value - hand[i].value - 1);
        }
        return (notStraight == 0);
    }

    /**
     * Returns {@code true} if the {@link Card}s all have the same suit; returns
     * {@code false} otherwise.
     *
     * <ul>
     *     <li>Precondition: {@code hand} must be sorted from the least value to the greatest value.</li>
     *     <li>Note: {@code hand.length} does <i>not</i> need to be 5.</li>
     * </ul>
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains a "flush"
     */
    public static boolean isFlush(Card[] hand) {
        int sizeOfHand = hand.length;
        boolean flush = true;
        Card.Suit suit = hand[0].suit;
        for (int i = 1; i < sizeOfHand; i++) {
            flush = flush && (hand[i].suit == suit);
        }
        return flush;
    }

    /**
     * Returns {@code true} if three of the {@link Card}s in {@code hand} are
     * three of a kind and another two are a pair; returns {@code false}
     * otherwise.
     *
     * <ul>
     *     <li>Precondition: {@code hand} must be sorted from the least value to the greatest value.</li>
     *     <li>Note: {@code hand.length} does <i>not</i> need to be 5.</li>
     * </ul>
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains a "full house"
     */
    public static boolean isFullHouse(Card[] hand) {
        int cardsRemaining = hand.length;
        int startOfPartialHand = 0;
        while (cardsRemaining >= 5) {
            /* In C, `partial_hand` is another pointer into the same array (no copying).
             * In Java, `Arrays.copyOfRange()` allocates a new array and copies elements. */
            if (isThreeOfKind(Arrays.copyOfRange(hand, startOfPartialHand, startOfPartialHand + 3))) {
                startOfPartialHand = startOfPartialHand + 3;
                cardsRemaining = cardsRemaining - 3;
                return isPair(Arrays.copyOfRange(hand, startOfPartialHand, startOfPartialHand + cardsRemaining));
            } else if (isPair(Arrays.copyOfRange(hand, startOfPartialHand, startOfPartialHand + 2))) {
                startOfPartialHand = startOfPartialHand + 2;
                cardsRemaining = cardsRemaining - 2;
                return isThreeOfKind(Arrays.copyOfRange(hand, startOfPartialHand, startOfPartialHand + cardsRemaining));
            } else {
                startOfPartialHand = startOfPartialHand + 1;
                cardsRemaining = cardsRemaining - 1;
            }
        }
        return false;
    }


    /**
     * Returns {@code true} if four of the {@link Card}s have the same value;
     * returns {@code false} otherwise.
     *
     * <ul>
     *     <li>Precondition: {@code hand} must be sorted from the least value to the greatest value.</li>
     *     <li>Note: {@code hand.length} does <i>not</i> need to be 5.</li>
     * </ul>
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
     * Returns {@code true} the {@link Card}s in {@code hand} are both a
     * straight and a flush; returns {@code false} otherwise.
     *
     * <ul>
     *     <li>Precondition: {@code hand} must be sorted from the least value to the greatest value.</li>
     *     <li>Note: {@code hand.length} does <i>not</i> need to be 5.</li>
     * </ul>
     *
     * @param hand the {@link Card}s to be assessed
     * @return {@code true} if and only if {@code hand} contains a "straight flush"
     */
    public static boolean isStraightFlush(Card[] hand) {
        return isStraight(hand) && isFlush(hand);
    }

    /**
     * Prints the {@code hand} and characterizes it in the best possible way.
     *
     * <ul>
     *     <li>Precondition: {@code hand} must be sorted from the least value to the greatest value.</li>
     *     <li>Note: {@code hand.length} does <i>not</i> need to be 5.</li>
     * </ul>
     *
     * @param hand the {@link Card}s to be assessed
     */
    public static void characterizeHand(Card[] hand) {
        /* IF THIS WERE THE C CODE, YOU WOULD WRITE THIS METHOD.
           BECAUSE THIS ISN'T THE C CODE, YOU DO NOT NEED TO DO SO UNLESS IT HELPS YOU. */
    }
}
