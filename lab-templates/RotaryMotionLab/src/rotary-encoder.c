/**************************************************************************//**
 *
 * @file rotary-encoder.c
 *
 * @author (TYPE YOUR NAME HERE)
 * @author (TYPE YOUR PARTNER'S NAME HERE, IF APPLICABLE)
 *
 * @brief Functions to report the direction that the rotary encoder is turning.
 *
 ******************************************************************************/

/*
 * RotaryMotionLab assignment and starter code (c) 2025 Christopher A. Bohn
 * RotaryMotionLab solution (c) the above-named student(s)
 */

#include <CowPi.h>
#include "display.h"
#include "io_functions.h"
#include "rotary-encoder.h"

static direction_t volatile direction = STATIONARY;

void sample_rotary_encoder(void) {
    /* THIS FUNCTION IS CALLED BY AN ISR -- DO **NOT** PRINT INSIDE THIS FUNCTION */
}

direction_t get_direction(void) {
    return STATIONARY;  // stub return value
}

void count_rotations(void) {
    static char buffer[18];
    static int clockwise_count = 0;
    static int counterclockwise_count = 0;
    switch (get_direction()) {
        case COUNTERCLOCKWISE:
            counterclockwise_count++;
            break;
        case CLOCKWISE:
            clockwise_count++;
            break;
        default:
            ;
    }
    sprintf(buffer, "CCW %3d  CW %3d", counterclockwise_count, clockwise_count);
    display_string(0, buffer);
}
