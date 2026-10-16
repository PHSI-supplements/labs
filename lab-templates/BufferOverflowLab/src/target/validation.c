/**************************************************************************//**
 *
 * @file validation.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Function prototypes for the attack validation functions.
 *
 * @copydetails validation.h
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
#include <stdlib.h>
#include <string.h>
#include "code-offsets.h"
#include "exit-codes.h"
#include "global-data.h"
#include "intro-outro.h"
#include "stack.h"
#include "stages.h"
#include "string-io.h"
#include "student.h"
#include "validation.h"

/**
 * Helper function to check whether the actual and expected checkpoint functions
 * are the same, and whether the checkpoint function found a misaligned stack
 * pointer (which would have been corrected before calling the validation
 * function).
 *
 * @return Bits suitable for bitwise-ORing into the program's exit code.
 */
static inline int validate_checkpoint_function(void) {
    int exit_code = 0;
    if (!actual_checkpoint_function) {
        exit_code = BYPASSED_PRIMARY_CHECKS;
    } else if (strcmp(expected_checkpoint_function, actual_checkpoint_function) != 0) {
        exit_code = INCORRECT_CHECKPOINT;
    } else {}
    if (anticipated_exit_code & MISALIGNED_STACK_POINTER) {
        exit_code |= MISALIGNED_STACK_POINTER;
    }
    return exit_code;
}

/**
 * Helper function to detect whether the student had bypassed some or all of the
 * verification code in the checkpoint function.
 *
 * @param exit_code                         The validation function's calculated exit code.
 * @param ignore_misaligned_stack_pointer   Should the "misaligned stack pointer" bit be used when comparing calculated exit codes?
 * @return                                  Bits suitable for bitwise-ORing into the program's exit code.
 */
static inline int validate_primary_checks(int exit_code, bool ignore_misaligned_stack_pointer) {
    if ((exit_code & ~BYPASSED_PRIMARY_CHECKS) != (anticipated_exit_code & ~BYPASSED_PRIMARY_CHECKS & (ignore_misaligned_stack_pointer ? ~MISALIGNED_STACK_POINTER : ~0))) {
        exit_code |= BYPASSED_PRIMARY_CHECKS;
    }
    if ((exit_code & BYPASSED_PRIMARY_CHECKS)) {
        printf("[ERROR] You attempted to bypass the validation checks for stage %u.\n", stage);
        printf("[ERROR] Nice try. Now do it right.\n");
    }
    return exit_code;
}

[[gnu::noinline, gnu::section(".validation.text")]]
void validate_void(void) {
    int actual_exit_code = SUCCESS;
    uintptr_t stack_pointer = get_stack_pointer();
    if (stack_pointer % stack_pointer_alignment != 0) {
        FORCE_STACK_POINTER_ALIGNMENT;
#if defined (__aarch64__) || defined (__arm__)
        actual_exit_code |= BYPASSED_PRIMARY_CHECKS | MISALIGNED_STACK_POINTER;
#endif
    }
    actual_exit_code |= validate_checkpoint_function();
    if (stage != STACK_NO_CODE && stage != HEAP_NO_CODE) {
        actual_exit_code |= INCORRECT_CHECKPOINT;
    }
    actual_exit_code |= validate_primary_checks(actual_exit_code, true);
    if (actual_exit_code == SUCCESS) {
        printf("[SUCCESS] Congratulations! You reached %s, successfully clearing stage %u.\n", actual_checkpoint_function, stage);
    }
    report_outcome(actual_exit_code | VALIDATED_VOID);
    unreachable();
}

[[gnu::noinline, gnu::section(".validation.text")]]
void validate_int(void) {
    int actual_exit_code = SUCCESS;
    uintptr_t stack_pointer = get_stack_pointer();
    if (stack_pointer % stack_pointer_alignment != 0) {
        FORCE_STACK_POINTER_ALIGNMENT;
        actual_exit_code |= BYPASSED_PRIMARY_CHECKS | MISALIGNED_STACK_POINTER;
    }
    actual_exit_code |= validate_checkpoint_function();
    if (reported_student_id_int != STUDENT_ID_INT) {
        actual_exit_code |= INCORRECT_FUNCTION_ARGUMENT;
    }
    if (stage != STACK_CODE_INT && stage != ROP_INT && stage != HEAP_CODE_INT) {
        actual_exit_code |= INCORRECT_CHECKPOINT;
    }
    actual_exit_code |= validate_primary_checks(actual_exit_code, false);
    if (actual_exit_code == SUCCESS) {
        printf("[SUCCESS] Congratulations! You reached %s with student id %d, successfully clearing stage %u.\n",
               actual_checkpoint_function, reported_student_id_int, stage);
    }
    report_outcome(actual_exit_code | VALIDATED_INT);
    unreachable();
}

