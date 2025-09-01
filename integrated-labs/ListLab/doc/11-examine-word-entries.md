## Examining Word Entries

The `get_word_entry()` function retrieves the current node's word entry.
The `get_next_word_entry()` and `get_previous_word_entry()` retrieve the head's and tail's word entries, respectively.
If the current, head, or tail pointers are `NULL`, then the corresponding functions return `NULL`.


- [ ] Implement `get_word_entry()`.
- [ ] Implement `get_next_word_entry()`.
- [ ] Implement `get_previous_word_entry()`.


- [ ] Build and run *linkedlist* (and, optionally, *arraylist* in another terminal window)
- [ ] Create a list by selecting option 2 ("Test list") and function 1 ("create_list()"). Get the iterator with function 3 ("get_iterator()").
- [ ] Test `get_word_entry()` on an empty list by selecting function 13 ("get_word_entry()").
- [ ] Create a list with one node by selecting function 7 ("append()").
- [ ] Test `get_word_entry()` by selecting function 13 ("get_word_entry()").
- [ ] Create a list with multiple nodes by selecting function 7 ("append()").
- [ ] Test `get_previous_word_entry()` selecting function 15 ("get_previous_word_entry()").
- [ ] Iterate back to the head with `iterate_previous()` (function 8), and test `get_next_word_entry()` selecting function 14 ("get_next_word_entry()").
- [ ] Continue to test `get_word_entry()`, `get_next_word_entry()`, and `get_previous_word_entry()` until you discover a bug or are satisfied that your implementation is correct.
- [ ] Free the memory by selecting function 2 ("delete_list()").
  Exit out of the program by selecting function 0, then option 0.

---

|                      [⬅️](10-insert-delete-node.md)                       |      [⬆️](../README.md)      |                      [➡️](12-swap-merge-nodes.md)                       |
|:-------------------------------------------------------------------------:|:----------------------------:|:-----------------------------------------------------------------------:|
| [Insertion and Deletion at Arbitrary Locations](10-insert-delete-node.md) | [Front Matter](../README.md) | [Swapping and Merging Nodes, and Final Testing](12-swap-merge-nodes.md) |
