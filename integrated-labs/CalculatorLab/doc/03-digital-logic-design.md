> 📇 **Scenario continued**
>
> You sit down with Herb to discuss the plan.
> "We'll place the calculator's output on a seven-segment display.
> We already have a ROM design that will drive the segments from BCD inputs,
> but it's fairly sparse.
> I think encoding the logic into a PLA will have a smaller footprint on the silicon die."
> 
> Herb pauses for a moment and then continues,
> "The AND plane in the PLA we're using can handle up to three variables per AND gate,
> and the OR plane can handle up to three product terms per OR gate.
> If you can design the logic to be even more compact than that, that'd be nice,
> but a maximum of three variables per product term and a maximum three product terms per expression are the limits."

## Digital Logic Design

In the first part of this assignment, you will design the digital logic to display decimal numerals on a seven-segment display.
You will *not* implement the logic using discrete logic gates.
Instead, you will formulate minimal sum-of-products expressions that could be programmed into a PLA.

> ⚙️ **Simulated Hardware**
>
> In lieu of actually programming a PLA, you will place the appropriate sum-of-products expressions in the return statements of seven C functions.

### Reference Glyphs

- [ ] [Attach the Seven-Segment Display Module to the Cow Pi](BB-peripherals.md).
- [ ] Place both of the Cow&nbsp;Pi's switches in the *left* position.
- [ ] Compile the program and upload it to the Cow&nbsp;Pi.

The rightmost digit on the display module will repeatedly cycle through the decimal numerals using the simulated ROM.
The digit next to it will repeatedly cycle through the decimal numerals using the simulated PLA;
however, since you haven't implemented the digital logic yet, the second digit remains blank.

As you add functionality to the simulated PLA, you can check your work by comparing the on/off states of the segments between the two digits.

### Implement the B Segment

The B segment's Karnaugh map is:

|                              | β3 β2 = 00<br>/β3 /β2 | β3 β2 = 01<br>/β3 β2 | β3 β2 = 11<br>β3 β2 | β3 β2 = 10<br>β3 /β2 |
|:----------------------------:|:---------------------:|:--------------------:|:-------------------:|:--------------------:|
|  **β1 β0 = 00<br>/β1 /β0**   |           1           |          1           |          X          |          	1          |
|   **β1 β0 = 01<br>/β1 β0**   |           1           |          0           |          X          |          	1          |
|   **β1 β0 = 11<br>β1 β0**    |           1           |          1           |          X          |          	X          |
|   **β1 β0 = 10<br>β1 /β0**   |           1           |          0           |          X          |          	X          |

> 🪢 **Reminder**
>
> The variables are the bits for the binary encodings of the numerals.
> We do not care about the output for encodings that do not correspond to decimal numerals.

- [ ] Cover every cell that contains a `1` (and possibly some `X`s) using as few power-of-two-sized groupings as possible.
- [ ] Convert each grouping into a product term, and form a sum-of-products expression for the B segment.

  > 📝 **Grading Note**
  >
  > Use at most three variables in each product term, and use at most three product terms.

- [ ] Express the sum-of-products using the following syntax:
    - Use `!` to invert a variable (do *not* use `~`, or you will get erroneous output)
    - Join each minterm's variables with `&&`
    - Enclose each minterm in parentheses
    - Join the minterms with `||`
    - For example: `(I && !J && K) || (!I && L) || (J)`
- [ ] Locate the `get_segment_B()` in *seven_segment_pla.c*, and have the function return the sum-of-products expression.
- [ ] Compile the program and upload it to the Cow Pi.
- [ ] Compare the on/off states of the B segment between the ROM-driven digit and the PLA-driven digit to confirm that your expression is correct.

### Implement the Remaining Segments

For each of the remaining segments:

- [ ] Prepare a Karnaugh map for that segment.
- 
  > 🐛 **Bug in Chapter 10 Quiz**
  > 
  > The Karnaugh map for the E segment in the Chapter 10 quiz, question 3, has a bug.
  > The available answers and the answer key for that question are written to match the buggy Karnaugh map;
  > however, you should not blindly copy that Karnaugh map for this assignment.

- [ ] Form a minimal sum-of-products expression for that segment.

  > 📝 **Grading Note**
  >
  > Use at most three variables in each product term, and use at most three product terms.

- [ ] Express the sum-of-products using the syntax described earlier.
- [ ] Locate the corresponding function in *seven_segment_pla.c*, and have the function return the sum-of-products expression.
- [ ] Compile the program and upload it to the Cow Pi.
- [ ] Compare the on/off states of that segment between the ROM-driven digit and the PLA-driven digit to confirm that your expression is correct.

When every segment of the PLA-driven digit behaves identically to the ROM-driven digit, you have completed the digital logic design portion of the assignment.

---

|          [⬅️](02-seven-segment.md)           |      [⬆️](../README.md)      |         [➡️](04-polling.md)         |
|:--------------------------------------------:|:----------------------------:|:-----------------------------------:|
| [Seven Segment Display](02-seven-segment.md) | [Front Matter](../README.md) | [Polling Discussion](04-polling.md) |
