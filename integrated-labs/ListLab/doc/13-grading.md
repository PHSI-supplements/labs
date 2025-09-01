> 📇 **Epilogue**
>
> You hear somebody enter the room.
> After the new arrival authenticates with the new application, Archie introduces you to her,
> "Lil, this is our new developer, the one who wrote the app we just used."
> He turns to you: “This is Lilith Redd from business operations.”
> He turns back to her and continues, "Lil, what’s the good word?"
> 
> "The word isn’t good, I’m afraid. I just heard back from the insurance company."
> 
> *To be continued...*

## Turn-In and Grading

Be sure that you have pushed your code to git.unl.edu.

### No Credit for Uncompilable Code

If the TA cannot create an executable from your code, then your code will be assumed to have no functionality.
Be sure to compile and test your code on the nuros.unl.edu Linux server with the original driver code, the original header file(s), and the original CMake configuration files.

> ✍️ **One Edit Rule**
>
> At the TA's discretion, if they can make your code compile with one edit (such as introducing a missing semicolon) then they may do so and then assess a 10% penalty on the resulting score.
> The TA is under no obligation to do so, and you should not rely on the TA’s willingness to edit your code for grading.
> If there are multiple options for a single edit that would make your code compile, there is no guarantee that the TA will select the option that would maximize your score.

### Late Submissions

This assignment is due before the start of your lab section.
If you have late days available, you may use one or more to extend your deadline.
You can exercise a late day (or days) by editing the [LATE-DAYS-USED-ON-THIS-ASSIGNMENT.txt](../LATE-DAYS-USED-ON-THIS-ASSIGNMENT.txt) file and including the update with your code.

After you have exhausted your late days, we will accept late turn-ins up to one hour late, assessing a 10% penalty on these late submissions.
After you have exhausted your late days, any work turned in more than one hour late will not be graded.

### Rubric

[//]: # (<span style="background-color: lime;">TODO: update?</span>)

This assignment is worth 35 points.

<!-- Archie's Code - 5 -->
- [ ] **+2** Student's answers in *answers.txt* demonstrate an understanding of the bug in Section~\ref{subsec:uninitializedvariables's code and how to correct it.}
- [ ] **+3** Student's answer in *answers.txt* demonstrate an understanding of the bug in Section~\ref{subsec:danglingPointers's code.}
<!-- Word Entries - 2 -->
- [ ] **+½** `create_word_entry` initializes `word_entry` as specified.
- [ ] **+½** `increment_count()` increases the number of occurrences by one.
- [ ] **+½** `get_count()` returns the number of occurrences.
- [ ] **+½** `get_word()` returns the word.
<!-- Sorting - 8 -->
- [ ] **+2** `word_to_lowercase()` returns a copy of the word with all uppercase letters made lowercase.
- [ ] **+2** `words_are_equal()`, `word1_is_earlier_than_word2()`, and `word1_is_later_than_word3()` return `true` if and only if `word1` is equal to, less than, or greater than `word2`, respectively.
- [ ] **+2** `insert_word()` correctly inserts a word into a list, when the book file is pre-sorted.
- [ ] **+2** `insert_word()` correctly inserts a word into a list, when the book file is not pre-sorted.
<!-- Linked List - 20 -->
- [ ] **+½** `create_node()` initializes `node` as specified.
- [ ] **+½** `create_list()` initializes `word_list` as specified.
- [ ] **+1** `get_iterator()` returns the list's `iterator`, and `get_list()` returns the iterator's `list`, as specified.
- [ ] **+1** `has_next()` and `has_previous()` correctly report the presence/absence of a next/previous node, as specified
- [ ] **+2** `iterate_next()` and `iterate_previous()` change the current node to the next/previous node, as specified
- [ ] **+1** `prepend()` places a word entry at the start of a linked list.
- [ ] **+1** `append()` places a word entry at the end of a linked list.
- [ ] **+2** `insert()` places a node containing `word_entry` in a linked list at the iterator's location.
- [ ] **+2** `delete()` removes a node from a linked list.
- [ ] **+3** `get_word_entry()`, `get_next_word_entry()`, and `get_previous_word_entry()` return the `word_entry_t` contained in the current/next/previous node as specified.
- [ ] **+2** `swap_next()` and `swap_previous()` swap the positions of the current node and the next/previous node, as specified
- [ ] **+2** `merge_next()` and `merge_previous()` combine the current node with the next/previous node, as specified
- [ ] **+1** The system, using your code, can generate a list from a pre-sorted file of up to 80,000 words without crashing or timing-out.
- [ ] **+1** The system, using your code, can generate a list from an unsorted file of up to 80,000 words without crashing or timing-out.
- Penalties:
  - [ ] **no credit** for functions that time out.
  - [ ] **-1** for each `goto` statement, `break` statement used to exit from a loop, or `return` statement that occurs within a loop

---

|                      [⬅️](12-swap-merge-nodes.md)                       |      [⬆️](../README.md)      |                                                [➡️](AA-JavaVsC.md)                                                |
|:-----------------------------------------------------------------------:|:----------------------------:|:-----------------------------------------------------------------------------------------------------------------:|
| [Swapping and Merging Nodes, and Final Testing](12-swap-merge-nodes.md) | [Front Matter](../README.md) | [Appendix A: Differences and Similarities between Java and C that are Relevant to this Assignment](AA-JavaVsC.md) |
