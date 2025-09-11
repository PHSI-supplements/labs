> 📇 **Scenario, continued**
>
> It is entirely probable that H.Awk, left to his own devices, would simply have used an array instead of making the effort to create an array-backed list with a well-defined abstract model.
> Fortunately, someone pulled his strings, and you have available to you an abstract model of a list that can be realized by any number of implementations.

## Preparing to Work with Lists

Like `word_entry_t`, the `list_t` and the `iterator_t` datatypes have functions to encapsulate them.
In the case of `list_t` and `iterator_t`, however, this encapsulation is essential because the code in *sorted_word_entries.c* has access to the type declaration but not the type definition.

- [ ] Review the datatypes and functions declared in *list.h*.

A list is abstractly modeled as having a sequence of word entries and an iterator that points to the "current" word entry.
The iterator can point to anywhere between the first word entry and the last word entry.

> 💡 **Tip**
> 
> A good rule of thumb is that if the previous operation returned the iterator, then the iterator is valid;
> if the previous operation returned the list, then the iterator is invalid and should not be used.
> Attempting to access non-existent word entries beyond the bounds of the list will also invalidate the iterator.

- The `get_iterator()` function sets the iterator to the first word entry, and the `iterate_next()` and `iterate_previous()` functions cause the iterator to advance and retreat
- The `has_next()` and `has_previous()` functions report whether there are additional word entries in the indicated direction
- The `get_word_entry()` function retrieves the word entry that the iterator points to, and the `get_next_word_entry()` and `get_previous_word_entry()` functions retrieve the word entry in the indicated direction
- The `prepend()` and `append()` functions place a word entry at the beginning or end of the list, respectively, setting the iterator to the new word entry
- The `insert()` function places a new word entry at the iterator's location, and `delete()` function removes the word entry at the iterator's location -- both of these functions invalidate the iterator
- The `swap_next()` and `swap_previous()` functions can be used to move a word entry forward and backward
- The `merge_next()` and `merge_previous()` functions can be used to combine a word entry with its neighbor


- [ ] Review the `test_list()` function in *list-test.c* to see uses of the `list_t` and `iterator_t` functions.
- [ ] Run the *arraylist* executable, selecting task 2 ("Test list") to observe the behavior of the `list_t` and `iterator_t` functions.

---

|           [⬅️](04-alphabetical-functions.md)           |      [⬆️](../README.md)      |       [➡️](06-inserting-words.md)        |
|:------------------------------------------------------:|:----------------------------:|:----------------------------------------:|
| [Alphabetical Functions](04-alphabetical-functions.md) | [Front Matter](../README.md) | [Inserting Words](06-inserting-words.md) |
