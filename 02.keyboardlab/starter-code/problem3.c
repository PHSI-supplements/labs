/*
 * STUDENT: (Type your name here)
 */

/*
 * KeyboardLab (c) 2021 Christopher A. Bohn
 */

/******************************************************************************
 * This code will output a multiple of ten based on a particular formula.
 * The implementation cannot use addition (+), subtraction (-), division (/),
 * nor modulo (%). The implementation may not use the literal number 5.
 * This will require use of bitwise AND, bitwise OR, left-shift, and
 * right-shift.
 ******************************************************************************/

#include <stdio.h>
#include <math.h>

/* Returns 1 if the argument is an even number, and returns 0 if the argument
 * is an odd number */
int is_even(int number) {
    /* WRITE THIS FUNCTION */
    return 0;
}

/* Outputs a multiple of 10 by repeatedly applying a formula:
 * - if a number is negative then set it to 0
 * - if a positive number is even then divide it by 2
 * - if a positive number is odd then subtract 1 and multiply the difference by 5 */
int produce_multiple_of_ten(int seed) {
    int five = 0;                   /* CREATE THE VALUE 5 */
    int subtract_one_mask = 0;      /* CREATE A BITMASK YOU CAN USE TO SUBTRACT 1 */
    int number = seed > 0 ? seed : 0;
    int position_of_last_digit = number > 0 ? (int)log10(number) : 0;
    char number_string[33];
    sprintf(number_string, "%d", number);
    while (number_string[position_of_last_digit] != '0') {
        if (is_even(number)) {
            number = 0;             // DIVIDE BY 2
        } else {
            number = 0;             // SUBTRACT 1 AND MULTIPLY THE DIFFERENCE BY 5
        }
        position_of_last_digit = number > 0 ? (int)log10(number) : 0;
        sprintf(number_string, "%d", number);
    }
    return number;
}
