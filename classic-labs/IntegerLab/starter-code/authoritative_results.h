/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file authoritative_results.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Function prototypes to get authoritative results, and definitions to
 *      select the implementation appropriate for the target machine.
 *
 ******************************************************************************/

/*
 * IntegerLab (c) 2018-23 Christopher A. Bohn
 *
 * Assignment and starter code licensed under the Apache License,
 * Version 2.0 (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef AUTHORITATIVE_RESULTS_H
#define AUTHORITATIVE_RESULTS_H

#ifndef __ASSEMBLER__

#include <stdint.h>

struct authoritative_result {
    uint16_t result;
    uint16_t supplemental_result;
    uint8_t z_flag;
    uint8_t s_flag;
    uint8_t o_flag;
    uint8_t c_flag;
};

void evaluate_addition(uint16_t operand1, uint16_t operand2, struct authoritative_result *result) __attribute__ ((no_instrument_function));
void evaluate_subtraction(uint16_t operand1, uint16_t operand2, struct authoritative_result *result) __attribute__ ((no_instrument_function));
void evaluate_unsigned_multiplication(uint16_t operand1, uint16_t operand2, struct authoritative_result *result) __attribute__ ((no_instrument_function));
void evaluate_unsigned_division(uint16_t operand1, uint16_t operand2, struct authoritative_result *result) __attribute__ ((no_instrument_function));
void evaluate_signed_multiplication(uint16_t operand1, uint16_t operand2, struct authoritative_result *result) __attribute__ ((no_instrument_function));
void evaluate_signed_division(uint16_t operand1, uint16_t operand2, struct authoritative_result *result) __attribute__ ((no_instrument_function));

#endif //__ASSEMBLER__

//#if defined _POSIX_VERSION || defined _XOPEN_VERSION  // this didn't work on my Mac

// for now, assume a 64-bit machine;
// see https://github.com/cpredef/predef/blob/master/Architectures.md for IA32 macros if we change that assumption
// (see that link also for ARM macros when we get to that)

#if defined (__linux__) && ((__x86_64__) || defined (_M_X64))
#define X86_64_LINUX
#elif defined (__APPLE__) && ((__x86_64__) || defined (_M_X64))
#define X86_64_MACOS
#else
#warning Some of the code to determine the *expected* supplemental_result and *expected* flags is not yet defined for your system.
#define DEFAULT_IMPLEMENTATION
#endif // target

#endif //AUTHORITATIVE_RESULTS_H
