> 📇 **Scenario, continued**
>
> Your keyboard was mistakenly delivered to the Plywood Scenery Cutting Studio instead of the Pleistocene Petting Zoo.
> While that gets sorted out, you "borrow" some tar from the La Brea Tar Pits diorama and use the tar to re-attach your keyboard's missing keys.
> 
> As you fasten a Scrabble tile in place for the *W*, more keys fall off, denying you the use of *+*, *-*, */*, *%*, *5*, and *B*.
> You cannot get any more adhesive, so you sit down to your next programming tasks without those keys.

## Using Bitmasks and Shifting Bits

### The Task

- [ ] Edit *problem3.c* so that
  - `is_even()` returns 1 if the number is even (that is, divisible by 2) and 0 if the number is odd
  - `produce_multiple_of_ten()` will always output a multiple of 10 following a specific formula: if a number is even then divide it by 2;
    otherwise, subtract 1 from the number and multiply the difference by 5 (for example, an input of 7 yields 30 because $(7-1) \times 5 = 30$);
    repeat until the last decimal digit is 0.
    - These numbers are guaranteed to be non-negative.

You may not use addition (`+`), subtraction (`-`), division (`/`), nor modulo (`%`).
You also may not use the number `5` nor the letter `b`.
(Exceptions: you *may* use the forward-slash (`/`) for comments, and the percent-sign (`%`) that is already present in the `sprintf()` calls' format strings is allowed)}

> #### Hints
> - Following the weighted-sum technique to convert between binary and decimal (or by examining the textbook's Table 2.1), 
>   you will note that <span style="background-color: yellow;">all even numbers have a 0 as their least significant bit</span>, 
>   and <span style="background-color: yellow;">all odd numbers have a 1 as their least significant bit</span>
> - Less obvious is that you can <span style="background-color: yellow;">subtract 1 from an odd number by changing its least significant bit to a 0</span>
> - As we will cover in Chapter 3, you can <span style="background-color: yellow;">halve a number by shifting its bits to the right by one</span>
> - You can create an integer by <span style="background-color: yellow;">producing its bit pattern through a series of bit operations</span>

- [ ] Build the executable in your IDE or with the command `cmake --build build`.
  Be sure to fix both errors and warnings.
- [ ] Run the executable in your IDE or with the command `build/keyboardlab` and select option 3 ("check problem 3"). \\
  You will be prompted to enter a number.
  The program will then report whether it is even, and it will print the generated multiple of ten.

Here are some test cases you might try:

| input | even? | multiple of ten |
|:-----:|:-----:|:---------------:|
|   7   |  no   |       30        |
|  56   |  yes  |       30        |
|  57   |  no   |       280       |
|  58   |  yes  |       140       |
|  300  |  yes  |       300       |
|  301  |  no   |      1500       |
|  302  |  yes  |       750       |

<font color="red">
You can double-check that you aren't using disallowed keys by running the constraint-checking Python script:

```
ctest --test-dir build --output-on-failure -R keyboardlab3
```
</font>

The `is_even()` function is worth four points, two for correctly determining that an integer is even and  two for correctly determining that an integer is odd.
Partial credit is available for determining that a character is even but returning a non-zero value other than 1.
You will receive no credit if you simply hard-code a return value.

The `produce_multiple_of_ten()` function is worth four points, one each for: assigning the value 5 to the variable `five`, dividing an even number by 2, subtracting 1 from an odd number, and having the correct functionality.

---

|               [⬅️](03-characters-as-numbers.md)               |      [⬆️](../README.md)      |         [➡️](05-grading.md)          |
|:-------------------------------------------------------------:|:----------------------------:|:------------------------------------:|
| [Treating Characters as Numbers](03-characters-as-numbers.md) | [Front Matter](../README.md) | [Turn-In and Grading](05-grading.md) |
