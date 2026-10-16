/**************************************************************************//**
 *
 * @file checkpoints.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Function for the stages' checkpoints.
 *
 * There are three `static inline` checkpoint functions that serve as templates
 *      for the stage-specific functions whose names are parameterized by the
 *      scenario.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "exit-codes.h"
#include "global-data.h"
#include "../customization/randomization.h"
#include "stack.h"
#include "stages.h"
#include "student.h"
#include "validation.h"
#include "checkpoints.h"

[[gnu::always_inline]]
/**
 * The template function for the stages that do not require an argument to be passed to the checkpoint function.
 *
 * @note This template is suitable for `STACK_NO_CODE_CHECKPOINT` used in stage 0, and for `HEAP_NO_CODE_CHECKPOINT`
 *      used in stage 5.
 */
static inline void checkpoint_void(void) {
    anticipated_exit_code = SUCCESS;
    uintptr_t stack_pointer = stack_pointer_after_checkpoint_prologue = get_stack_pointer();
    if (stack_pointer % stack_pointer_alignment != 0) {
        FORCE_STACK_POINTER_ALIGNMENT;
#if defined (__x86_64__)
        if (stage == STACK_NO_CODE) {
            printf("[INFO] You reached %s!\n"
                   "[WARNING] Your stack pointer is misaligned, but this is okay (even expected) in stage %u.\n",
                   actual_checkpoint_function, stage);
            printf("[WARNING] In later stages, you should think about how to preserve %%rsp's alignment.\n");
        } else {
            printf("[ERROR] You reached %s, but your stack pointer is misaligned.\n", actual_checkpoint_function);
            anticipated_exit_code |= MISALIGNED_STACK_POINTER;
        }
#elif defined (__aarch64__) || defined (__arm__)
        printf("[ERROR] You reached %s, but your stack pointer is misaligned.\n", actual_checkpoint_function);
        anticipated_exit_code |= MISALIGNED_STACK_POINTER;
#endif
    }
    if (stage != STACK_NO_CODE && stage != HEAP_NO_CODE) {
        printf("[ERROR] You reached %s, but your target should have been %s.\n", actual_checkpoint_function, expected_checkpoint_function);
        anticipated_exit_code |= INCORRECT_CHECKPOINT;
    }
    validate_void();
    unreachable();
}

[[gnu::always_inline]]
/**
 * The template function for the stages that require the integer representation of the student ID to be passed to the
 * checkpoint function.
 *
 * @note This template is suitable for `STACK_CODE_INT_CHECKPOINT` used in stage 1, for `ROP_INT_CHECKPOINT` used in
 *      stage 3, and for `HEAP_CODE_INT_CHECKPOINT` used in stage 6.
 *
 * @param student_id The integer representation of the student ID
 */
static inline void checkpoint_int(uint32_t student_id) {
    reported_student_id_int = student_id;
    anticipated_exit_code = SUCCESS;
    uintptr_t stack_pointer = stack_pointer_after_checkpoint_prologue = get_stack_pointer();
    if (stack_pointer % stack_pointer_alignment != 0) {
        FORCE_STACK_POINTER_ALIGNMENT;
        printf("[ERROR] You reached %s, but your stack pointer is misaligned.\n", actual_checkpoint_function);
        anticipated_exit_code |= MISALIGNED_STACK_POINTER;
    }
    if (reported_student_id_int != STUDENT_ID_INT) {
        printf("[ERROR] You reached %s with student id %u, which is not the correct student id.\n", actual_checkpoint_function, reported_student_id_int);
        anticipated_exit_code |= INCORRECT_FUNCTION_ARGUMENT;
    }
    if (stage != STACK_CODE_INT && stage != ROP_INT && stage != HEAP_CODE_INT) {
        printf("[ERROR] You reached %s, but your target should have been %s.\n", actual_checkpoint_function, expected_checkpoint_function);
        anticipated_exit_code |= INCORRECT_CHECKPOINT;
    }
    validate_int();
    unreachable();
}

[[gnu::always_inline]]
/**
 *
 * The template function for the stages that require the string representation of the student ID to be passed to the
 * checkpoint function.
 *
 * @note This template is suitable for `STACK_CODE_STRING_CHECKPOINT` used in stage 2, and for `ROP_STRING_CHECKPOINT`
 *      used in stage 4.
 *
 * @param student_id A pointer to the string representation of the student ID
 */
