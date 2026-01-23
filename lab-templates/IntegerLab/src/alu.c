/**************************************************************************//**
 *
 * @file alu.c
 *
 * @author (TYPE YOUR NAME HERE)
 *
 * @brief Functions that students must implement for IntegerLab to demonstrate
 * understanding of boolean logic and bit-limited integer arithmetic.
 *
 ******************************************************************************/

/*
 * IntegerLab assignment and starter code (c) 2018-26 Christopher A. Bohn
 * IntegerLab solution (c) the above-named student
 */

#include "alu.h"

/**
 * Determines whether a bit vector, when interpreted as a two's complement signed integer, is negative.
 * @param value the bit vector to be evaluated
 * @return 1 if the interpreted argument is less than zero; 0 otherwise
 */
bool is_negative(uint16_t value) {
    return false;
}

/**
 * Determines whether two values are equal. Two values are considered equal if their bit vectors are identical.
 * @param value1 the first value for the comparison
 * @param value2 the second value for the comparison
 * @return 1 if the two arguments are equal; 0 otherwise
 */
bool equal(uint16_t value1, uint16_t value2) {
    return false;
}

/**
 * Determines whether two values are not equal. Two values are considered equal if their bit vectors are identical.
 * @param value1 the first value for the comparison
 * @param value2 the second value for the comparison
 * @return 0 if the two arguments are equal; 1 otherwise
 */
bool not_equal(uint16_t value1, uint16_t value2) {
    return false;
}

/**
 * Computes the logical inverse of the argument.
 * @param value the value to be inverted; 0 is considered `false`, and non-zero values are considered `true`
 * @return 1 if the argument is 0; 0 otherwise
 */
bool logical_not(uint32_t value) {
    return false;
}

/**
 * Computes the logical conjunction of the arguments.
 * @param value1 the first operand for the conjunction; 0 is considered `false`, and non-zero values are considered `true`
 * @param value2 the second operand for the conjunction; 0 is considered `false`, and non-zero values are considered `true`
 * @return 1 if both arguments are `true`; 0 otherwise.
 */
bool logical_and(uint32_t value1, uint32_t value2) {
    return false;
}

/**
 * Computes the logical disjunction of the arguments.
 * @param value1 the first operand for the disjunction; 0 is considered `false`, and non-zero values are considered `true`
 * @param value2 the second operand for the disjunction; 0 is considered `false`, and non-zero values are considered `true`
 * @return 1 if either (or both) argument is `true`; 0 otherwise.
 */
bool logical_or(uint32_t value1, uint32_t value2) {
    return false;
}

/**
 * Zero-extends a value from a smaller data size to a larger data size.
 *
 * The lower `from_size` bits of `value` are interpreted as an unsigned integer.
 * Those bits are copied unchanged into the result. Any bits between `from_size`
 * and `to_size` are set to 0. All bits above the lower `to_size` bits are
 * unchanged from the original value.
 *
 * For example, zero-extending an 8-bit (`ONE_BYTE`) value to 16 bits
 * (`TWO_BYTES`) preserves bits 7..0, sets bits 15..8 to 0, and leaves bits
 * 31..16 unchanged.
 *
 * @pre `to_size` >= `from_size`
 * @pre `to_size` and `from_size` must be 8 (`ONE_BYTE`), 16 (`TWO_BYTES`), or 32 (`FOUR_BYTES`)
 *
 * @param value     The original value containing the bits to be extended.
 * @param from_size The size (in bits) of the original value to be extended.
 * @param to_size   The size (in bits) of the destination value.
 * @return          The zero-extended value.
 */
uint32_t zero_extend(uint32_t value, data_size_t from_size, data_size_t to_size) {
    assert(to_size >= from_size);
    uint32_t lower_preservation_mask = LOWER_BITS_MASK(from_size);
    uint32_t upper_preservation_mask = 0xFFFF'FFFFuL << to_size;
    return (value & upper_preservation_mask) | (value & lower_preservation_mask);
}

