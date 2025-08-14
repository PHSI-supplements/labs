## Characterizing a Poker Hand

### Write `characterize_hand()`

- [ ] Add code to `characterize_hand()` to print the five cards in `hand`.
- [ ] Add code to `characterize_hand()` to use the `is...()` functions to determine the best characterization of `hand`.

Recall from the discussion of the [types of poker hands](01-terminology.md#types-of-poker-hands) that the hand characterizations from most-desirable to least-desirable are:
- Straight Flush
- Four of a Kind
- Full House
- Flush
- Straight
- Three of a Kind
- Two Pair
- Pair
- High Card (the default if the hand cannot be better characterized)


- [ ] Add code to `characterize_hand()` to print that determination.

You can test your code using the program's option 3 (which allows you to specify a particular hand) and option 4 (which generates a random hand).
(Unlike poker with a "real" deck of cards, this program allows a card to appear more than once in a hand;
decide for yourself whether this is best characterized as a known bug or as a feature.)
For now, the program does not correctly characterize a hand that is a three of a kind, a full house, or a four of a kind.


### Write `is_three_of_kind()`

- [ ] Implement and test `is_three_of_kind()`.
  - Do three cards all have the same value?
  - You may assume that `hand` is pre-sorted from the least value to the greatest value

### Write `is_full_house()`

- [ ] Implement and test `is_full_house()`.
  - Does the hand contain a three of a kind and also contain a pair with a different value than that of the other three cards?
    - The card value of the pair might be less than the card value of the three of a kind, or it might be greater than the card value of the three of a kind. 
  - You may assume that `hand` is pre-sorted from the least value to the greatest value

### Write `is_four_of_kind()`

- [ ] Implement and test `is_four_of_kind()`.
  - Do four cards all have the same value?
  - You may assume that `hand` is pre-sorted from the least value to the greatest value

---    

You will receive half-credit for `characterize_hand()`, `is_three_of_kind()`, `is_full_house()`, and `is_four_of_kind()` if you make a good-faith effort at implementing these functions as specified.
You will receive full credit for these functions if you implement them correctly.

---

|             [⬅️](05-code-reading.md)              |      [⬆️](../README.md)      |         [➡️](07-grading.md)          |
|:-------------------------------------------------:|:----------------------------:|:------------------------------------:|
| [Study the Code in *poker.c*](05-code-reading.md) | [Front Matter](../README.md) | [Turn-In and Grading](07-grading.md) |
