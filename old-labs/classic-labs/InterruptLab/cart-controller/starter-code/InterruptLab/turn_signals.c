/**************************************************************************/ /**
 *
 * @file turn_signals.c
 *
 * @author (STUDENT -- TYPE YOUR NAME HERE)
 *
 * @brief A setup function and interrupt service routines for the turn signal
 *    subsystem of a remote-controlled cart.
 *
 ******************************************************************************/

/*
 * InterruptLab (c) 2021-23 Christopher A. Bohn
 *
 * Assignment and starter code licensed under the Apache License,
 * Version 2.0 (http://www.apache.org/licenses/LICENSE-2.0).
 */


#include <CowPi.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "turn_signals.h"
#include "supplement.h"

volatile enum turn_directions indicated_turn_direction;
void handle_button_action(void);


void initialize_turn_signals(void) {
  indicated_turn_direction = NO_TURN;


}


void handle_button_action(void) {
  debounce_interrupt({
    static int8_t number_of_buttons_pressed = -1;  // unless there are many, many buttons, this initial value will never occur
    bool left_button_is_pressed; bool right_button_is_pressed;
    while ((left_button_is_pressed = cowpi_left_button_is_pressed())
             + (right_button_is_pressed = cowpi_right_button_is_pressed())
           == number_of_buttons_pressed) {}   // busy-wait through the race condition
    /* Add code to respond to button presses */


    number_of_buttons_pressed = left_button_is_pressed + right_button_is_pressed;
  });
}


ISR(TIMER1_COMPA_vect) {


}
