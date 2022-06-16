/*
 * STUDENT: (Type your name here)
 */

/*
 * IntegerLab (c) 2018-21 Christopher A. Bohn
 */

/******************************************************************************
 * In this lab, students are required to implement integer arithmetic for
 * unsigned 16-bit integers and signed (twos complement) 16-bit integers using
 * only bitwise and (&), bitwise or (|), bitwise xor (^), bitwise complement
 * (~), and bit shifts (<< and >>). DO NOT USE built-in addition (+),
 * subtraction (-), multiplication (*), division (/), nor modulo (%).
 ******************************************************************************/

#include "alu.h"

/* Adds the two arguments and stores the sum in the return structure's result
 * field.  If the operation overflowed then the overflow flag is set. */
addition_subtraction_result add(uint16_t augend, uint16_t addend) {
    addition_subtraction_result addition;
    addition.result = augend + addend;                          // THIS IS DISALLOWED
    addition.overflow = false;                                  // THIS IS WRONG
    return addition;
}

/* Subtracts the second argument from the first, stores the difference in the
 * return structure's result field.  If the operation overflowed then the
 * overflow flag is set. */
addition_subtraction_result subtract(uint16_t menuend, uint16_t subtrahend) {
    uint16_t augend = menuend;
    uint16_t addend = (uint16_t)(-subtrahend);                  // THIS IS DISALLOWED
    return add(augend, addend);
}

/* Multiplies the two arguments.  The function stores lowest 16 bits of the
 * product in the return structure's product field and the full 32-bit product
 * in the full_product field.  If the product doesn't fit in the 16-bit
 * product field then the overflow flag is set. */
multiplication_result multiply(uint16_t multiplicand, uint16_t multiplier) {
    multiplication_result multiplication;
    multiplication.product = multiplicand * multiplier;         // THIS IS DISALLOWED
    multiplication.full_product = multiplicand * multiplier;    // THIS IS DISALLOWED
    multiplication.overflow = false;                            // THIS IS WRONG
    return multiplication;
}

/* Divides the first argument by the second.  The function stores the quotient
 * in the return structure's quotient field and the the remainder in the
 * remainder field.  If the divisor is zero then the quotient and remainder
 * fields should be ignored, and the division_by_zero field should be set. */
division_result divide(uint16_t dividend, uint16_t divisor) {
    division_result division;
    if (divisor) {
        division.quotient = dividend / divisor;                 // THIS IS DISALLOWED
        division.remainder = dividend % divisor;                // THIS IS DISALLOWED
    }
    division.division_by_zero = false;                          // THIS IS WRONG
    return division;
}
