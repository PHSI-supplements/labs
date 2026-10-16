/**************************************************************************//**
 *
 * @file buffer-overflow-lab.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Code to initiate BufferOverflowLab.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include <ctype.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include "exit-codes.h"
#include "global-data.h"
#include "intro-outro.h"
#include "../customization/randomization.h"
#include "scenario.h"
#include "stack.h"
#include "stages.h"
#include "student.h"
#include "validation.h"
#include "vulnerability.h"


/**
 * Prints the expected command line arguments.
 */
static void print_usage(void) {
    printf("\n"
            "[INFO] Usage:\n"
            "[INFO]   target <stage-number> [print (input|stack)+]\n"
            "[INFO]\n"
            "[INFO] Arguments:\n"
            "[INFO]   <stage-number>  Required integer in the range [0, %u]\n"
            "[INFO]   print           Enable printing of diagnostic data\n"
            "[INFO]     input         Print your input\n"
            "[INFO]     stack         Print stack snapshots\n"
            "\n", NUMBER_OF_STAGES - 1
          );
    printf("[INFO] Student ID (integer): %8u (%#010x)\n", STUDENT_ID_INT, STUDENT_ID_INT);
    printf("[INFO] Student ID (string): \"%s\"\n\n", STUDENT_ID_STRING);
}


/**
 * Catches raised signals and redirects execution to the stage's end.
 *
 * @param signal The signal that was raised
 */
static void signal_handler(int signal) {
    report_outcome(128 + signal);
}


/**
 * Initiates the call chain that eventually reaches the vulnerable code.
 *
 * @param include_stack_canary Indicates whether the vulnerable function should place a stack canary on the stack
 */
void launch(bool include_stack_canary) {
    uintptr_t stack_pointer = get_stack_pointer();
    if (stack_pointer % stack_pointer_alignment != 0) {
        FORCE_STACK_POINTER_ALIGNMENT;
        fprintf(stderr, "[INITIALIZATION FAILURE] The stack pointer (%#zx) was not properly aligned before launch.\n", stack_pointer);
        report_outcome(UNSUCCESSFUL_INITIALIZATION);
        unreachable();
    }
    printf("[SCENARIO]\n%s\n\n", get_intro());
    fill_stack(STUDENT_STACK_OFFSET, include_stack_canary);
}

/**
 * Configures the attack surface.
 *
 * @param argc The number of tokens on the command line
 * @param argv The tokens found on the command line
 * @return Normally, `main` returns the exit code; in this case, `main` passes control to another function that will terminate the program with an exit code.
 */
