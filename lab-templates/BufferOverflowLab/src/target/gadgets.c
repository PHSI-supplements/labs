/**************************************************************************//**
 *
 * @file gadgets.c
 *
 * @author Christopher A. Bohn
 *
 * @brief functions to hold assembly language snippets that serve as ROP
 *      gadgets.
 *
 * The gadgets' instructions are defined in gadgets.h; however, their order is
 *      specified in target/student.h.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include "../customization/randomization.h"
#include "gadgets.h"

// TODO: have T32 gadgets get the return address from the stack (`pop {r4, pc}`, omit subsequent `bx lr`)

[[gnu::used, gnu::noinline, gnu::section(".gadgets.text")]]
void gadget01(void) {
    __asm__ volatile (GADGET_PADDING01);
    __asm__ volatile ("ret\n");
    __asm__ volatile (GADGET_NOP01_1);
    __asm__ volatile (GADGET01);
    __asm__ volatile (GADGET_NOP01_2);
#if defined (__aarch64__)
    __asm__ volatile ("ldp x29, x30, [sp], #16");
#endif
}

[[gnu::used, gnu::noinline, gnu::section(".gadgets.text")]]
void gadget02(void) {
    __asm__ volatile (GADGET_PADDING02);
    __asm__ volatile ("ret\n");
    __asm__ volatile (GADGET_NOP02_1);
    __asm__ volatile (GADGET02);
    __asm__ volatile (GADGET_NOP02_2);
#if defined (__aarch64__)
    __asm__ volatile ("ldp x29, x30, [sp], #16");
#endif
}

[[gnu::used, gnu::noinline, gnu::section(".gadgets.text")]]
void gadget03(void) {
    __asm__ volatile (GADGET_PADDING03);
    __asm__ volatile ("ret\n");
    __asm__ volatile (GADGET_NOP03_1);
    __asm__ volatile (GADGET03);
    __asm__ volatile (GADGET_NOP03_2);
#if defined (__aarch64__)
    __asm__ volatile ("ldp x29, x30, [sp], #16");
#endif
}

[[gnu::used, gnu::noinline, gnu::section(".gadgets.text")]]
void gadget04(void) {
    __asm__ volatile (GADGET_PADDING04);
    __asm__ volatile ("ret\n");
    __asm__ volatile (GADGET_NOP04_1);
    __asm__ volatile (GADGET04);
    __asm__ volatile (GADGET_NOP04_2);
#if defined (__aarch64__)
    __asm__ volatile ("ldp x29, x30, [sp], #16");
#endif
}

[[gnu::used, gnu::noinline, gnu::section(".gadgets.text")]]
void gadget05(void) {
    __asm__ volatile (GADGET_PADDING05);
    __asm__ volatile ("ret\n");
    __asm__ volatile (GADGET_NOP05_1);
    __asm__ volatile (GADGET05);
    __asm__ volatile (GADGET_NOP05_2);
#if defined (__aarch64__)
    __asm__ volatile ("ldp x29, x30, [sp], #16");
#endif
}

[[gnu::used, gnu::noinline, gnu::section(".gadgets.text")]]
void gadget06(void) {
    __asm__ volatile (GADGET_PADDING06);
    __asm__ volatile ("ret\n");
    __asm__ volatile (GADGET_NOP06_1);
    __asm__ volatile (GADGET06);
    __asm__ volatile (GADGET_NOP06_2);
#if defined (__aarch64__)
    __asm__ volatile ("ldp x29, x30, [sp], #16");
#endif
}
