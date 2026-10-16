/**************************************************************************//**
 *
 * @file stack.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Function for working with the assignment's custom stack.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "exit-codes.h"
#include "global-data.h"
#include "student.h"
#include "validation.h"
#include "stack.h"

constexpr char hexdigits[] = "0123456789ABCDEF";

/**
 * Inline helper function that moves the stack pointer from the old stack to the
 * new stack (and back again if there was no exploit), and launches the call chain
 * that has the attack surface.
 *
 * @param new_stack_pointer     The address that the stack pointer should point to.
 * @param include_stack_canary  Should the vulnerable function defend against stack buffer overflows with a canary?
 * @param launch_function       A function pointer to the start of the call chain.
 */
static inline void exchange_stack_and_launch(void *new_stack_pointer,
                                             bool include_stack_canary,
                                             void (*launch_function)(bool));

void create_predictable_stack_and_launch(bool allow_executable_code_on_stack,
                                         bool create_randomized_offset,
                                         bool include_stack_canary,
                                         void (*launch_function)(bool)) {
#if defined (ARDUINO_RASPBERRY_PI_PICO) || defined (PICO_RP2040)
    // use the RP2040's existing stack
    launch_function(include_stack_canary);
#else
    void *stack = mmap(stack_base_address, stack_segment_size,
                       PROT_READ | PROT_WRITE | (allow_executable_code_on_stack ? PROT_EXEC : 0),
                       MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
                       -1, 0);
    if (stack == MAP_FAILED) {
        perror("[INITIALIZATION FAILURE] Failed to allocate predictable stack.");
        report_outcome(UNSUCCESSFUL_INITIALIZATION);
        unreachable();
    }
    uintptr_t new_stack_pointer = (uintptr_t)stack + stack_segment_size - minimum_stack_offset;
    if (create_randomized_offset) {
        // 0-31 multiples of 16 bytes, or 0-7 multiples of 8 bytes
        size_t size_of_stack_word = sizeof(uintptr_t);
        unsigned int offset_range = size_of_stack_word * size_of_stack_word / 2;
        uintptr_t random_offset = (rand() / (RAND_MAX / offset_range)) * (2 * size_of_stack_word);
        new_stack_pointer -= random_offset;
    }
    FORCE_STACK_POINTER_ALIGNMENT;
    exchange_stack_and_launch((void *) new_stack_pointer, include_stack_canary, launch_function);
    munmap(stack_base_address, stack_segment_size);
#endif
}

static inline void exchange_stack_and_launch(void *new_stack_pointer,
                                             bool include_stack_canary,
                                             void (*launch_function)(bool)) {
    void *old_stack_pointer;
#if defined (__x86_64__)
    __asm__ volatile(
                "movq %%rsp, %0\n"
                "movq %1, %%rsp\n"
                : "=&r"(old_stack_pointer)
                : "r"(new_stack_pointer)
                : "memory"
                );
        launch_function(include_stack_canary);
        __asm__ volatile (
                "mov %0, %%rsp\n"
                :
                : "r"(old_stack_pointer)
                : "memory"
                );
#elif defined (__aarch64__) || defined(__arm__)
    __asm__ volatile(
            "mov %0, sp\n"
            "mov sp, %1\n"
            : "=&r"(old_stack_pointer)
            : "r"(new_stack_pointer)
            : "memory"
            );
    launch_function(include_stack_canary);
    __asm__ volatile(
            "mov sp, %0\n"
            :
            : "r"(old_stack_pointer)
            : "memory"
            );
#endif
}

stack_word_string_t *stack_to_strings(stack_word_string_t *destination,
                                      void const *source,
                                      size_t count) {
    if (!destination) {
        return nullptr;
    }
    size_t word_size = sizeof(uintptr_t);
    size_t i = 0, j = 0;
    uint8_t const *byte = (uint8_t *) source + count * sizeof(uintptr_t);
    bool adding_padding = false;
    while ((byte > (uint8_t *) source) || adding_padding) {
        byte--;
        if (adding_padding) {
            destination[i][j + 0] = ' ';
            destination[i][j + 1] = ' ';
        } else {
            destination[i][j + 0] = hexdigits[*byte >> 4];
            destination[i][j + 1] = hexdigits[*byte & 0xF];
        }
        if (((uintptr_t) byte % word_size != 0)) {
            destination[i][j + 2] = ' ';
            j += 3;
            if (byte <= (uint8_t *) source) {
                adding_padding = true;
            }
        } else {
            destination[i][j + 2] = '\0';
            j = 0;
            i++;
            adding_padding = false;
        }
    }
    return destination;
}