int main(int argc, char const *argv[]) {
    // TODO: run the attack in a child process with `ADDR_NO_RANDOMIZE` personality, reporting token back to parent to prevent syscall-based attack
    actual_checkpoint_function = nullptr;   // if it's still nullptr in `report_outcome` then no checkpoint was reached
    print_input = false;
    print_stack = false;
    srand(time(nullptr));
    canary = rand();
    if ((argc == 1) || (argc == 3) || (argc > 5)) {
        print_usage();
        report_outcome(UNSUCCESSFUL_INITIALIZATION);
        unreachable();
    }
    stage = (unsigned int) strtol(argv[1], nullptr, 10);
    if ((errno == EINVAL) || !isdigit(argv[1][0])) {
        print_usage();
        report_outcome(UNSUCCESSFUL_INITIALIZATION);
        unreachable();
    }
    if (argc > 3) {
        if (strncmp(argv[2], "print", 5) != 0) {    // compare only the first 5, to allow arguments such as "printing"
            print_usage();
            report_outcome(UNSUCCESSFUL_INITIALIZATION);
            unreachable();
        }
        if (!strncmp(argv[3], "input", 5)) {        // compare only the first 5, to allow arguments such as "inputs"
            print_input = true;
        } else if (!strncmp(argv[3], "stack", 5)) { // compare only the first 5, to allow arguments such as "stacks"
            print_stack = true;
        } else {
            print_usage();
            report_outcome(UNSUCCESSFUL_INITIALIZATION);
            unreachable();
        }
    }
    if (argc == 5) {
        if (!strncmp(argv[4], "input", 5)) {
            print_input = true;
        } else if (!strncmp(argv[4], "stack", 5)) {
            print_stack = true;
        } else {
            print_usage();
            report_outcome(UNSUCCESSFUL_INITIALIZATION);
            unreachable();
        }
    }

    expected_checkpoint_function =
            ((char const *[]) {
                    [STACK_NO_CODE]     = STRINGIFY(STACK_NO_CODE_CHECKPOINT),
                    [STACK_CODE_INT]    = STRINGIFY(STACK_CODE_INT_CHECKPOINT),
                    [STACK_CODE_STRING] = STRINGIFY(STACK_CODE_STRING_CHECKPOINT),
                    [ROP_INT]           = STRINGIFY(ROP_INT_CHECKPOINT),
                    [ROP_STRING]        = STRINGIFY(ROP_STRING_CHECKPOINT),
                    [HEAP_NO_CODE]      = STRINGIFY(HEAP_NO_CODE_CHECKPOINT),
                    [HEAP_CODE_INT]     = STRINGIFY(HEAP_CODE_INT_CHECKPOINT),
            })[stage];

    // C-standard signals
    signal(SIGINT, signal_handler);
    signal(SIGSEGV, signal_handler);
    signal(SIGILL, signal_handler);
    signal(SIGABRT, signal_handler);
    signal(SIGFPE, signal_handler);
    signal(SIGTERM, signal_handler);
    // POSIX-standard signals that we might see
    signal(SIGBUS, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGKILL, signal_handler);

    // TODO: troubleshoot this -- why didn't __gadgets_start link to the symbol defined in the linker directive?
    extern void *__gadgets_start;
    extern void *gadget01(void);
    // the gadget section is set up to start on a 4KB boundary with 4KB between its start and the start of the previous & next sections
    // if the page size is not 4KB, then we don't want to disable access to those other sections
    bool safe_to_disable_access = (GADGETS_SIZE >= (size_t) sysconf(_SC_PAGE_SIZE));
    if (safe_to_disable_access && !(stage == ROP_INT || stage == ROP_STRING )) {
        int mprotect_result = mprotect(gadget01, GADGETS_SIZE, PROT_NONE);   // disallow ROP during the non-ROP stages
//        int mprotect_result = mprotect(__gadgets_start, GADGETS_SIZE, PROT_NONE);   // disallow ROP during the non-ROP stages
        if (mprotect_result) {
            printf("[INITIALIZATION] Failed to deny access to gadgets (starting at %p) in stage %u; setting read-only permission.\n",
                   __gadgets_start, stage);
//            mprotect_result = mprotect(__gadgets_start, GADGETS_SIZE, PROT_READ);
            mprotect_result = mprotect(gadget01, GADGETS_SIZE, PROT_READ);
        }
        if (mprotect_result) {
            printf("[INITIALIZATION] Could not set read-only permission: ");
            switch(errno) {
                case EACCES:
                    printf("EACCES\n");
                    break;
                case EINVAL:
                    printf("EINVAL\n");
                    break;
                case ENOMEM:
                    printf("ENOMEM\n");
                    break;
                default:
                    perror(nullptr);
            }
            printf("\n");
        }
    }

    create_predictable_stack_and_launch(
            // executable code on the stack?
            stage == STACK_NO_CODE || stage == STACK_CODE_INT || stage == STACK_CODE_STRING,
            // randomized stack offset?
            stage == ROP_INT || stage == ROP_STRING || stage == HEAP_NO_CODE || stage == HEAP_CODE_INT,
            // include stack canary?
            stage == HEAP_NO_CODE || stage == HEAP_CODE_INT,
            // initiation function
            launch);
    report_outcome(NO_EXPLOIT);
    unreachable();
}