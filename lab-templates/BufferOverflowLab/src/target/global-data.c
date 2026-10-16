/**************************************************************************//**
 *
 * @file global-data.c
 *
 * @author Christopher A. Bohn
 *
 * @copybrief global-data.h
 *
 * @copydetails global-data.h
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include "exit-codes.h"
#include "global-data.h"

uintptr_t stack_snapshots[3][preferred_snapshot_count];
uintptr_t *buffer_on_stack;
uintptr_t stack_pointer_after_checkpoint_prologue;
bool print_input;
bool print_stack;

[[gnu::section(".validation.data")]]
unsigned int stage;

[[gnu::section(".validation.data")]]
char const *expected_checkpoint_function;

[[gnu::section(".validation.data")]]
char const *actual_checkpoint_function;

[[gnu::section(".validation.data")]]
uint32_t reported_student_id_int;

[[gnu::section(".validation.data")]]
char const *reported_student_id_string;

[[gnu::section(".validation.data")]]
int anticipated_exit_code = UNDEFINED;

[[gnu::section(".validation.data")]]
long canary;