/**
 * Sign-extends a value from a smaller data size to a larger data size.
 *
 * The lower `from_size` bits of `value` are interpreted as a signed integer in
 * two’s-complement representation. Those bits are copied unchanged into the
 * result. Bits between `from_size` and `to_size` are filled with copies of the
 * sign bit (bit `from_size - 1`). All bits above the lower `to_size` bits are
 * unchanged from the original value.
 *
 * For example, sign-extending an 8-bit (`ONE_BYTE`) value to 16 bits
 * (`TWO_BYTES`) copies bit 7 into bits 15..8, while preserving the original
 * lower 8 bits and leaving bits 31..16 unchanged.
 *
 * @pre `to_size` >= `from_size`
 * @pre `to_size` and `from_size` must be 8 (`ONE_BYTE`), 16 (`TWO_BYTES`), or 32 (`FOUR_BYTES`)
 *
 * @param value     The original value containing the bits to be extended.
 * @param from_size The size (in bits) of the original signed value.
 * @param to_size   The size (in bits) of the destination value.
 * @return          The sign-extended value.
 */
uint32_t sign_extend(uint32_t value, data_size_t from_size, data_size_t to_size) {
    assert(to_size >= from_size);
    uint32_t lower_preservation_mask = LOWER_BITS_MASK(from_size);
    uint32_t upper_preservation_mask = 0xFFFF'FFFFuL << to_size;
    uint32_t sign_bit = value & (1L << (from_size - 1));    /* some students may prefer to check the from_size and use (1<<7) or (1<<15) accordingly */
    uint32_t sign_extension;
    if (sign_bit) {
        sign_extension = 0xFFFF'FFFF & ~upper_preservation_mask & ~lower_preservation_mask;
    } else {
        sign_extension = 0;
    }
    return (value & upper_preservation_mask) | sign_extension | (value & lower_preservation_mask);
}

/**
 * Performs binary addition for one bit position.
 * Given input bits a, b, and c_in, computes sum = a + b + c, with c_out (carry_out) as 0 or 1 depending on whether or
 * not the full sum fits into a single bit.
 * @param bits the `struct` with the input bits
 * @return The `struct` with the output (and input) bits
 */
one_bit_adder_t one_bit_full_addition(one_bit_adder_t bits) {
//    bits.sum = ...;
//    bits.c_out = ...;
    return bits;
}

/**
 * Uses 32 one-bit full adders (or, equivalently, uses 1 one-bit full adder 32 times) to add two 32-bit integers.
 * While a carry-in bit is provided for the least-significant bit, the carry-out bit from the most-significant bit is
 * not preserved (as it is not needed for any part of this assignment).
 * @param value1 the first number to be added
 * @param value2 the second number to be added
 * @param initial_carry_in The carry-in bit for the least-significant bit's adder
 * @return the 32-bit sum of the arguments
 */
uint32_t ripple_carry_addition(uint32_t value1, uint32_t value2, uint8_t initial_carry_in) {
    [[maybe_unused]] uint8_t carry = initial_carry_in & 0x1;        // [[maybe_unused]] to suppress warning until students implement ripple_carry_addition()
    uint32_t sum = 0;
    return sum;
}

/**
 * Adds two 16-bit integers. The arguments are bit vectors that can be interpreted either as unsigned integers or as
 * signed integers. After computing the sum, this function determines whether overflow occurs when the bit vectors are
 * interpreted as unsigned integers, and this function also determines whether overflow occurs when the bit vectors are
 * interpreted as signed integers.
 *
 * This function does not alter the ALU's `supplemental_result` field, and it sets the ALU's
 * `divide_by_zero` flag to 0.
 *
 * @param augend the number to be added to
 * @param addend the number to be added to the augend
 * @return the sum in the ALU's `result` field, and the `unsigned_overflow` and `signed_overflow` flags set appropriately
 */
alu_result_t add(uint16_t augend, uint16_t addend) {
    alu_result_t sum = {};          // empty initializer to suppress uninitialized variable warning in the starter code
    return sum;
}

/**
 * Subtracts two 16-bit integers. The arguments are bit vectors that can be interpreted either as unsigned integers
 * or as signed integers. After computing the difference, this function determines whether overflow occurs when the bit
 * vectors are interpreted as unsigned integers, and this function also determines whether overflow occurs when the bit
 * vectors are interpreted as signed integers.
 *
 * This function does not alter the ALU's `supplemental_result` field, and it sets the ALU's
 * `divide_by_zero` flag to 0.
 *
 * @param menuend the number to be subtracted from
 * @param subtrahend the number to be subtracted from the menuend
 * @return the difference in the ALU's `result` field, and the `unsigned_overflow` and `signed_overflow` flags set appropriately
 */
alu_result_t subtract(uint16_t menuend, uint16_t subtrahend) {
    alu_result_t difference = {};   // empty initializer to suppress uninitialized variable warning in the starter code
    return difference;
}

