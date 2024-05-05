/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file starter.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Functions that are Cow Pi model-specific.
 *
 ******************************************************************************/

/*
 * PollingLab (c) 2021-24 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

void initialize_board(void);
void display_string(int row, char const string[]);
void refresh_display(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //DISPLAY_H