/**************************************************************************//**
*
* @file string-io.h
*
* @author Christopher A. Bohn
*
* @brief Functions that work with the program's input.
*
******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include <stdlib.h>
#include <stdio.h>
#include "global-data.h"
#include "stack.h"
#include "string-io.h"

constexpr char const hexdigits[] = "0123456789ABCDEF";
static char *input = nullptr;                   //!< the buffer for the recorded input; the buffer may grow
static size_t input_buffer_size = 300;          //!< The size of the buffer for the recorded input; the buffer may grow
static size_t input_size = 0;                   //!< The number of bytes in the input that have been read (so far)

/**
 * Helper function to record a single byte of the input.
 *
 * @param byte          The byte to be recorded.
 * @param after_byte    A space or newline to be placed after the human-readable form of the byte.
 */
static void record_input_byte(uint8_t byte, char after_byte);

char *get_s(char *destination) {
    input = malloc(3 * input_buffer_size);
    if (!input) {
        fprintf(stderr, "[MEMORY ALLOCATION FAILURE] Could not allocate space to record input.\n");
        if (print_input) {
            printf("[INFO] Your attack will continue, but the printed input will be blank.\n");
        } else {
            printf("[INFO] This will not affect your attack.\n");
        }
    }
    int c;
    buffer_on_stack = (uintptr_t *) destination;
    snapshot_stack_words(stack_snapshots[0], buffer_on_stack, preferred_snapshot_count);
    while (((c = getc(stdin)) != EOF) && (c != '\n')) {
        if (input) record_input_byte(c, ' ');
        *destination++ = (char) c;
        input_size++;
    }
    if (input) {
        record_input_byte('\0', '\0');
    } else {
        input = "";
    }
    *destination = '\0';
    input_size++;
    destination = (char *) buffer_on_stack;
    snapshot_stack_words(stack_snapshots[1], buffer_on_stack, preferred_snapshot_count);
    return destination;
}

char const *get_recorded_input(void) {
    return input;
}

size_t get_input_size(void) {
    return input_size;
}

static void record_input_byte(uint8_t byte, char after_byte) {
    if (input_size >= input_buffer_size - 1) {      // "-1" to allow room for NUL termination if realloc fails
        input_buffer_size *= 2;
        char *new_buffer = realloc(input, 3 * input_buffer_size);
        if (new_buffer) {
            input = new_buffer;
        } else {
            input_buffer_size /= 2;   // for reporting purposes
            printf("[MEMORY ALLOCATION FAILURE] Could not allocate space to record input after %zu bytes.", input_size);
            if (print_input) {
                printf("[INFO] Your attack will continue, but the printed input will not be the full input.\n");
            } else {
                printf("[INFO] This will not affect your attack.\n");
            }
            input[3 * input_size] = '\0';
            return;
        }
    }
    input[3 * input_size + 0] = hexdigits[byte >> 4];
    input[3 * input_size + 1] = hexdigits[byte & 0xF];
    input[3 * input_size + 2] = after_byte;
}
