/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file character_selector.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Functions to select the message's next character
 *
 ******************************************************************************/

/*
 * InterruptLab (c) 2021-23 Christopher A. Bohn
 * Number Pad Texter (c) 2023 Christopher A. Bohn
 *
 * Assignment and starter code licensed under the Apache License,
 * Version 2.0 (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef CHARACTER_SELECTOR_H
#define CHARACTER_SELECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

void initialize_selector(void);
void update_character(char key_face);
void finalize_character(void);
void reset_selector();

#ifdef __cplusplus
} // extern "C"
#endif

#endif //CHARACTER_SELECTOR_H