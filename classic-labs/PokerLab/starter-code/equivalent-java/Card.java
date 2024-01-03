/*
 * PokerLab (c) 2018-21 Christopher A. Bohn
 */

/**
 * This source code defines a card and provides a
 * couple of operations for cards.
 */
public class Card {
    public enum Suits {CLUBS, DIAMONDS, HEARTS, SPADES}

    public int value;
    public Suits suit;

    /**
     * Assigns the provided values to a blank card, making it no longer blank.
     * Returns the no-longer-blank card.
     *
     * @param value the new card's value
     * @param suit  the new card's suit
     */
    public Card(int value, Suits suit) {
        this.value = value;
        this.suit = suit;
    }

    /**
     * Returns the printable representation of a Card.
     *
     * @return the printable representation of this Card
     */
    public String toString() {
        String valueString;
        String suitsString = suit.toString();
        if (value < 1 || value > 13) {              // Illegal values
            valueString = "UNKNOWN";
        } else if ((value > 1) && (value < 11)) {   // Number card
            valueString = Integer.toString(value);
        } else {                                    // Ace or face card
            switch (value) {
                case 1:
                    valueString = "ACE";
                    break;
                case 11:
                    valueString = "JACK";
                    break;
                case 12:
                    valueString = "QUEEN";
                    break;
                case 13:
                    valueString = "KING";
                    break;
                default:
                    valueString = "DEADCODE";       // This line is unreachable
            }
        }
        String displayString = valueString + " of " + suitsString;
        return displayString;
    }

    public static void main(String... arguments) {
        Card c = new Card(3, Suits.HEARTS);
        System.out.println(c);
    }
}