[[gnu::noinline, gnu::section(".validation.text")]]
void validate_string(void) {
    int actual_exit_code = SUCCESS;
    uintptr_t stack_pointer = get_stack_pointer();
    if (stack_pointer % stack_pointer_alignment != 0) {
        FORCE_STACK_POINTER_ALIGNMENT;
        actual_exit_code |= BYPASSED_PRIMARY_CHECKS | MISALIGNED_STACK_POINTER;
    }
    actual_exit_code |= validate_checkpoint_function();
    if (strncmp(reported_student_id_string, STUDENT_ID_STRING, STUDENT_ID_SIZE) != 0) {
        actual_exit_code |= INCORRECT_FUNCTION_ARGUMENT;
    }
    if (reported_student_id_string == STUDENT_ID_STRING) {
        actual_exit_code |= INCORRECT_FUNCTION_ARGUMENT;
    }
    if (stage != STACK_CODE_STRING && stage != ROP_STRING) {
        actual_exit_code |= INCORRECT_CHECKPOINT;
    }
    actual_exit_code |= validate_primary_checks(actual_exit_code, false);
    if (actual_exit_code == SUCCESS) {
        printf("[SUCCESS] Congratulations! You reached %s with student id \"%s\", successfully clearing stage %u.\n",
               actual_checkpoint_function, reported_student_id_string, stage);
    }
    report_outcome(actual_exit_code | VALIDATED_STRING);
    unreachable();
}


[[gnu::noinline, gnu::section(".validation.text")]]
void report_outcome(int exit_code) {
    if (print_stack) {
        stack_word_string_t initial_stack[preferred_snapshot_count];
        stack_word_string_t resulting_stack[preferred_snapshot_count];
        stack_word_string_t final_stack[preferred_snapshot_count];
        stack_to_strings(initial_stack, stack_snapshots[0], preferred_snapshot_count);
        stack_to_strings(resulting_stack, stack_snapshots[1], preferred_snapshot_count);
        stack_to_strings(final_stack, stack_snapshots[2], preferred_snapshot_count);
#if defined(__x86_64__)
        char const stack_pointer_name[] = "%rsp";
        char const argument_register_name[] = "%rdi";
#elif defined(__aarch64__)
        char const stack_pointer_name[] = "sp";
        char const argument_register_name[] = "x0";
#elif defined(__arm__)
        char const stack_pointer_name[] = "sp";
        char const argument_register_name[] = "r0";
#endif
        printf("\n[INFO]\n  %-*s  %-*s  %s%s%s\n", 3 * (int) sizeof(uintptr_t), "initial stack",
               3 * (int) sizeof(uintptr_t), "resulting stack", "after ", actual_checkpoint_function, "'s prologue");
        for (size_t i = 0; i < preferred_snapshot_count; i++) {
            printf("| %s | %s | %s |\n", initial_stack[i], resulting_stack[i], final_stack[i]);
        }
        char datum_to_display[80];
        sprintf(datum_to_display, "buffer = %p", buffer_on_stack);
        int string_length = (int) strlen(datum_to_display);
        printf("  %s", datum_to_display);
        sprintf(datum_to_display, "%s = %p", stack_pointer_name, (void *) stack_pointer_after_checkpoint_prologue);
        printf("%*s\n", (int) (3 * (3 * sizeof(uintptr_t)) + 3 - string_length), datum_to_display);
        if (stage == STACK_CODE_INT || stage == ROP_INT || stage == HEAP_CODE_INT) {
            sprintf(datum_to_display, "%s = %#x", argument_register_name, reported_student_id_int);
        }
        if (stage == STACK_CODE_STRING || stage == ROP_STRING) {
            sprintf(datum_to_display, "%s = %p", argument_register_name, reported_student_id_string);
        }
        printf("%*s\n", (int) (3 * (3 * sizeof(uintptr_t)) + 5), datum_to_display);
    }

    if (!actual_checkpoint_function
        && (exit_code != NO_EXPLOIT)
        && !(exit_code & BYPASSED_PRIMARY_CHECKS)
        && !(exit_code & CAUGHT_SIGNAL)
        && !(exit_code & UNSUCCESSFUL_INITIALIZATION)) {
        exit_code = BYPASSED_PRIMARY_CHECKS | NO_EXPLOIT;
    }
    printf("\n[SCENARIO]\n%s\n\n", get_outro(exit_code & 0xFF));
    printf("\n[GRADING] ");
    if ((exit_code & 0xFF) == SUCCESS) {
        printf("Stage %u cleared.\n", stage);
    } else if ((exit_code & 0xFF) == MISALIGNED_STACK_POINTER) {
        printf("Stage %u cleared with misaligned stack pointer.\n", stage);
    } else {
        printf("Stage %u not cleared.\n", stage);
//        printf("Stage %u not cleared: diagnostic %x.\n", stage, exit_code);
    }
    fflush(stdout);
    exit(exit_code & 0xFF);
}
