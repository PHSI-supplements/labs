/**************************************************************************//**
 *
 * @file validation.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Function prototypes for the attack validation functions.
 *
 * These functions substantially run the same checks that the checkpoint
 *      functions run, plus two other checks:
 *      - They check whether the actual checkpoint function was the expected
 *          checkpoint function, and
 *      - The check whether the checkpoint function's computed exit code is the
 *          same as the validation function's computed exit code.
 *
 * The validation functions reside in the `.validation.text` section so that
 *      students cannot direct their attack to jump into the validation
 *      functions, nor to the `report_outcome()` function.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdint.h>

/**
 * Validation function that validates `checkpoint_void()`'s results.
 */
void validate_void(void);

/**
 * Validation function that validates `checkpoint_int()`'s results.
 */
void validate_int(void);

/**
 * Validation function that validates `checkpoint_string()`'s results.
 */
void validate_string(void);

/**
 * Function to wrap up the stage, reporting the results before terminating the program.
 *
 * @param exit_code The exit code that encodes the results.
 */
void report_outcome(int exit_code);

#endif //VALIDATION_H
