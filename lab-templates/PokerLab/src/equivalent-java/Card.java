/*
 * PokerLab assignment and starter code (c) 2018-23 Christopher A. Bohn
 */

/* ************************************************************************//**
 *
 * Methods to populate a card's fields and to create a printable
 * representation of a card.
 *
 * @author Christopher A. Bohn
 *
 ******************************************************************************/
public class Card {

    public static final int MINIMUM_FACE_VALUE = 2;
    public static final int MAXIMUM_FACE_VALUE = 10;
    public static final int MINIMUM_VALUE = MINIMUM_FACE_VALUE - 1;
    public static final int MAXIMUM_VALUE = MAXIMUM_FACE_VALUE + 3;
    public static final int NUMBER_OF_CARDS = 52;

    public enum Suit {CLUBS, DIAMONDS, HEARTS, SPADES}

    public int value;
    public Suit suit;

    /**
     * Initializes a Card.
     *
     * @param value the new Card's value
     * @param suit  the new Card's suit
     */
    public Card(int value, Suit suit) {
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
        if (value < MINIMUM_VALUE || value > MAXIMUM_VALUE) {                           // Illegal values
            valueString = "UNKNOWN";
        } else if ((value >= MINIMUM_FACE_VALUE) && (value <= MAXIMUM_FACE_VALUE)) {    // Number card
            valueString = Integer.toString(value);
        } else {                                                                        // Ace or face card
            switch (value) {
                case MINIMUM_VALUE:
                    valueString = "ACE";
                    break;
                case MAXIMUM_VALUE - 2:
                    valueString = "JACK";
                    break;
                case MAXIMUM_VALUE - 1:
                    valueString = "QUEEN";
                    break;
                case MAXIMUM_VALUE:
                    valueString = "KING";
                    break;
                default:
                    valueString = "DEADCODE";       // This line is unreachable
            }
        }
        return valueString + " of " + suitsString;
    }
}
