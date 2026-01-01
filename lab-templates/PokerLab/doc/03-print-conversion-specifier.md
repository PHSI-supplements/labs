## Adding a Conversion Specifier

Before you make any other changes, you should edit *card.c* so that the program compiles without generating any warnings or errors.

- [ ] Determine the conversion specifier that instructs `sprintf()` to convert a signed decimal integer variable into part of a string

You can find a list of conversion specifiers in the textbook's [Appendix C](https://unl.grlcontent.com/compeng2e/page/appendixc#c13).
If you need to do so, you can review the "Printing" section of the textbook's Chapter 1.

- [ ] Place that conversion specifier in `sprintf()`'s format string on line 63 of *card.c*
- [ ] Re-compile the program to make sure there are no more compiler warnings or errors
  - Use the "Build" feature in your IDE, or use the command
    ```
    cmake --build build
    ```

---

|       [⬅️](02-getting-started.md)        |      [⬆️](../README.md)      |            [➡️](04-creating-deck-of-cards.md)            |
|:----------------------------------------:|:----------------------------:|:--------------------------------------------------------:|
| [Getting Started](02-getting-started.md) | [Front Matter](../README.md) | [Creating a Deck of Cards](04-creating-deck-of-cards.md) |
