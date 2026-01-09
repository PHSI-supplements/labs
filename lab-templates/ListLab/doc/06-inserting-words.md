## Inserting Words

The `build_list()` function in *sorted_word_entries.c* reads words from a "book" and sends them to `insert_word()`.
You do not need to implement `build_list()`.

The `insert_word()` function in *sorted_word_entries.c* finds the correct place in the list for a lowercase copy of the word.
If the word is already in the list, then it increments the word's count;
otherwise, it inserts the word into the list.
You will implement `insert_word()`.

---

### TL;DR

- You will receive half of the credit for `insert_word()` if it works on pre-sorted books.
If you choose to use this implementation:
  - [ ] Implement `insert_word()` for pre-sorted books
  - [ ] Test this implementation and move on to implementing a linked list
  - [ ] Return to this sub-problem later to attempt a more-general implementation

- To receive full credit for `insert_word()`, it must work on books that are not pre-sorted.
  If you choose to use this implementation:
  - [ ] Implement `insert_word()` such that:
    - The word is placed at the end of the list
    - If the word is not in its proper location, then it is moved to is proper location
    - Once in its proper location, if there is another word entry with the same word, then the two word entries are combined

- [ ] Build and run the executable.
- [ ] Use tasks 4--6 to test `insert_word()` until you discover a bug or are satisfied that your implementation is correct.
- [ ] Use task 7 to test your code with the files of words.
- [ ] When you have finished, select 0 to exit the program.

---

### Limited Implementation

The simplest implementation of `insert_word()` is to assume that the words in the book are already sorted -- as they are for "Animals", "Cars", and "Frankenstein".
In this case, you know that if the word is already in the list then it is the last word in the list,
and if the word is not already in the list then it belongs at the end of the list.

You will receive half of the credit for `insert_word()` if it works on pre-sorted books.
*If you choose to use this implementation:*

- [ ] Implement `insert_word()` for pre-sorted books
- [ ] Test this implementation and move on to implementing a linked list
- [ ] Return to this sub-problem later to attempt a more-general implementation

*Otherwise, implement Insertion Sort…*

### Insertion Sort

> 📽️ **Optional Videos**
> 
> Consider reviewing [these videos](https://canvas.unl.edu/courses/209782/pages/insertion-sort) about Insertion Sort.

While you probably learned about sorting in CSCE 156, RAIK 184H, or SOFT 161, you may not have learned about *Insertion Sort*.
If you did learn about Insertion Sort, you probably learned to use it to sort an array or list in-place, and that it's a $\mathcal{O}(n^2)$ algorithm that is less efficient than $\mathcal{O}(n \log n)$ sorting algorithms such as Merge Sort and Quick Sort.
Insertion Sort is often taught as a way to sort an array in-place,
but a variation of Insertion Sort has a particular advantage in that it can be applied *as the list is built*, making for a much simpler and less error-prone implementation than a different sort that requires the list to already be built.

Your Insertion Sort algorithm will read an input and then traverse a sorted list to find the proper location in the sorted list for the input.
The input is then inserted into the list at that location, preserving the property that the list is sorted.

- [ ] Implement `insert_word()` such that:
  - The word is placed at the end of the list
  - If the word is not in its proper location, then it is moved to is proper location
  - Once in its proper location, if there is another word entry with the same word, then the two word entries are combined

### Testing Your Changes

If you were to apply category-partition testing, you might arrive at these categories and partitions:

|          Categories          |                                                     Partitions                                                     |
|:----------------------------:|:------------------------------------------------------------------------------------------------------------------:|
| Word's position in the list  | only word in the list<br>at the start of the list<br>at the end of the list<br>somewhere in the middle of the list |
|  The list's initial length   |                                     no words<br>one word<br>more than one word                                     |
| Word is already in the list? |                                                     yes<br>no                                                      |
|  Word is already lowercase?  |                                                     yes<br>no                                                      |


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
You can test "only word in the list"/"word is not already in the list" with task 4.
You can test most of the other combinations with tasks 5 \& 6.
When you select these options, an initial sorted list (empty or pre-populated, as appropriate) will be created and printed, and you will be prompted to enter a word.
After you have entered a word, 'insert_word()` will be called, and the resulting sorted list (with a new word with 1 occurrence, or with an existing word's occurrences increased by 1) will be printed.
- [ ] Test `insert_word()` until you discover a bug or are satisfied that your implementation is correct.

### Testing the System with "Books"

When you are satisfied that your word entry, alphabetical, and word insertion functions are correct, test them with book files.
With task 7, you will be prompted for the name of a book file, and then the list will be generated and printed.
You can use the "*file*-table.md" files to confirm the correctness of the results.

> ❗️ **Important**
> 
> If your program requires more than a few seconds to build a list, then there is a bug in your code.

- [ ] Test building a list until you discover a bug or are satisfied that your implementations are correct.
- [ ] When you have finished, select 0 to exit the program.

As a reminder, the book files are:

- "data/Animals" (sorted, 7 words)
- "data/Plants" (unsorted, 7 words)
- "data/Cars" (sorted, 74 words)
- "data/Food" (unsorted, 125 words)
- "data/Frankenstein" (sorted, 74,363 words)
- "data/TheLostWorld" (unsorted, 77,268 words)

---

|              [⬅️](05-preparing-to-work-with-lists.md)              |      [⬆️](../README.md)      |          [➡️](07-linked-list-overview.md)          |
|:------------------------------------------------------------------:|:----------------------------:|:--------------------------------------------------:|
| [Preparing to Work with Lists](05-preparing-to-work-with-lists.md) | [Front Matter](../README.md) | [Linked List Overview](07-linked-list-overview.md) |
