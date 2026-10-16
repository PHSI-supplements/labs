/**************************************************************************//**
 *
 * @file intro-outro.c
 *
 * @author Christopher A. Bohn
 *
 * @sa ../customization/scenario.c
 *
 * @brief The scenario intro/outro accessor functions.
 *
 ******************************************************************************/

/*
 * BufferOverflowLab (c) 2025-26 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include <stdio.h>
#include "scenario.h"
#include "intro-outro.h"
#include "global-data.h"

char const *get_intro(void) {
    return intros[stage];
}

char const *get_outro(int exit_code) {
    int outro_index = SCENARIO_INDEX(exit_code);
    if (outro_index < 0) {
        printf("[ERROR, IMPORTANT] Unspecified exit code -- notify your instructor.");
        return "n/a";
    } else if (128 <= exit_code && exit_code <= 255) {
        char const *message;
        char generic_message[20];
        switch(exit_code) {
            // C-standard signals
            case CONTROL_C:
                message = "Terminating after you pressed Control-C";
                break;
            case SEGMENTATION_FAULT:
                message = "Oops! Segmentation Fault.";
                break;
            case ILLEGAL_INSTRUCTION:
                message = "You tried to execute an opcode that doesn't correspond to a valid instruction.";
                break;
            case ABORT:
                message = "Oof! Abort signal.";
                break;
            case BAD_MATH:
                message = "You tried some ill-advised math, such as (perhaps) dividing by zero.";
                break;
            case TERMINATED_EXTERNALLY:
                message = "Received a termination signal from an external source.";
                break;
            // POSIX-standard signals
            case BUS_ERROR:
                message = "Ouch! Memory bus error.";
                break;
            case QUITTED:
                message = "Terminating after you pressed Control-\\.";
                break;
            case KILLED:
                message = "Received a Kill signal from an external source.";
                break;
            default:
                sprintf(generic_message, "Caught signal %3d.", exit_code - 128);
                message = generic_message;
        }
        printf("[ERROR] %s\n", message);
        return outros[stage][outro_index];
    } else {
        return outros[stage][outro_index];
    }
}
