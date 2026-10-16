/**************************************************************************//**
 *
 * @file checkpoints.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Function prototypes for the stages' checkpoints, with parameterized
 *      names.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef CHECKPOINTS_H
#define CHECKPOINTS_H

#include <stdint.h>
#include "scenario.h"

void STACK_NO_CODE_CHECKPOINT(void);
void STACK_CODE_INT_CHECKPOINT(uint32_t student_id);
void STACK_CODE_STRING_CHECKPOINT(char const *student_id);
void ROP_INT_CHECKPOINT(uint32_t student_id);
void ROP_STRING_CHECKPOINT(char const *student_id);

#endif //CHECKPOINTS_H
