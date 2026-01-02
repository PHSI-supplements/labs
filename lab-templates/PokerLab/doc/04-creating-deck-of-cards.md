## Creating a Deck of Cards

### Completing *card.c*

Look over the rest of the code in *card.c* and work at understanding anything that you don't initially understand.
When you have done so:

- [ ] Add the missing code to `create_card()` to populate a card's fields.
- [ ] Change the first two lines of `card_to_string()` so that this function uses the fields from the card argument that is passed to the function.

You will receive half-credit for `create_card()` and `card_to_string()` if you make a good-faith effort at implementing these functions as specified.
You will receive full credit for these functions if you implement them correctly.

- [ ] Compile your code (from your IDE or using `cmake --build build`).
- [ ] Run the program (from your IDE or using the command `build/pokerlab`).
- [ ] Test your changes to *card.c* by selecting option 1.

Catching errors now will be easier than trying to catch them after you've started the next task.

- [ ] Examine the remaining starter code in *card.c* to make sure you understand it.


### Write the Code for `populate_deck()`

- [ ] Using `create_card()` from *card.c*, create cards corresponding to the 52 standard playing cards and add them to the `deck[]` array.
- [ ] Compile and run your program.
    - Confirm that you wrote `populate_deck()` correctly by selecting option 2 to print out all 52 cards in `deck[]`.

---

### Save Your Progress

- [ ] Use `git add` (or your IDE's equivalent) to stage *card.c* (and any other files you have edited).
- [ ] Use `git commit` (or your IDE's equivalent) to commit the update to the local copy of your repository.
      Be sure to use a descriptive commit message.
- [ ] Use `git push` (or your IDE's equivalent) to push the commit to git.unl.edu.


---

|             [⬅️](03-print-conversion-specifier.md)             |      [⬆️](../README.md)      |             [➡️](05-code-reading.md)              |
|:--------------------------------------------------------------:|:----------------------------:|:-------------------------------------------------:|
| [Print Conversion Specifier](03-print-conversion-specifier.md) | [Front Matter](../README.md) | [Study the Code in *poker.c*](05-code-reading.md) |
