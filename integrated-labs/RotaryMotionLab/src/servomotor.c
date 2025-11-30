/**************************************************************************//**
 *
 * @file rotary-encoder.c
 *
 * @author (TYPE YOUR NAME HERE)
 * @author (TYPE YOUR PARTNER'S NAME HERE, IF APPLICABLE)
 *
 * @brief Code to control a servomotor.
 *
 ******************************************************************************/

/*
 * RotaryMotionLab assignment and starter code (c) 2025 Christopher A. Bohn
 * RotaryMotionLab solution (c) the above-named student(s)
 */

#include <CowPi.h>
#include "display.h"
#include "io_functions.h"
#include "servomotor.h"

static int volatile pulse_width_us;

void center_servo(void) {
}

void servo_step_clockwise(void) {
}

void servo_step_counterclockwise(void) {
}

void shape_pulse() {
    /* THIS FUNCTION IS CALLED BY AN ISR -- DO **NOT** PRINT INSIDE THIS FUNCTION */
}

void test_servo(void) {
    static uint8_t counter = 0xFF;
    counter++;
    if (!(counter & 0x1F)) {
        static int direction = 1;
        static int deflection = 0;
        deflection += direction;
        if (direction > 0) {
            servo_step_counterclockwise();
        } else {
            servo_step_clockwise();
        }
        if (deflection == (MAXIMUM_PULSE_WIDTH_uS - MINIMUM_PULSE_WIDTH_uS) / (2 * PULSE_INCREMENT_uS)
            || deflection == (MINIMUM_PULSE_WIDTH_uS - MAXIMUM_PULSE_WIDTH_uS) / (2 * PULSE_INCREMENT_uS)) {
            direction = -direction;
        }
    }
}
