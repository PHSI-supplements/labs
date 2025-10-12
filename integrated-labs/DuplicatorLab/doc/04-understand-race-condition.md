## Understand the Race Condition

There is a file included with the starter code, *threelines.txt* that contains three lines of text.
The race condition in the starter code is so pronounced that it can cause errors in the output even when copying only three lines:

```text
% cat data/threelines.txt
first line
second line
third line
% build/duplicator data/threelines.txt copy.txt; cat copy.txt
second line
second line
second line
third line
% build/duplicator data/threelines.txt copy.txt; cat copy.txt
first line
third line
third line
```

### An Example Interleaving

We can try to understand the race condition by thinking about the program's *valid interleavings*.
Using the line numbering from [the previous section](03-understanding-code.md), we can describe an interleaving that would produce the **correct** output:

```text
     2
     3
     4
     5   (read_original enters loop)
              B
              C
              D
              E   (write_copy enters loop)
     6   (buffer is empty)
     7   (status = BUFFER_HAS_DATA)
     8
     9   ("first line" placed in buffer)
              F   (buffer has data)
              G   (status = BUFFER_IS_EMPTY)
              H   ("first line" copied from buffer)
              I
     5
     6   (buffer is empty)
     7   (status = BUFFER_HAS_DATA)
     8
     9   ("second line" placed in buffer)
     5
     6   (buffer has data)
    14
              E
              F   (buffer has data)
              G   (status = BUFFER_IS_EMPTY)
              H   ("second line" copied from buffer)
              I
     5
              E
              F   (buffer is empty)
              J   (buffer is empty)
              M
     6   (buffer is empty)
     7   (status = BUFFER_HAS_DATA)
     8
     9   ("third line" placed in buffer)
              E
              F   (buffer has data)
              G   (status == BUFFER_IS_EMPTY)
              H   ("third line" copied from buffer)
              I
     5
     6   (buffer is empty)
     7   (status = BUFFER_HAS_DATA)
     8   (fgets returns NULL)
    11   (status = FINISHED)
    12   (loop termination condition)
     5
    18
              E
              F   (finished)
              J   (finished)
              K   (loop termination condition)
              E
              P
```

### Your Task: Show that an Incorrect Output is Possible

- [ ] Determine a valid interleaving that produces this output:
  ```text
  % build/duplicator data/threelines.txt copy.txt; cat copy.txt
  first line
  third line
  third line
  ```

- [ ] Place your answer in *answers.txt*.
  > 💡 **Tip**
  > 
  > We recommend including parenthetical remarks because they may help you to think about the state of the system at various points in your proposed interleaving.

---

|             [⬅️](03-understanding-code.md)              |      [⬆️](../README.md)      |            [➡️](05-remove-race-condition.md)             |
|:-------------------------------------------------------:|:----------------------------:|:--------------------------------------------------------:|
| [Understand the Starter Code](03-understanding-code.md) | [Front Matter](../README.md) | [Remove the Race Condition](05-remove-race-condition.md) |
