/**************************************************************************//**
 *
 * @file stack.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Named constants, function prototypes, and inlined functions for
 *      working with the assignment's custom stack.
 *
 * This file is organized into four parts:
 *      - *SETUP* elements needed to create the custom stack
 *      - *ACCESSORS* elements used to non-destructively gather information
 *              about the stack
 *      - *MUTATORS* elements used to modify the stack (currently, only a macro
 *              to realign the stack pointer to the ABI's or ISA's requirement)
 *      - *RAW2HEX* elements to create human-readable (more or less) strings
 *              representing the bytes within a memory range
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef STACK_H
#define STACK_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>


/* *** SETUP *** */

#if __SIZEOF_POINTER__ >= 8
constexpr uintptr_t stack_segment_lower_bound = 0x7'FFEF'0000;      //!< the low-address end of the custom stack
constexpr uintptr_t stack_segment_upper_bound = 0x7'FFEF'4000;      //!< the high-address end of the custom stack
constexpr size_t minimum_stack_offset = 1024;                       //!< a gap between the nominal bottom of the stack and the high-address end
#elif __SIZEOF_POINTER__ == 4
// RP2040 core 0 stack
constexpr uintptr_t stack_segment_lower_bound = 0x2004'1000;
constexpr uintptr_t stack_segment_upper_bound = 0x2004'2000;
// RP2040 core 1 stack
//constexpr uintptr_t stack_segment_lower_bound = 0x2004'0000;
//constexpr uintptr_t stack_segment_upper_bound = 0x2004'1000;
// RP2350 core 0 stack
//constexpr uintptr_t stack_segment_lower_bound = 0x2008'1000;
//constexpr uintptr_t stack_segment_upper_bound = 0x2008'2000;
// RP350 core 1 stack
//constexpr uintptr_t stack_segment_lower_bound = 0x2008'0000;
//constexpr uintptr_t stack_segment_upper_bound = 0x2008'1000;
// either core 0 stack
//constexpr uintptr_t stack_segment_lower_bound = SRAM_STRIPED_END + 0x1000;
//constexpr uintptr_t stack_segment_upper_bound = SRAM_STRIPED_END + 0x2000;
// either core 1 stack
//constexpr uintptr_t stack_segment_lower_bound = SRAM_STRIPED_END;
//constexpr uintptr_t stack_segment_upper_bound = SRAM_STRIPED_END + 0x1000;

constexpr size_t minimum_stack_offset = 128;
#else
#error This lab is not designed to work with less than a 32-bit address space
#endif

static_assert(stack_segment_upper_bound > stack_segment_lower_bound);
constexpr size_t stack_segment_size = stack_segment_upper_bound - stack_segment_lower_bound;
static void *const stack_base_address = (void *) stack_segment_lower_bound;

/**
 * Creates the custom stack, points the stack pointer to it, and launches the call chain that has the attack surface.
 *
 * @param allow_executable_code_on_stack    Should the stack have execute permissions? Needs to be `true` for code injection attacks.
 * @param create_randomized_offset          Should there be a runtime randomized stack offset in addition to the student-specific offset?
 * @param include_stack_canary              Should the vulnerable function defend against stack buffer overflows with a canary?
 * @param launch_function                   A function pointer to the start of the call chain.
 */
void create_predictable_stack_and_launch(bool allow_executable_code_on_stack,
                                         bool create_randomized_offset,
                                         bool include_stack_canary,
                                         void (*launch_function)(bool));


/* *** STACK ACCESSORS *** */

/**
 * Places a copy of the stack pointer into a general-purpose register.
 *
 * @return A copy of the stack pointer.
 */
static inline uintptr_t get_stack_pointer(void) {
    uintptr_t stack_pointer;
#if defined(__x86_64__)
    __asm__ volatile ("mov %%rsp, %0" : "=r"(stack_pointer));
#elif defined(__aarch64__) || defined(__arm__)
    __asm__ volatile ("mov %0, sp" : "=r"(stack_pointer));
#else
# error "Unsupported architecture"
#endif
    return stack_pointer;
}

