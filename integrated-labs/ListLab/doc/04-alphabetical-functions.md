## Alphabetical Functions

---

### TL;DR

- [ ] Implement the `word_to_lowercase()` function.
- [ ] Implement the `words_are_equal()` function.
- [ ] Implement the `word1_is_earlier_than_word2()` function.
- [ ] Implement the `word1_is_later_than_word2()` function.


- [ ] Build and run the executable.
- [ ] Select task 3, "Test alphabetical functions", and enter words when prompted.
- [ ] Continue to test until you discover a bug or are satisfied that your implementations are correct.
- [ ] When you have finished, select 0 to exit the program.

---

### Making a Lowercase Copy of a Word

Because the book's words should be insensitive to capitalization, we will store the words with all of their letters in lowercase.
In *challenge-response.c*, there is a `word_to_lowercase()` function to do just that.

- [ ] Implement the `word_to_lowercase()` function.

Unlike KeyboardLab, you can use the `tolower()` function\footnote{\url{https://en.cppreference.com/w/c/string/byte/tolower}} from `ctype.h`.

### Comparing Words

Because the book's words need to be sorted, we need to be able to compare words.
In *challenge-response.c*, there are three functions to do that:

- `words_are_equal()` which returns `true` if and only if the two words are indistinguishable
- `word1_is_earlier_than_word2()` which returns `true` if and only if the first word precedes the second word in an alphabetically-sorted list
- `word1_is_later_than_word2()` which returns `true` if and only if the first word follows the second word in an alphabetically-sorted list


- [ ] Implement the `words_are_equal()` function.
- [ ] Implement the `word1_is_earlier_than_word2()` function.
- [ ] Implement the `word1_is_later_than_word2()` function.

We recommend that you use the `strncmp()` function\footnote{\url{https://en.cppreference.com/w/c/string/byte/strncmp}} from `string.h`.

### Testing Your Changes

You can build an executable that uses H.Awk's array-backed list with the command \\
\verb+make arraylist+ \\
or, if you want to limit each `malloc()` call to no more than 32KB, then use the command \\
\verb+make arraylist "OPTION=-DHOBBLE"+

- [ ] Build and run the executable.
  ```
  0) Quit
  1) Test word_entry
  2) Test list
  3) Test alphabetical functions
  4) Test insert_word (empty list)
  5) Test insert_word (singleton list)
  6) Test insert_word (populated list)
  7) Create and print book list
     Select the task you wish to check:
  ```
- [ ] Select task 3, "Test alphabetical functions", and enter words when prompted.

Each word will be displayed in its lowercase form, and the results of the three comparison functions will be shown.

- [ ] Continue to test until you discover a bug or are satisfied that your implementations are correct.
- [ ] When you have finished, select 0 to exit the program.

---

|      [⬅️](03-word-entries.md)      |      [⬆️](../README.md)      |              [➡️](05-preparing-to-work-with-lists.md)              |
|:----------------------------------:|:----------------------------:|:------------------------------------------------------------------:|
| [Word Entries](03-word-entries.md) | [Front Matter](../README.md) | [Preparing to Work with Lists](05-preparing-to-work-with-lists.md) |

