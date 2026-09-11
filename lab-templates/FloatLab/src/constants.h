/**************************************************************************//**
 *
 * @file constants.h
 *
 * @author (TYPE YOUR NAME HERE)
 *
 * @brief Named constants for use in FloatLab.
 *
 ******************************************************************************/

/*
 * FloatLab assignment and starter code (c) 2019-26 Christopher A. Bohn
 * FloatLab solution (c) the above-named student
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

/* BITMASKS TO EXTRACT SPECIFIC BITFIELDS */

[[maybe_unused]] constexpr uint32_t SIGN_BIT_MASK      = 0x0000'0000;
[[maybe_unused]] constexpr uint32_t EXPONENT_BITS_MASK = 0x0000'0000;
[[maybe_unused]] constexpr uint32_t FRACTION_BITS_MASK = 0x0000'0000;

/* PROPERTIES OF 32-BIT FLOATING POINT NUMBERS */

[[maybe_unused]] constexpr int EXPONENT_BIAS = 0;
[[maybe_unused]] constexpr int NUMBER_OF_FRACTION_BITS = 0;

/* SPECIAL VALUES */

[[maybe_unused]] constexpr uint32_t NAN      = 0x0000'0000;
[[maybe_unused]] constexpr uint32_t INFINITY = 0x0000'0000;

#endif //CONSTANTS_H
