/**************************************************************************//**
 *
 * @file scenario.h
 *
 * @author Christopher A. Bohn
 *
 * @sa ../customization/scenario.h
 *
 * @brief Extern variable declarations and macros to access scenario data.
 *
 * The scenario may change from one semester to the next; however, the variable
 *      names and helper macros are fixed and do not need to be customized.
 *      The contents of this file do are the aspects of the scenario that do not
 *      change.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef TARGET_SCENARIO_H
#define TARGET_SCENARIO_H

#if __has_include(<stdbit.h>)
#include <stdbit.h>
#endif
#include <limits.h>
#include "exit-codes.h"
#include "stages.h"
#include "../customization/scenario.h"

#define STRINGIFY_HELPER(macro) #macro
#define STRINGIFY(macro)        STRINGIFY_HELPER(macro)

extern char const *intros[NUMBER_OF_STAGES];                            //!< Messages to be printed at the start of a stage
extern char const *outros[NUMBER_OF_STAGES][NUMBER_OF_CORE_EXIT_CODES]; //!< Messages to be printed at the end of a stage, with a different message for each possible outcome

// TODO: eventually, stdbit.h will be more reliably be available
#if __has_include(<stdbit.h>)
#define SCENARIO_INDEX(exit_code)   (                                       \
    ((exit_code) <= 0 )                                                     \
        ? (exit_code)                                                       \
        : (int) stdc_bit_width((unsigned int) exit_code)                    \
)
#else
// TODO: until then, use the more complex expression
#define SCENARIO_INDEX(exit_code)   (                                       \
    ((exit_code) <= 0 )                                                     \
        ? (exit_code)                                                       \
        : (int) ((sizeof(exit_code) * CHAR_BIT) - __builtin_clz(exit_code)) \
)
#endif

#endif //TARGET_SCENARIO_H
