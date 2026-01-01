/**************************************************************************//**
 *
 * @file io_functions.c
 *
 * @author (TYPE YOUR NAME HERE)
 * @author (TYPE YOUR PARTNER'S NAME HERE, IF APPLICABLE)
 *
 * @brief Code to read inputs and write to outputs.
 *
 ******************************************************************************/

/*
 * RotaryMotionLab assignment and starter code (c) 2025 Christopher A. Bohn
 * RotaryMotionLab solution (c) the above-named student(s)
 */

#include <CowPi.h>
#include "display.h"
#include "io_functions.h"


// Pointers to memory-mapped I/O structures
static cowpi_ioport_t volatile *ioport;


void initialize_io(void) {
    // Configure the pins (starter code)
    cowpi_set_pullup_input_pins(1 << A_WIPER_PIN | 1 << B_WIPER_PIN);
    cowpi_set_output_pins(1 << SERVO_PIN);
    // Point the `ioport` pointer to the correct address (student task)
//    ioport = (cowpi_ioport_t *) (...);
}

void set_servo_pin(bool logic_value) {
}

uint32_t get_quadrature(void) {
    return 0;   // stub return value
}
