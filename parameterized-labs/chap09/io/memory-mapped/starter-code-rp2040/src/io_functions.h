/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file io_functions.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Functions that students must re-implement using memory-mapped I/O.
 *
 ******************************************************************************/

/*
 * PollingLab (c) 2021-24 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef IO_FUNCTIONS_H
#define IO_FUNCTIONS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void initialize_io(bool key_mode);
uint32_t get_microseconds(void);
bool left_button_is_pressed(void);
bool right_button_is_pressed(void);
bool left_switch_is_in_left_position(void);
bool left_switch_is_in_right_position(void);
bool right_switch_is_in_left_position(void);
bool right_switch_is_in_right_position(void);
void set_left_led(bool turn_on);
void set_right_led(bool turn_on);
uint8_t get_keypress(void);
void test_io(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //IO_FUNCTIONS_H