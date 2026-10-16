/**************************************************************************//**
 *
 * @file string-io.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Function prototypes for functions that work with the program's input.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef STRING_IO_H
#define STRING_IO_H

#include <stddef.h>
#include <stdint.h>

/**
 * A drop-in replacement for `gets()`.
 *
 * Like `gets()`, `get_s()` reads from `stdin` until encountering either a
 * newline or an end-of-file marker and places the characters into the
 * destination array, replacing the newline (or EOF) with a NUL character.
 * Importantly, there is no way to limit the number of characters that are
 * read.
 *
 * The principle difference between `gets()` and `get_s()` (besides `gets()`
 * not being available at all in C23 code) is that `get_s()` records a copy
 * of the input and takes snapshots of the stack before & after reading the
 * input.
 *
 * @param destination The buffer that the input should be placed in.
 * @return A pointer to `destination`.
 */
char *get_s(char destination[]);

/**
 * Retrieve the copy of the input that was made by `get_s()`.
 *
 * @return A pointer to the recording of the input.
 */
char const *get_recorded_input(void);

/**
 * Retrieve the number of bytes that was in the input, including the terminating
 * NUL.
 *
 * @return The number of bytes in the input.
 */
size_t get_input_size(void);

#endif //STRING_IO_H
