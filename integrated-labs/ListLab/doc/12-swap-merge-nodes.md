## Swapping and Merging Nodes, and Final Testing

### Swapping Nodes

The `swap_next()` and `swap_previous()` functions cause the current node to swap places in the list with its next or previous node, respectively.
Just as repeated calls to `iterate_next()` or `iterate_previous()` can move the iterator to any position in the list,
repeated calls to `swap_next()` or `swap_previous()` can move a node to any position in the list.

- [ ] Implement `swap_next()`.
- [ ] Implement `swap_previous()`.


- [ ] Build and run *build/linkedlist* (and, optionally, *build/arraylist* in another terminal window)
- [ ] Create a list by selecting option 2 ("Test list") and function 1 ("create_list()").
- [ ] Add a node by selecting function 10 ("append()"), and test that `swap_next()` does not crash the program when there is no next node, by selecting function 16 ("swap_next()").
- [ ] Get a valid iterator (function 3), and test that `swap_previous()` does not crash the program when there is no next node, by selecting function 17 ("swap_previous()").
- [ ] Prepend (function 9) two more nodes.
- [ ] Test that you can move the head node to the tail by swapping next (function 16) twice.
- [ ] Test that you can move the tail node to the head by swapping previous (function 17) twice.
- [ ] Continue to test `swap_next()` and `swap_previous()` until you discover a bug or are satisfied that your implementation is correct.
- [ ] Free the memory by selecting function 2 ("delete_list()").
  Exit out of the program by selecting function 0, then option 0.



### Merging Nodes

Once you have a word entry in its correct position in the list, it's possible that there's another word entry with the same word.
If that happens, then the word entries should be merged, resulting in one word entry whose *occurrences* is the sum of the two original word entries' *occurrences*.


- [ ] Implement `merge_next()`.
- [ ] Implement `merge_previous()`.


- [ ] Build and run *build/linkedlist* (and, optionally, *build/arraylist* in another terminal window)
- [ ] Create a list by selecting option 2 ("Test list") and function 1 ("create_list()").
- [ ] Add a node by selecting function 10 ("append()"), and test that `merge_next()` does not crash the program when there is no next node, by selecting function 18 ("merge_next()").
- [ ] Get a valid iterator (function 3), and test that `merge()` does not crash the program when there is no next node, by selecting function 19 ("merge_previous()").
- [ ] Prepend (function 9) four more nodes, and iterate (function 7) to the third of the five nodes.
- [ ] Test that you can merge the current node with its next node by selecting function 18 ("merge_next()").
- [ ] Test that you can merge the current node with its previous node by selecting function 19 ("merge_previous()").
- [ ] Test that you can merge the current node with the tail node by selecting function 18 ("merge_next()").
- [ ] Test that you can merge the current node with the head node by selecting function 19 ("merge_previous()").
- [ ] Continue to test `swap_next()` and `swap_previous()` until you discover a bug or are satisfied that your implementation is correct.
- [ ] Free the memory by selecting function 2 ("delete_list()").
  Exit out of the program by selecting function 0, then option 0.


### Testing the System with "Books"

When you are satisfied that your linked list functions are correct, test them with book files.
You can use the "*file*-table.md" files to confirm the correctness of the results.

> ❗️ **Important**
>
> If your program requires more than a few seconds to build a list, then there is a bug in your code.

- [ ] Test building a list until you discover a bug or are satisfied that your implementations are correct.
- [ ] When you have finished, select 0 to exit the program.

As a reminder, the book files are:

- "Animals" (sorted, 7 words)
- "Plants" (unsorted, 7 words)
- "Cars" (sorted, 74 words)
- "Food" (unsorted, 125 words)
- "Frankenstein" (sorted, 74,363 words)
- "TheLostWorld" (unsorted, 77,268 words)

Your code might already be able to handle large files in just a few seconds, in which case you are finished.

On the other hand, your code might run briskly when working with smaller files of only a couple of hundred words but then become very sluggish when the number of words is in the thousands.
This tends to be due to one (or both) of two causes.
Look for inefficient algorithms, and look for memory leaks.
If you use the `top` utility while running your program, and you notice that your program is allocating more than 10MB, then you probably have a memory leak.
If your program is allocating more than 1GB, then your program most certainly has a memory leak.

---

|           [⬅️](11-examine-word-entries.md)           |      [⬆️](../README.md)      |   [➡️](13-grading.md)    |
|:----------------------------------------------------:|:----------------------------:|:------------------------:|
| [Examining Word Entries](11-examine-word-entries.md) | [Front Matter](../README.md) | [Turn-IN and Grading](13-grading.md) |