static inline void checkpoint_string(char const *student_id) {
    reported_student_id_string = student_id;
    anticipated_exit_code = SUCCESS;
    uintptr_t stack_pointer = stack_pointer_after_checkpoint_prologue = get_stack_pointer();
    if (stack_pointer % stack_pointer_alignment != 0) {
        FORCE_STACK_POINTER_ALIGNMENT;
        printf("[ERROR] You reached %s, but your stack pointer is misaligned.\n", actual_checkpoint_function);
        anticipated_exit_code |= MISALIGNED_STACK_POINTER;
    }
    uintptr_t frame_pointer = get_frame_pointer();
    if (((uintptr_t) reported_student_id_string <= frame_pointer)
        && ((uintptr_t) reported_student_id_string >= stack_segment_lower_bound)
        && ((uintptr_t) reported_student_id_string <= stack_segment_upper_bound)) {
        printf("[WARNING] The pointer to your string is a dangling pointer.\n");
    }
    if (strncmp(reported_student_id_string, STUDENT_ID_STRING, STUDENT_ID_SIZE) != 0) {
        printf("[ERROR] You reached %s with student id \"%s\", which is not the correct student id.\n", actual_checkpoint_function, reported_student_id_string);
        if ((uintptr_t) reported_student_id_string <= frame_pointer) {
            printf("[INFO] This error might have been caused by your string getting clobbered.\n");
        }
        anticipated_exit_code |= INCORRECT_FUNCTION_ARGUMENT;
    }
    if (reported_student_id_string == STUDENT_ID_STRING) {
        printf("[ERROR] You reached %s, using a string already present in the code.\n", actual_checkpoint_function);
        printf("[ERROR] You had to take some effort to make that happen.\n"
               "[ERROR] Now try injecting your own string.\n");
        anticipated_exit_code |= INCORRECT_FUNCTION_ARGUMENT;
    }
    validate_string();
    unreachable();
}


[[gnu::used, gnu::noinline, gnu::aligned(16), gnu::section(".checkpoints.text")]]
/**
 * A space-filler to create a student-specific offset in the checkpoint code section.
 */
void padding(void) {
    __asm__ volatile(
            CHECKPOINT_PADDING01
            );
}


/* *** The checkpoint functions with parameterized names *** */


[[gnu::used, gnu::noinline, gnu::aligned(16), gnu::section(".checkpoints.text")]]
void STACK_NO_CODE_CHECKPOINT(void) {
    snapshot_stack_words(stack_snapshots[2], buffer_on_stack, preferred_snapshot_count);
    actual_checkpoint_function = __FUNCTION__;
    checkpoint_void();
    __asm__ volatile(
            CHECKPOINT_PADDING02
            );
}

[[gnu::used, gnu::noinline, gnu::aligned(16), gnu::section(".checkpoints.text")]]
void STACK_CODE_INT_CHECKPOINT(uint32_t student_id) {
    snapshot_stack_words(stack_snapshots[2], buffer_on_stack, preferred_snapshot_count);
    actual_checkpoint_function = __FUNCTION__;
    checkpoint_int(student_id);
    __asm__ volatile(
            CHECKPOINT_PADDING03
            );
}

[[gnu::used, gnu::noinline, gnu::optimize("no-omit-frame-pointer"), gnu::aligned(16), gnu::section(".checkpoints.text")]]
void STACK_CODE_STRING_CHECKPOINT(char const *student_id) {
    snapshot_stack_words(stack_snapshots[2], buffer_on_stack, preferred_snapshot_count);
    actual_checkpoint_function = __FUNCTION__;
    checkpoint_string(student_id);
    __asm__ volatile(
            CHECKPOINT_PADDING04
            );
}

[[gnu::used, gnu::noinline, gnu::aligned(16), gnu::section(".checkpoints.text")]]
void ROP_INT_CHECKPOINT(uint32_t student_id) {
    snapshot_stack_words(stack_snapshots[2], buffer_on_stack, preferred_snapshot_count);
    actual_checkpoint_function = __FUNCTION__;
    checkpoint_int(student_id);
    __asm__ volatile(
            CHECKPOINT_PADDING05
            );
}

[[gnu::used, gnu::noinline, gnu::optimize("no-omit-frame-pointer"), gnu::aligned(16), gnu::section(".checkpoints.text")]]
void ROP_STRING_CHECKPOINT(char const *student_id) {
    snapshot_stack_words(stack_snapshots[2], buffer_on_stack, preferred_snapshot_count);
    actual_checkpoint_function = __FUNCTION__;
    checkpoint_string(student_id);
    __asm__ volatile(
            CHECKPOINT_PADDING06
            );
}