/**
 * Places a copy of the frame pointer into a general-purpose register.
 *
 * @return A copy of the frame pointer.
 */
static inline uintptr_t get_frame_pointer(void) {
    return (uintptr_t) __builtin_frame_address(0);
}

/**
 * Copy the specified number of stack words to another part of memory.
 * This inlined function is appropriate when `memcpy` would modify memory that is being copied (such as memory in the stack's red zone).
 *
 * @param destination   The base address of where the snapshot will be stored.
 * @param source        The base address of the memory being copied.
 * @param count         The number of stack words being copied.
 */
static inline void snapshot_stack_words(uintptr_t *restrict destination, uintptr_t const *restrict source, size_t count) {
    count &= ~((size_t)1);  // if `count` isn't a multiple of 2, we'll make it a multiple of 2 that won't overflow `destination`
#if defined(__x86_64__)
    __asm__ volatile (
            "rep movsq"
            : "+D"(destination), "+S"(source), "+c"(count)
            :
            : "memory"
            );
#elif defined(__aarch64__)
    uintptr_t scratch1, scratch2;
    __asm__ volatile (
            "1:\n"
            "ldp %[scratch1], %[scratch2], [%[source]], #16\n"
            "stp %[scratch1], %[scratch2], [%[destination]], #16\n"
            "subs %[count], %[count], #2\n"
            "bne 1b\n"
            : [destination]"+r"(destination), [source]"+r"(source), [count]"+r"(count), [scratch1]"=&r"(scratch1), [scratch2]"=&r"(scratch2)
            :
            : "memory", "cc"
            );
#elif defined(__arm__)
    uintptr_t scratch1, scratch2;
    __asm__ volatile (
            ".syntax unified\n"
            "1:\n"
            "ldmia %[source]!, {%[scratch1], %[scratch2]}\n"
            "stmia %[destination]!, {%[scratch1], %[scratch2]}\n"
            "subs %[count], #2\n"
            "bne 1b\n"
            : [destination]"+l"(destination), [source]"+l"(source), [count]"+r"(count), [scratch1]"=&l"(scratch1), [scratch2]"=&l"(scratch2)
    :
    : "memory", "cc"
    );
#endif
}


/* *** STACK MUTATOR *** */

constexpr size_t stack_pointer_alignment = 2 * sizeof(uintptr_t);

#if defined(__x86_64__)
#define FORCE_STACK_POINTER_ALIGNMENT do { __asm__ volatile( "andq $-16, %%rsp \n" : : : "memory" ); } while(0)
#elif defined(__aarch64__)
#define FORCE_STACK_POINTER_ALIGNMENT do { uintptr_t scratch; __asm__ volatile( "mov %0, sp \n and %0, %0, #-16 \n mov sp, %0\n" : "=r" (scratch) : : "memory" ); } while(0)
#elif defined(__arm__)
#define FORCE_STACK_POINTER_ALIGNMENT do { uintptr_t scratch; __asm__ volatile( ".syntax unified \n mov %0, sp \n lsrs %0, %0, #3 \n lsls %0, %0, #3 \n mov sp, %0\n" : "=l" (scratch) : : "memory" ); } while(0)
#endif


/* *** RAW2HEX *** */

typedef char stack_word_string_t[3 * sizeof(uintptr_t)];    //<! Enough space to hold a human-readable string representation of one stack word

/**
 * Produce a human-readable string representation of a range of memory, such as a stack snapshot.
 *
 * @param destination   The array of `stack_word_string_t`s to hold the strings; there should be at least `count` rows.
 * @param source        The block of memory to be stringified.
 * @param count         The number of stack words to be stringified.
 * @return              A pointer to `destination`.
 */
stack_word_string_t *stack_to_strings(stack_word_string_t destination[], void const *source, size_t count);

#endif //STACK_H
