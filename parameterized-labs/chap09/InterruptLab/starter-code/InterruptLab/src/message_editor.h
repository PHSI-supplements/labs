/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file message_editor.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Functions to manage the user's message.
 *
 ******************************************************************************/

/*
 * InterruptLab (c) 2021-24 Christopher A. Bohn
 * Number Pad Texter (c) 2023-24 Christopher A. Bohn
 *
 * Assignment and starter code licensed under the Apache License,
 * Version 2.0 (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef MESSAGE_EDITOR_H
#define MESSAGE_EDITOR_H

#include <CowPi.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__AVR__)
static cowpi_pininterrupt_t *const interrupt_controller = (cowpi_pininterrupt_t *) (0x3B);
static inline void disable_pin_interrupts() { interrupt_controller->pci_control = 0x0; }
static inline void enable_pin_interrupts() { interrupt_controller->pci_control = 0x7; }
#elif defined (__MBED__)
static inline void disable_pin_interrupts() { ; }
static inline void enable_pin_interrupts() { ; }
#else
#error Unrecognized board!
#endif //Board

void initialize_editor(void);
void replace_character(char c);
void delete_character(void);
void advance_cursor(void);
void retreat_cursor(void);
void send_message_to_output();

#ifdef __cplusplus
} // extern "C"
#endif

#endif //MESSAGE_EDITOR_H
