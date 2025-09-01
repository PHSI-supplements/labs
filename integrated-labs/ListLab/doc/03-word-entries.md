> 📇 **Scenario, continued**
>
> You break the problem down into three sub-problems:
> - Designing the Data Structure and Its Algorithms
> - Alphabetizing Words
> - Inserting Words
>
> H.Awk provides you with the code he worked on.
> It turns out that while he finished implementing the array-backed list, he didn't finish the sorting algorithm.
> You decide to warm up by finishing the app and then circling back to the linked list.

## Word Entries

The `word_entry_t` type is defined in *word_entry.h*:
```c
typedef struct {
    char word[MAXIMUM_WORD_LENGTH + 1];
    int occurrences;
} word_entry_t;
```
There are also a handful of function prototypes in *word_entry.h* that encapsulate this datatype.

---

### TL;DR

The `create_word_entry()` function allocates space for a `word_entry_t`, and the `delete_word_entry()` function releases that memory.
The `create_word_entry()` function, however, does not yet initialize the word entry.

- [ ] In `create_word_entry()`'s `else` block, copy `word` into `word_entry`'s `word` field.
- [ ] In `create_word_entry()`'s `else` block, set `word_entry`'s `occurrences` field to 0.

You do not need to make any changes to `delete_word_entry()`.

- [ ] In `increment_count()`, increase the word entry's number of occurrences by one.
- [ ] In `get_count()`, return the number of occurrences.
- [ ] In `get_word()`, return a pointer to the word entry's word. (Do *not* make a copy of the word.)

You can build an executable that uses H.Awk's array-backed list with the command
```shell
cmake --build build --target arraylist
```
<!--
or, if you want to limit each `malloc()` call to no more than 256 bytes, then use the command \\
\verb+make arraylist OPTION="-DHOBBLE"+
--> 

        
- [ ] Build and run the executable.
- [ ] Select task 1, "Test word_entry".
- [ ] Select function 1, "create_word_entry()", and enter a word when prompted.
- [ ] Use functions 3 ("increment_count()"), 4 ("get_count()"), and 5 ("get_word()") to test your code.
- [ ] Continue to test until you discover a bug or are satisfied that your implementations are correct.
- [ ] When you have finished, use function 2 ("delete_word_entry()") to release the word entry's memory, then select 0 to return to the main menu, and then select 0 to exit the program.

> ⓘ **Note**
> 
> Whenever you return to the main menu, any existing list will be deleted.
> No memory references survive when moving between one main-menu-option and another.

---

### Creating and Destroying Word Entries

The `create_word_entry()` function allocates space for a `word_entry_t`, and the `delete_word_entry()` function releases that memory.
The `create_word_entry()` function, however, does not yet initialize the word entry.

- [ ] In `create_word_entry()`'s `else` block, copy `word` into `word_entry`'s `word` field.
- [ ] In `create_word_entry()`'s `else` block, set `word_entry`'s `occurrences` field to 0.

When you copy the word, you must actually copy the word and not merely copy the pointer, for two reasons.
The first reason, from a program design perspective, is that you don't know whether the caller might later put a different word in the array that the `word` parameter is in, or the caller might even deallocate that array's memory.
The second reason, from a memory perspective, is that an array embedded in a 'struct' (such as `word_entry_t`'s `word` field) is effectively a constant pointer and cannot be re-assigned.

You do not need to make any changes to `delete_word_entry()`.

### Accessors and Mutators
(*aka*, Getters and Setters)

We want to control the possible changes that other code might make to a word entry.
Indeed, the only reasonable change would be to increase the number of times that the word is found in a book, whenever we encounter that word again.
Similarly, we want to make sure that data that our "getter" functions cannot be used by the caller to make changes to the structure's data.
The `get_count()` function returns a value, so there's no hazard there.
The `get_word()` function returns a pointer to a constant -- while it *is* possible to discard a `const` qualifier, doing so will result in a warning that it will result in undefined behavior.
(The array that the pointer points to isn't actually constant, but the caller is obligated to act as though it is.)

- [ ] In `increment_count()`, increase the word entry's number of occurrences by one.
- [ ] In `get_count()`, return the number of occurrences.
- [ ] In `get_word()`, return a pointer to the word entry's word. (Do *not* make a copy of the word.)

When returning the word entry's word, simply returning the pointer is sufficient -- and desirable.
It is sufficient because the caller is obligated to treat it as a constant.
The alternative, making a copy, is not desirable because the function doesn't expect the caller to provide a destination, which means that the function would have to allocate memory for the destination;
the caller would be unable to later free this memory without discarding the `const` qualifier.

### Testing Your Changes

You can build an executable that uses H.Awk's array-backed list with the command
```shell
cmake --build build --target arraylist
```
<!--
or, if you want to limit each `malloc()` call to no more than 32KB, then use the command \\
\verb+make arraylist "OPTION=-DHOBBLE"+
-->

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
- [ ] Select task 1, "Test word_entry".
  ```
  0) Return to main menu
  1) create_word_entry()
  2) delete_word_entry()
  3) increment_count()
  4) get_count()
  5) get_word()
     Select the function you wish to check:
  ```
- [ ] Select function 1, "create_word_entry()", and enter a word when prompted.

    The word entry will be displayed.
    For example, if your word was "foo" then the output will be:
    ```
    Created --           0 : foo
    ```
- [ ] Use functions 3 ("increment_count()"), 4 ("get_count()"), and 5 ("get_word()") to test your code.
- [ ] Continue to test until you discover a bug or are satisfied that your implementations are correct.
- [ ] When you have finished, use function 2 ("delete_word_entry()") to release the word entry's memory, then select 0 to return to the main menu, and then select 0 to exit the program.

> ⓘ **Note**
>
> Whenever you return to the main menu, any existing list will be deleted.
> No memory references survive when moving between one main-menu-option and another.

---

|              [⬅️](02-getting-started.md)              |      [⬆️](../README.md)      |           [➡️](04-alphabetical-functions.md)           |
|:-------------------------------------------------:|:----------------------------:|:------------------------------------------------------:|
|  [The Books, Business Rules](02-getting-started.md)   | [Front Matter](../README.md) | [Alphabetical Functions](04-alphabetical-functions.md) |
