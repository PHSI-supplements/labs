> 📇 **Scenario, continued**
>
> "Thanks for your help," Archie says.
> "Maybe you can help our other developer with the project he's working on."
> A guy walks up.
> He's wearing a Members-Only jacket over a Hawaiian shirt and looks like he might be a comedian's nemesis in another life.
>
> "To protect against corporate espionage, we're writing an authentication system based on counting the words in books.
> To make it work, we need to sort the words and count the number of occurrences of each word.
> I'm using an array-backed list to store a book's words.
> It works fine on my desktop system, but the device from Eclectic Electronics that we're deploying it to has an interesting quirk:
> it has plenty of memory for our needs, but it has 256-byte memory segments, and a memory allocation cannot span more than one segment.
> That's a bit of a problem for the array once the list grows large enough."
>
> You think about the problem for a moment, and then suggest, "What if we replace the array-backed list with a linked list...?"
> You plug in your shiny, new keyboard, tune your satellite radio to the Greatest Hits of the 1920s, and settle in to solving this interesting problem.

## Getting Started

### Compiling and Running

[//]: # (TODO: Finish this section)

This assignment is a little different from the other assignments, in that it has two build targets instead of one,
and in that it has a timeout feature that will terminate the program if it runs too long.
These differences mean there are a few extra options when compiling and running your code.

*We strongly recommend that you leave the timeout feature enabled for most or all of your testing.*
However, if you are using an interactive debugger

#### Configuring the Project

<u>From the Command Line</u>

<u>From VS Code</u>

#### Compiling the Project

<u>From the Command Line</u>

<u>From VS Code</u>

#### Running the Program

<u>From the Command Line</u>

<u>From VS Code</u>

<!--
### Configuring the Project

If you're using an IDE, open the project in the *FooLab* directory (the same directory that has CMakeLists.txt).
It should configure the project for you.
If you're working on your personal computer instead of Nuros, you may be prompted to identify the compiler you'll use.

If you're working from the command line, then navigate to the *FooLab* directory (the same directory that has CMakeLists.txt).
If you're working on Nuros, run the command:
```shell
cmake --preset=default
```
If you're working on your personal computer, run the command:
```shell
cmake --preset=personal-computer
```
or, if you need to specify a particular compiler:
```shell
cmake --preset=personal-computer -DCMAKE_C_COMPILER=/path/to/the/compiler
```

### Compiling the Project

If you're using an IDE, there should be a "Build" button.
In VS Code, you can also select one of these commands from the command palette:
```
CMake: Build                                # Builds all targets
CMake: Build Target                         # Build a specific target
```

If you're working from the command line, then navigate to the *FooLab* directory (the same directory that has CMakeLists.txt) and run the command:
```shell
cmake --build build
```
or, to build a specific target:
```shell
cmake --build build --target foolab
```

### Running the Program

If you're using an IDE, there should be a "Run" button.
In VS Code, you can also select one of these commands from the command palette:
```
CMake: Run Without Debugging
CMake: Debug
```

If you're working from the command line, then navigate to the *FooLab* directory (the same directory that has CMakeLists.txt) and run the command:
```shell
build/foolab
```

-->

### The Books

The starter code includes six files that you can use as inputs.
Three are pre-sorted, and three aren't.
Two are short, only 7 words, which can be useful for debugging.
- "Animals"  (sorted, 7 words)
- "Plants" (unsorted, 7 words)

Two are moderate-sized, 74-125 words, to give you confidence in the correctness of your solution.
- "Cars"   (sorted,  74 words)
- "Food" (unsorted, 125 words)

Two are real books;[^gutenberg] they are large, in excess of 74,000 words, and they are useful to reveal whether you have any memory leaks in your code.
- Mary Shelly's [*Frankenstein; Or, The Modern Prometheus*](https://www.gutenberg.org/ebooks/84) (sorted, 74,363 words, filename: "Frankenstein")
- Arthur Conan Doyle's [*The Lost World*](https://www.gutenberg.org/ebooks/139) (unsorted, 77,268 words, filename "TheLostWorld")

[This assignment's Appendix C](CC-word-tables.md) has a table for each of these book files.
The tables have the challenge words and the number of occurrences for each challenge word.
You may use these files to confirm the correctness of your solution.

Throughout the assignment, we note that if building the list takes more than a few seconds, there is a bug in your code;
You should be able to build a list for *Frankenstein* or *The Lost World* in under a second.
Your code may take longer, but it should not take much longer.

<span style="background-color: yellow;">Some of the tests in *sorted-test.c* will timeout after ten seconds to stop runaway code.
To disable this timeout (such as when debugging with breakpoints), compile the code with</span>
```shell
cmake --preset=timeout-disabled
cmake --build build
```
(to re-enable the timeout, use `cmake --preset=default; cmake --build build`)

You will earn most of the credit for this lab if your code works for pre-sorted files of up to 200 words.
The remaining credit is for making your code work with unsorted files and, when using files of up to 80,000 words, your code can generate a list and find a word in fewer than 20 seconds.

### Business Rules

You are not required to implement the challenge-response app's business rules.
We include them here as a reference, if it helps you to understand the code better.

- All of the book's words are sorted alphabetically without regard to capitalization (for example, "hello" occurs after "Hear" and before "HELP")
- The word occurs *occurrences* times in the book

As a simple example, look at the *Food* file.
After sorting and counting, [we have](CC-word-tables.md#food):

|   *word*    | *occurrences* |
|:-----------:|:-------------:|
|    apple    |       7       |
|   banana    |       4       |
|   carrot    |      15       |
|    date     |       3       |
|  eggplant   |       2       |
|     fig     |       6       |
|   granola   |       9       |
| horseradish |       9       |
|     ice     |       6       |
|    jelly    |       3       |
|    kale     |       1       |
|    lemon    |       2       |
|    mango    |       8       |
|    naan     |       7       |
|   orange    |       5       |
|  pineapple  |       1       |
|   quinoa    |      11       |
|   raisin    |       4       |
|  spaghetti  |      10       |
|   tomato    |      12       |

---

[^gutenberg] The text for these books was obtained from [Project Gutenberg](https://www.gutenberg.org/).
In accordance with Paragraph~1.C of the [Project Gutenberg License](https://www.gutenberg.org/policy/license), all references to Project Gutenberg have been removed from the "derived works" that we are distributing.
(Removing the references to Project Gutenberg was also necessary to ensure that *only* the words from the books are included in the list.)

|           [⬅️](01-stray-values-in-memory.md)           |      [⬆️](../README.md)      |      [➡️](03-word-entries.md)      |
|:------------------------------------------------------:|:----------------------------:|:----------------------------------:|
| [Stray Values in Memory](01-stray-values-in-memory.md) | [Front Matter](../README.md) | [Word Entries](03-word-entries.md) |