/**
 * Multiplies two 16-bit integers, producing a 32-bit integer. The second argument *must* be zero or a power of
 * two.
 * @param value the number to be multiplied
 * @param power_of_two the number that the first is to be multiplied by
 * @return the full product of the two arguments
 */
uint32_t multiply_by_power_of_two(uint16_t value, uint16_t power_of_two) {
    assert(is_zero(power_of_two) || is_power_of_two(power_of_two));
    return 0;
}

/**
 * Multiplies two 16-bit integers. The arguments are bit vectors that are interpreted as unsigned integers. The lower
 * 16 bits of the full product are placed in the ALU's `result` field, and the upper 16 bits of the full
 * product are placed in the ALU's `supplemental_result` field.
 *
 * This function sets the ALU's `divide_by_zero` flag to 0 but it does not alter the ALU's
 * `unsigned_overflow` and `signed_overflow` flags.
 *
 * @param multiplicand the number to be multiplied
 * @param multiplier the number that the first is to be multiplied by
 * @return the product in the ALU's `result` and `supplemental_result` fields
 */
alu_result_t unsigned_multiply(uint16_t multiplicand, uint16_t multiplier) {
    alu_result_t product = {};      // empty initializer to suppress uninitialized variable warning in the starter code
    return product;
}

/**
 * Divides two 16-bit integers. The arguments are bit vectors that are interpreted as unsigned integers.
 *
 * The divisor *must* be zero or a power of two.
 *
 * If the divisor is non-zero, the quotient is placed in the ALU's `result` field, the modulus (or
 * remainder) is placed in the ALU's `supplemental_result` field, and the `divide_by_zero` flag
 * is set to 0.
 *
 * If the divisor is zero, the ALU's `divide_by_zero` flag is set to 1 and no guarantees are made about
 * the contents of the `result` and `supplemental_result` fields.
 *
 * Regardless, the ALU's `unsigned_overflow` and `signed_overflow` flags are not altered.
 *
 * @param dividend the number to be divided
 * @param divisor the number that divides the first
 * @return the ALU's `divide_by_zero` flag set appropriately, and the quotient in the ALU's `result` field and the remainder in the `supplemental_result` field when these are mathematically defined
 */
alu_result_t unsigned_divide(uint16_t dividend, uint16_t divisor) {
    alu_result_t quotient = {};     // empty initializer to suppress uninitialized variable warning in the starter code
    return quotient;
}

/*
 * SIGNED_MULTIPLY AND SIGNED_DIVIDE ARE FOR BONUS CREDIT.
 * YOU ARE NOT REQUIRED AT ATTEMPT THEM.
 */

/**
 * Multiplies two 16-bit integers. The arguments are bit vectors that are interpreted as signed integers. The lower
 * 16 bits of the full product are placed in the ALU's `result` field, and the upper 16 bits of the full
 * product are placed in the ALU's `supplemental_result` field.
 *
 * This function sets the ALU's `divide_by_zero` flag to 0 but it does not alter the ALU's
 * `unsigned_overflow` and `signed_overflow` flags.
 *
 * @param multiplicand the number to be multiplied
 * @param multiplier the number that the first is to be multiplied by
 * @return the product in the ALU's `result` and `supplemental_result` fields
 */
alu_result_t signed_multiply(uint16_t multiplicand, uint16_t multiplier) {
    alu_result_t product = {};      // empty initializer to suppress uninitialized variable warning in the starter code
    return product;
}

/**
 * Divides two 16-bit integers. The arguments are bit vectors that are interpreted as signed integers.
 *
 * The divisor *must* be zero or a power of two.
 *
 * If the divisor is non-zero, the quotient is placed in the ALU's `result` field, the modulus (or
 * remainder) is placed in the ALU's `supplemental_result` field, and the `divide_by_zero` flag
 * is set to 0.
 *
 * If the divisor is zero, the ALU's `divide_by_zero` flag is set to 1 and no guarantees are made about
 * the contents of the `result` and `supplemental_result` fields.
 *
 * Regardless, the ALU's `unsigned_overflow` and `signed_overflow` flags are not altered.
 *
 * @param dividend the number to be divided
 * @param divisor the number that divides the first
 * @return the ALU's `divide_by_zero` flag set appropriately, and the quotient in the ALU's `result` field and the remainder in the `supplemental_result` field when these are mathematically defined
 */
alu_result_t signed_divide(uint16_t dividend, uint16_t divisor) {
    alu_result_t quotient = {};     // empty initializer to suppress uninitialized variable warning in the starter code
    return quotient;
}
