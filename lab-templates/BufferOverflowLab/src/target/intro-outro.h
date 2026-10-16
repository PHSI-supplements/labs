/**************************************************************************//**
 *
 * @file intro-outro.h
 *
 * @author Christopher A. Bohn
 *
 * @sa ../customization/scenario.c
 *
 * @brief Prototypes for the scenario intro/outro accessor functions.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#ifndef INTRO_OUTRO_H
#define INTRO_OUTRO_H

/**
 * Returns the vignette for the start of a stage within the assignment's scenario.
 *
 * @return The scenario's introduction for the stage.
 */
char const *get_intro(void);

/**
 * Returns the vignette for the end of a stage within the assignment's scenario.
 *
 * The specific outro depends not only on the stage but also on the exit code.
 * If multiple exit conditions are present, then the highest-priority condition
 * (defined by the bit significance in the exit code) is used to select the
 * outro.
 *
 * An additional message that is not scenario-specific may also be displayed.
 *
 * @param exit_code The program's upcoming exit code.
 * @return The scenario's outroduction for the stage, given the particulars of
 *      how the student's attack played out.
 */
char const *get_outro(int exit_code);

#endif //INTRO_OUTRO_H
