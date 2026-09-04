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

This assignment is a little different from the other assignments, in that it has two build targets instead of one.

#### Compiling the Project

<u>From the Command Line</u>

- `cmake --build build --target arraylist` -- compile the program using the array-backed list that's in the starter code
- `cmake --build build --target linkedlist` -- compile the program using the linked list that you'll write
- `cmake --build build` -- compile both versions of the program, useful for running the two side-by-side during testing

<u>From VS Code</u>

From the Command Palette, either select `CMake: Build Target` and choose one of:

- `arraylist EXECUTABLE` -- compile the program using the array-backed list that's in the starter code
- `linkedlist EXECUTABLE` -- compile the program using the linked list that you'll write

or, to compile both versions of the program, select `CMake: Build`

<u>From CLion</u>

Select `arraylist` or `linkedlist` from the Run/Debug Configurations drop-down menu, and then click the "🔨" (Build) button to the left of the Run/Debug Configurations drop-down menu.

#### Running the Program

<u>From the Command Line</u>

- `build/arraylist` -- run the program using the array-backed list that's in the starter code
- `build/linkedlist` -- run the program using the linked list that you'll write

<u>From VS Code</u>

From the Command Pallet, select `Set Launch/Debug Target` and choose either `arraylist` or `linkedlist`, and then click on the "Run" icon as normal.
If you want to run both versions of the program side-by-side, you'll need to do so from the command line.

<u>From CLion</u>

Select `arraylist` or `linkedlist` from the Run/Debug Configurations drop-down menu, and then click either the "▶" (Run) button or the "🪲" (Debug) button to the right of the Run/Debug Configurations drop-down menu.
If you want to run both versions of the program side-by-side, you'll need to do so from the command line.

### The Books

The `data/` directory includes six files that you can use as inputs.
Three are pre-sorted, and three aren't.
Two are short, only 7 words, which can be useful for debugging.
- "data/Animals"  (sorted, 7 words)
- "data/Plants" (unsorted, 7 words)

Two are moderate-sized, 74-125 words, to give you confidence in the correctness of your solution.
- "data/Cars"   (sorted,  74 words)
- "data/Food" (unsorted, 125 words)

Two are real books;[^gutenberg] they are large, in excess of 74,000 words, and they are useful to reveal whether you have any memory leaks in your code.
- Mary Shelly's [*Frankenstein; Or, The Modern Prometheus*](https://www.gutenberg.org/ebooks/84) (sorted, 74,363 words, filename: "data/Frankenstein")
- Arthur Conan Doyle's [*The Lost World*](https://www.gutenberg.org/ebooks/139) (unsorted, 77,268 words, filename "data/TheLostWorld")

[This assignment's Appendix C](CC-word-tables.md) has a table for each of these book files.
The tables have the challenge words and the number of occurrences for each challenge word.
You may use these files to confirm the correctness of your solution.

Throughout the assignment, we note that if building the list takes more than a few seconds, there is a bug in your code;
You should be able to build a list for *Frankenstein* or *The Lost World* in under a second.
Your code may take longer, but it should not take much longer.

You will earn most of the credit for this lab if your code works for pre-sorted files of up to 200 words.
The remaining credit is for making your code work with unsorted files and, when using files of up to 80,000 words, your code can generate a list and find a word in fewer than 20 seconds.

<span style="background-color: yellow;">You should be able to build a list from a file of up to 200 words in only a couple of seconds.
If it longer than that, you may have an infinite loop running.
The longer it takes, the more likely it is that you have an infinite loop.</span>

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
