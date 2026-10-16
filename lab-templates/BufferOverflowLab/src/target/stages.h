/**************************************************************************//**
 *
 * @file stages.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Named constants for the assignment's stage numbers.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef STAGES_H
#define STAGES_H

constexpr int NUMBER_OF_STAGES = 5;

constexpr unsigned int STACK_NO_CODE         = 0;
constexpr unsigned int STACK_CODE_INT        = 1;
constexpr unsigned int STACK_CODE_STRING     = 2;
constexpr unsigned int ROP_INT               = 3;
constexpr unsigned int ROP_STRING            = 4;
constexpr unsigned int HEAP_NO_CODE          = 5;
constexpr unsigned int HEAP_CODE_INT         = 6;

#endif //STAGES_H
