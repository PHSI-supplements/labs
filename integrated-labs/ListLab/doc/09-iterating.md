## Iterating

In our list design, the iterator is used to navigate the list.

Iterating forward past the tail, or backward past the head, is problematic -- 
these actions would fire an exception in languages with software exceptions.
Our list specification instead invalidates the iterator, resulting in undefined behavior.
The surest way to avoid that problem is to first determine whether there's another element to iterate to.

- [ ] Implement `has_next()` and `has_previous()` to return true if and only if the iterator's current node has a next or previous node, respectively.

The `iterate_next()` and `iterate_previous()` functions cause the iterator to move back and forth across the sequence.
For a linked list, this means that you follow the current node's `next` or `previous` pointers, as appropriate.

- [ ] Implement `iterate_next()` and `iterate_previous()`.
  - Iterating to a non-existent node beyond the bounds of the list invalidates the iterator and results in undefined behavior.
    Normally, when behavior is undefined, any resulting behavior is acceptable, including crashing the program.
  - <font color="red">In this assignment, when the behavior is undefined, any result is acceptable *except* crashing the program.
    Specifically, **you may not dereference a null pointer**.</font>


- [ ] Build and run *build/linkedlist* (and, optionally, *build/arraylist* in another terminal window)
- [ ] Create a list by selecting option 2 ("Test list") and function 1 ("create_list()"). Get the iterator with function 3 ("get_iterator()").
- [ ] Test that `has_next()` and `has_previous()` both return `false` for an empty list, using functions 5 ("has_next()") and 6 ("has_previous()").
- [ ] Test that neither `iterate_next()` nor `iterate_previous()` crash the program for an empty list, using functions 7 ("iterate_next()") and 8 ("iterate_previous()").
  - Be sure to get a valid iterator (function 3) between those tests, since attempting to iterate beyond the list's bounds invalidates the iterator.
- [ ] Prepend a word entry (function 9).
- [ ] Test that `has_next()` and `has_previous()` both return `false` for singleton list, using functions 5 ("has_next()") and 6 ("has_previous()").
- [ ] Test that neither `iterate_next()` nor `iterate_previous()` crash the program for singleton list, using functions 7 ("iterate_next()") and 8 ("iterate_previous()").
  - Be sure to get a valid iterator (function 3) between those tests, since attempting to iterate beyond the list's bounds invalidates the iterator.
- [ ] Use `prepend()` and/or `append()` a few times to build-out the list.
- [ ] Test that `iterate_next()` nor `iterate_previous()` correctly navigate the list by updating the iterator, using functions 7 ("iterate_next()") and 8 ("iterate_previous()").
- [ ] Test that `has_next()` and `has_previous()` return `true` or `false` as appropriate for various positions in the list, using functions 5 ("has_next()") and 6 ("has_previous()").
- [ ] Continue to test the iteration functions until you discover a bug or are satisfied that your implementations are correct.
- [ ] Free the memory by selecting function 2 ("delete_list()").
  Exit out of the program by selecting function 0, then option 0.

---

|              [⬅️](08-create-and-attach-node.md)               |      [⬆️](../README.md)      |                      [➡️](10-insert-delete-node.md)                       |
|:-------------------------------------------------------------:|:----------------------------:|:-------------------------------------------------------------------------:|
| [Creating and Attaching a Node](08-create-and-attach-node.md) | [Front Matter](../README.md) | [Insertion and Deletion at Arbitrary Locations](10-insert-delete-node.md) |
