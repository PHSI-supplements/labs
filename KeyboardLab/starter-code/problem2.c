/**************************************************************************//**
 *
 * @file problem2.c
 *
 * @author (STUDENT -- TYPE YOUR NAME HERE)
 *
 * @brief Functions that students must implement for KeyboardLab to demonstrate
 * understanding that characters are integers.
 *
 ******************************************************************************/

/*
 * KeyboardLab assignment and starter code (c) 2021-23 Christopher A. Bohn
 * KeyboardLab solution (c) the above-named student
 */


/**
 * Analogous to ctype.h's <code>isdigit()</code> function, with a stronger guarantee about the return value.
 * Specifically, this function returns exactly 1 if the argument is a decimal digit (such as '5'), 0 otherwise.
 * This function is implemented without <code>#include</code>ing any files, without using any number keys other than 0
 * and 9 (and 7, which has the & symbol), without using any switch statements, and using at most one if statement.
 *
 * @param character the character to be evaluated
 * @return 1 if the argument is a decimal digit, 0 otherwise
 */
int iz_digit(char character) {
    /* WRITE THIS FUNCTION */
    return -9;
}

/**
 * Analogous to ctype.h's <code>tolower()</code> function.
 * Specifically, if the argument is an uppercase letter, the function returns the corresponding lowercase letter
 * (e.g., 'D' yields 'd'). Otherwise, the function returns the argument, unchanged.
 * This function is implemented without <code>#include</code>ing any files, without using any number keys other than 0
 * and 9 (and 7, which has the & symbol), without using any switch statements, and using at most one if statement.
 *
 * @param character the character to be converted to a lowercase letter (if possible)
 * @return the lowercase version of the argument if it is an uppercase letter, the original character otherwise
 */
char decapitalize(char character) {
    /* WRITE THIS FUNCTION */
    return '\a';
}
