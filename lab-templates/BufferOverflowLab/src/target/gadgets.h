/**************************************************************************//**
 *
 * @file gadgets.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Named constants for useful assembly language instructions.
 *
 * These instructions include NOPs, instructions that will be useful in ROP
 *      gadgets, and (eventually) red herring/chaff gadgets. By using named
 *      constants, the actual assembly code can vary by processor architecture,
 *      and it is easier to vary the gadget order by student.
 *
 ******************************************************************************/

// TODO: introduce red herring/chaff gadgets
// TODO: "add 16 to sp" in addition to "add 8 to sp"

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef GADGETS_H
#define GADGETS_H

#define EMPTY ""
#define NOP "nop"

// ALT_NOP
#if defined (__x86_64__)
//#define NOP_ALT "nopl 0x0(%rax,%rax,1)"
#define NOP_ALT ".nops 4"
#elif defined (__aarch64__)
#define NOP_ALT "add x0, x0, xzr"
#elif defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_8M_MAIN__)
#define NOP_ALT "nop.w"
#elif defined(__ARM_ARCH_6M__) || defined(__ARM_ARCH_8M_BASE__)
#define NOP_ALT ".syntax unified\n\tmov r0, r0"
#endif

// GENERATE_POINTER
#if defined (__x86_64__)
#define GENERATE_POINTER "leaq (%rsp, %rdi), %rsi"
#elif defined (__aarch64__)
#define GENERATE_POINTER "add x1, sp, x0"
#elif defined(__arm__)
#define GENERATE_POINTER "add r1, sp"
#endif

// POP_ONE
#if defined (__x86_64__)
//#define POP_ONE "pop %rsi"
#define POP_ONE EMPTY           // reuse the `pop %rdx`from POP_TWO until `pop2` is readily available
#elif defined (__aarch64__)
#define POP_ONE "ldr x1, [sp]"          // technically, not a pop
#elif defined(__arm__)
#define POP_ONE "pop {r1}"
#endif

// POP_TWO
//#if defined (__APX__)           // hypothetical macro
//#define POP_TWO "pop2 %rsi, %rdx"
//#elif defined (__x86_64__)      // going to have to rely on this one for a while
#if defined (__x86_64__)
#define POP_TWO "pop %rsi\n pop %rdx"
#elif defined (__aarch64__)
#define POP_TWO "ldp x1, x2, [sp], #16"
#elif defined(__arm__)
#define POP_TWO "pop {r1, r2}"
#endif

// ADD_TO_SP
#if defined (__x86_64__)
#define ADD_TO_SP "add $8, %rsp"                                    // add 8, later we'll have distinct add 8, add 16
#elif defined (__aarch64__)
#define ADD_TO_SP "add sp, sp, #16"    // add 16, later we'll have distinct add 8, add 16
#elif defined(__arm__)
#define ADD_TO_SP "add sp, #8"                                      // add 8, later we'll have add 4, add 8
#endif

// MOV1
#if defined (__x86_64__)
#define MOV1 "mov %rsi, %rdi"
#elif defined (__aarch64__)
#define MOV1 "mov x0, x1"
#elif defined(__arm__)
#define MOV1 "mov r0, r1"
#endif

// MOV2
#if defined (__x86_64__)
#define MOV2 "mov %rdx, %rdi"
#elif defined (__aarch64__)
#define MOV2 "mov x0, x2"
#elif defined(__arm__)
#define MOV2 "mov r0, r2"
#endif

#define RED_HERRING_1 "nop"
#define RED_HERRING_2 "nop"
#define RED_HERRING_3 "nop"
#define RED_HERRING_4 "nop"
#define RED_HERRING_5 "nop"
#define RED_HERRING_6 "nop"

#endif //GADGETS_H
