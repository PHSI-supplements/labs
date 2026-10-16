/**************************************************************************//**
 *
 * @file exit-codes.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Named constants for exit codes.
 *
 * Except for the signal-based exit codes and the UNDEFINED exit code, the
 *      program's exit code is a bitwise disjunction of these constants.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef EXIT_CODES_H
#define EXIT_CODES_H

#include <signal.h>

constexpr int NUMBER_OF_CORE_EXIT_CODES = 9;

constexpr int UNDEFINED                      =    -1;

// core exit codes
constexpr int SUCCESS                        =     0;
constexpr int UNUSED_EXIT_CODE               =   0x1;
constexpr int NO_EXPLOIT                     =   0x2;
constexpr int MISALIGNED_STACK_POINTER       =   0x4;
constexpr int INCORRECT_FUNCTION_ARGUMENT    =   0x8;
constexpr int INCORRECT_CHECKPOINT           =  0x10;
constexpr int BYPASSED_PRIMARY_CHECKS        =  0x20;
constexpr int UNSUCCESSFUL_INITIALIZATION    =  0x40;
constexpr int CAUGHT_SIGNAL                  =  0x80;

// supplemental exit codes, indicating the validation function used (if any)
// these are truncated from the exit code returned to the shell (`echo $?`) but will be included in diagnostics
constexpr int VALIDATED_VOID                 = 0x100;
constexpr int VALIDATED_INT                  = 0x200;
constexpr int VALIDATED_STRING               = 0x400;

// spelling-out these signal-based exit codes is a bit redundant, but these are the ones we'll look for.
// C-standard signals
constexpr int CONTROL_C                      = CAUGHT_SIGNAL + SIGINT;
constexpr int SEGMENTATION_FAULT             = CAUGHT_SIGNAL + SIGSEGV;
constexpr int ILLEGAL_INSTRUCTION            = CAUGHT_SIGNAL + SIGILL;
constexpr int ABORT                          = CAUGHT_SIGNAL + SIGABRT;
constexpr int BAD_MATH                       = CAUGHT_SIGNAL + SIGFPE;
constexpr int TERMINATED_EXTERNALLY          = CAUGHT_SIGNAL + SIGTERM;
// POSIX-standard signals
constexpr int BUS_ERROR                      = CAUGHT_SIGNAL + SIGBUS;
constexpr int QUITTED                        = CAUGHT_SIGNAL + SIGQUIT;
constexpr int KILLED                         = CAUGHT_SIGNAL + SIGKILL;

#endif //EXIT_CODES_H
