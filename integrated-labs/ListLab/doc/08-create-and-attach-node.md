## Creating and Attaching a Node

### Creating a Node, Creating a List

In *linked_list.c*:

- [ ] Edit `create_node()` to initialize all of a new node's fields, as well as those of its iterator.
- [ ] Edit `create_list()` to initialize all of a new list's fields.
  - The list's `iterator` field should point to its iterator, and the iterator's `list` field should point back to its list (See Section~\ref{subsubsec:listt-as-lined-list}).
- [ ] Edit `get_iterator()` to return the list's iterator.
- [ ] Edit `get_list()` to return the list's iterator. The current node should be the head of the list.


- [ ] Build and run *linkedlist* (and, optionally, *arraylist* in another terminal window)
- [ ] Test `create_node()` and `create_list()` by selecting option 2 ("Test list") and function 1 ("create_list()").
- [ ] Test `get_iterator()` and `get_list()` by selecting functions 3 ("get_iterator()") and 4 ("get_list()").
- [ ] Free the memory by selecting function 2 ("delete_list()").
  Exit out of the program by selecting function 0, then option 0.

It is unlikely that you made any errors that would cause these test to fail,
but it's better to find out now if you did.

### Prepending and Appending a Node

The `append()` function takes a word entry, makes it the payload of a new node, and places the new node at the start of the linked list.
The new node, of course, becomes the head of the list.
Similarly, the `append()` function takes a word entry, makes it the payload of a new node, and places the new node at the end of the linked list.
The new node becomes the tail of the list.
If the list is initially empty, then the new node is both the head and the tail of the list.


- [ ] Edit `prepend()` to place a word entry at the start of the list. The current node should be the newly-added node.
- [ ] Edit `append()` to place a word entry at the end of the list. The current node should be the newly-added node.


- [ ] Build and run *linkedlist* (and, optionally, *arraylist* in another terminal window)
- [ ] Create a list by selecting option 2 ("Test list") and function 1 ("create_list()").
- [ ] Test `prepend()` for an empty list by selecting function 9 ("prepend()").
- [ ] Test `prepend()` for a list with one node by selecting function 9 ("prepend()").
- [ ] Test `prepend()` for a list with multiple nodes by selecting function 9 ("prepend()").
- [ ] Delete the list (function 2, "delete_list()") and create a new list (function 1, "create_list()").
- [ ] Test `append()` for an empty list by selecting function 10 ("append()").
- [ ] Test `append()` for a list with one node by selecting function 10 ("append()").
- [ ] Test `append()` for a list with multiple nodes by selecting function 10 ("append()").
- [ ] Continue to test `append()` and `prepend()` until you discover a bug or are satisfied that your implementation is correct.
- [ ] Free the memory by selecting function 2 ("delete_list()").
  Exit out of the program by selecting function 0, then option 0.

---

|          [⬅️](07-linked-list-overview.md)          |      [⬆️](../README.md)      |    [➡️](09-iterating.md)     |
|:--------------------------------------------------:|:----------------------------:|:----------------------------:|
| [Linked List Overview](07-linked-list-overview.md) | [Front Matter](../README.md) | [Iterating](09-iterating.md) |
