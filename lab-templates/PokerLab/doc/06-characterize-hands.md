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


### Write `is_four_of_kind()`

- [ ] Implement and test `is_four_of_kind()`.
  - Do four cards all have the same value?
  - You may assume that `hand` is pre-sorted from the least value to the greatest value

### Write `is_two_pair()`

- [ ] Implement and test `is_two_pair()`.
  - Do two cards form a pair and a different two cards also form a pair?
  - You may assume that `hand` is pre-sorted from the least value to the greatest value

---    

You will receive half-credit for `characterize_hand()`, `is_three_of_kind()`, `is_full_house()`, and `is_four_of_kind()` if you make a good-faith effort at implementing these functions as specified.
You will receive full credit for these functions if you implement them correctly.

---

### Save Your Progress

- [ ] Use `git add` (or your IDE's equivalent) to stage *poker.c* (and any other files you have edited).
- [ ] Use `git commit` (or your IDE's equivalent) to commit the update to the local copy of your repository.
  Be sure to use a descriptive commit message.
- [ ] Use `git push` (or your IDE's equivalent) to push the commit to git.unl.edu.


---

|             [⬅️](05-code-reading.md)              |      [⬆️](../README.md)      |         [➡️](07-grading.md)          |
|:-------------------------------------------------:|:----------------------------:|:------------------------------------:|
| [Study the Code in *poker.c*](05-code-reading.md) | [Front Matter](../README.md) | [Turn-In and Grading](07-grading.md) |
