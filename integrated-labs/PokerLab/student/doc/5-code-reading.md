## Study the Code in *poker.c*

- [ ] Open the [PokerLab code reading](https://canvas.unl.edu/courses/200913/quizzes/468941) quiz in Canvas.

When you provide your answers in <!-- *answers.txt* --> the Canvas quiz, bear in mind that while it's good to know that you can read code, <font color="red">what we're really looking for is that you understand C's logical boolean operations</font>.
Not boolean operations in general, but <u>C's logical boolean operations</u>.
You will receive half-credit for demonstrating that you understand boolean operations in general,
but you will receive full-credit only if you demonstrate that you <u>understand what the outputs of C's logical boolean operations are</u> and what they mean,
and that you fully understand <u>how the inputs to C's logical boolean operations are interpreted</u>.

### Collaboration Rules

***For this part of the assignment***, you may discuss the code and its behavior with other students.

### Code to Study

#### Simple Boolean Logic Example 1

- [ ] Look at the code for `is_pair()`.

Notice that the parameter `hand`'s type is `card_t *`;
that is, `hand` is a pointer to a `card_t`.
In the code, though, we treat `hand` as though it were an array.
This is because in C, array variables are pointers, and we can treat pointers as array variables.
Notice also that `hand` is modified with the `const` keyword;
this states that the `is_pair()` function should treat the `hand` as a read-only array.
Now look at the rest of the code in `is_pair()`.

Why does `is_pair()` return a **1** when the hand contains at least one pair?
Why does it return a **0** when the hand contains no pairs?
If you can't determine this on your own, you may talk it over with other students or the TA.

<!-- - [ ] Type your answer in *answers.txt*. -->
- [ ] Type your answer in the Canvas quiz.

#### Simple Boolean Logic Example 2

- [ ] Look at the code for `is_flush()`.

Why does `is_flush()` return a **1** when all cards in the hand have the same suit?
Why does it return a **0** when at least two cards have different suits than each other?
If you can't determine this on your own, you may talk it over with other students or the TA.

<!-- - [ ] Type your answer in *answers.txt*. -->
- [ ] Type your answer in the Canvas quiz.

#### A More Interesting Boolean Logic Example

- [ ] Look at the code for `is_straight()`.

This is a little more challenging to understand than `is_pair()` and `is_flush()`.

> 💡 **Food for Thought**
> 
> It would have been more (ahem) straight-forward to implement `is_straight()` as:
> ```c
> int straight = 1;
> for (int i = 0; i < size_of_hand - 1; i++) {
>     straight = straight && (hand[i].value == hand[i + 1].value - 1);
> }
> return straight;
> ```
> Instead of using a logical-AND, we implemented `is_straight()` using addition and the awkwardly-named `not_straight` variable.
> There must be a point we're trying to make.

Why does `is_straight()` return a **1** when all cards in the hand are in sequence?
Why does it return a **0** when they are not in sequence?
If you can't determine this on your own, you may talk it over with other students or the TA.

*Suggestion*: set a breakpoint on this line:
```c
not_straight = not_straight + abs(hand[i + 1].value - hand[i].value - 1);
```
and launch the debugger.
(Or, if you're using gdb from the command line, launch the debugger and set a breakpoint on that line.)
Observe the changes to `not_straight`'s value with the hand 2♣️ 3♦️ 5♦️ 5♥️ 9♠️.

<!-- - [ ] Type your answer in *answers.txt*. -->
- [ ] Type your answer in the Canvas quiz.

#### Pointer Arithmetic

- [ ] Look at the code for `is_two_pair()`.

Recall that in C, array variables are pointers.
The assignment `partial_hand = hand + i` makes use of *pointer arithmetic*.
- If the assignment were `partial_hand = hand` then it would assign `hand`'s base address to `partial_hand`,
  and so `partial_hand` would point to the $0^{th}$ element of `hand`.
- The expression $hand+i$ generates the address for the $i^{th}$ element of `hand`,
  and so `partial_hand = hand + i` assigns to `partial_hand` the address of the $i^{th}$ element of `hand`.

This effectively makes `partial_hand` an array such that $\forall j : partial\_hand[j] = hand[i+j]$.

You may find it interesting to set a breakpoint in `is_to_pair()` and use the debugger to observe the changes to the address stored in `partial_hand`.

- [ ] Examine the remaining starter code in *poker.c* to make sure you understand it.

---

|            [⬅️](4-creating-deck-of-cards.md)            |      [⬆️](../README.md)      |             [➡️](6-characterize-hands.md)              |
|:-------------------------------------------------------:|:----------------------------:|:------------------------------------------------------:|
| [Creating a Deck of Cards](4-creating-deck-of-cards.md) | [Front Matter](../README.md) | [Characterizing a Poker Hand](6-characterize-hands.md) |
