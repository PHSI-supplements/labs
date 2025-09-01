## Insertion and Deletion at Arbitrary Locations

The `prepend()` and `append()` functions can only add nodes to the list's extrema.
One of the advantages of a linked list over an array is that insertions and deletions in the middle of the list are constant-time operations.

- [ ] Implement `insert()` to place a word entry at the iterator's current location; that is, the new node should be between the current node and its previous node.
- [ ] Implement `delete()` to remove the word entry at the iterator's current location.


- [ ] Build and run *build/linkedlist* (and, optionally, *build/arraylist* in another terminal window)
- [ ] Create a list by selecting option 2 ("Test list") and function 1 ("create_list()"). Get the iterator with function 3 ("get_iterator()").
- [ ] Test `insert()` for an empty list by selecting function 11 ("insert()").
- [ ] Get a valid iterator (function 3), and test `insert()` for a list with one node by selecting function 11 ("insert()").
- [ ] Get a valid iterator (function 3), iterate forward (function 7), and test `insert()` for a list with multiple nodes by selecting function 11 ("insert()").
- [ ] Test that you can delete the head of a list by prepending a node (function 9), and then deleting that node by selecting function 12 ("delete()").
- [ ] Test that you can delete a node in the middle of a list by getting a valid iterator (function 3), iterating forward (function 7), and deleting the second of three nodes by selecting function 12 ("delete()").
- [ ] Test that you can delete the tail of a list by getting a valid iterator (function 3), iterating forward (function 7), and deleting the second of two nodes by selecting function 12 ("delete()").
- [ ] Test that you can delete the only node in a singleton list by getting a valid iterator (function 3) and deleting the node by selecting function 12 ("delete()").
- [ ] Test that attempting to delete from an empty list doesn't crash the program, by getting a valid iterator (function 3) and selecting function 12 ("delete()").
- [ ] Continue to test `insert()` and `delete()` until you discover a bug or are satisfied that your implementation is correct.

---

|    [⬅️](09-iterating.md)     |      [⬆️](../README.md)      |           [➡️](11-examine-word-entries.md)           |
|:----------------------------:|:----------------------------:|:----------------------------------------------------:|
| [Iterating](09-iterating.md) | [Front Matter](../README.md) | [Examining Word Entries](11-examine-word-entries.md) |
