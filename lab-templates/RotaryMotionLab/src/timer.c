/**************************************************************************//**
 *
 * @file timer.c
 *
 * @author (TYPE YOUR NAME HERE)
 * @author (TYPE YOUR PARTNER'S NAME HERE, IF APPLICABLE)
 *
 * @brief Code to generate a periodic timer interrupt that is used to shape a
 *      servo's pulse and to sample a rotary encoder.
 *
 ******************************************************************************/

/*
 * RotaryMotionLab assignment and starter code (c) 2025 Christopher A. Bohn
 * RotaryMotionLab solution (c) the above-named student(s)
 */

#include "interrupt_support.h"
#include "servomotor.h"
#include "rotary-encoder.h"
#include "timer.h"

static void handle_timer_interrupt(void);

void initialize_timer(void) {
}

static void handle_timer_interrupt(void) {
}
