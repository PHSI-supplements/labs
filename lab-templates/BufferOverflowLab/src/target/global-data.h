/**************************************************************************//**
 *
 * @file global-data.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Data exposed to several files.
 *
 * Functions accessing these variables need to do so without affecting the
 *      stack, and so we expose them publicly without hiding them behind
 *      accessor/mutator functions. Some of the variables are placed in the
 *      `.validation.data` section so an attacker cannot address the variables'
 *      memory.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stddef.h>
#include <stdint.h>

constexpr size_t preferred_snapshot_count = 20;                 //!< how many stack words will be recorded in a snapshot

extern unsigned int stage;                                      //!< the lab stage specifies the students' challenge
extern char const *expected_checkpoint_function;                //!< which checkpoint function should the attack reach
extern char const *actual_checkpoint_function;                  //!< which checkpoint function *did* the attack reach
extern uint32_t reported_student_id_int;                        //!< the student ID passed to `checkpoint_int`
extern char const *reported_student_id_string;                  //!< the student ID passed to `checkpoint_string`
extern int anticipated_exit_code;                               //!< the exit code computed by the checkpoint function, used by the validation function to detect an attempt to bypass the checkpoint's verification steps
extern long canary;                                             //!< the stack canary used in the heap overflow stages

extern uintptr_t stack_snapshots[3][preferred_snapshot_count];  //!< buffers for stack snapshots before reading input, after reading input, and after reaching a checkpoint function
extern uintptr_t *buffer_on_stack;                              //!< a pointer to the buffer used in the stack-based attacks
extern uintptr_t stack_pointer_after_checkpoint_prologue;       //!< a copy of the stack pointer when the checkpoint function is ready to execute
extern bool print_input;                                        //!< a flag indicating that the student wants their input printed back to them
extern bool print_stack;                                        //!< a flag indicating that the student wants stack snapshots printed

#endif //GLOBAL_DATA_H
