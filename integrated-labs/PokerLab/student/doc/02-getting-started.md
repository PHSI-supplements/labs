> 📇 **Scenario**
> 
> You’re relaxing at your favorite hangout when another customer catches your attention.
> He’s rather large (dare I say, mammoth), a bit hairy, and looking frustrated in front of his laptop.
> 
> <!--![Archie, the Columbian Mammoth statue outside the Nebraska State Museum of Natural History. Photograph by Bohn.](archie.jpg)-->
> <figure>
>   <img src="archie.jpg" width="50%" alt="Archie, the Columbian Mammoth statue outside the Nebraska State Museum of Natural History">
>   <figcaption>Archie. <small>Photograph by Bohn.</small></figcaption>
> </figure>
> 
> "I’m Archie," he says, "and I'm trying to teach myself this card game called Poker.
> I found this source code that I thought I could use to understand Poker better,
> but the code is incomplete, and I don’t entirely understand what’s there.
> Could you explain the code to me, please?"

## Getting Started

The five source code files (*card.h*, *card.c*, *poker.h*, *poker.c*, and *pokerlab.c*) contain the starter code for this assignment<!--, and the text file (*answers.txt*) is where you'll provide some answers to demonstrate your ability to understand part of the starter code<-->.
*CMakeLists.txt* encodes information needed to build the application.
In the *equivalent-java* directory you will find *Card.java* and *Poker.java* that has Java code that is equivalent to the C code.
You do not need to use the Java files, but you may find them useful as a reference to help you understand some differences between Java and C.

The header file *card.h* defines a ``card'' structure, `card_t`, specifies two functions that operate on cards, and defines some useful constants.
The source file *card.c* has the bodies for the specified functions, but some code is missing.
Finally, the source file *poker.c* is supposed to generate a poker hand of five cards, print those five cards, and print what kind of hand it is -- but much of its code is missing.

The only files you will modify in this assignment are <!--*answers.txt*,--> *card.c*<!--,--> and *poker.c*.
Do *not* modify *pokerlab.c*, *card.h*, *poker.h*, nor *CMakeLists.txt*.

Most IDEs will be able to configure the compilation settings from *CMakeLists.txt*, and you can compile the program by clicking on "Build" or something similar.

- If you plan to operate from the command line, you can configure the compilation settings with this command:
  ```
  cmake -B build
  ```
  You can then compile the program with this command:
  ```
  cmake --build build
  ```

When you compile the starter code, it will generate a warning:

```text
card.c:63:30: warning: format string is empty [-Wformat-zero-length]
sprintf(valueString, "", value);
                     ^~
```

<font color="red">You should get in the habit of correcting *any* code that generates a warning!</font>

---

|        [⬅️](01-terminology.md)         |      [⬆️](../README.md)      |             [➡️](03-print-conversion-specifier.md)             |
|:--------------------------------------:|:----------------------------:|:--------------------------------------------------------------:|
| [Poker Terminology](01-terminology.md) | [Front Matter](../README.md) | [Print Conversion Specifier](03-print-conversion-specifier.md) |
