/**************************************************************************/ /**
 *
 * @file cart_controller.c
 *
 * @author (STUDENT -- TYPE YOUR NAME HERE)
 *
 * @brief An initialization function and main loop function for the
 *    simulated control of a simulated cart. Also the interrupt service routines
 *    for controlling the motion and updating the distance/direction of that
 *    cart.
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
#include <string.h>
#include "cart_controller.h"
#include "turn_signals.h"
#include "supplement.h"


// A couple of handy non-ASCII characters if you want them for your display
// ROM CODE 0
const char MU = (char)0xE4;
const char DEGREE = (char)0xDF;
// ROM CODE 2
// const char MU = (char)0xB5;
// const char DEGREE = (char)0xB0;

volatile bool display_needs_refreshed;

void handle_key_action(void);


void initialize_cart_system(void) {
  display_needs_refreshed = true;
  /* USE THIS CODE TO DETERMINE WHICH ROM CODE YOUR DISPLAY MODULE HAS, AND
     SET MU and DEGREE ACCORDINGLY ON LINE 32-38. THEN COMMENT-OUT THE NEXT
     EIGHT LINES AFTER THIS COMMENT */
  char label_string[] = "mu        degree";
  char candidates_string[17] = {0};
  if (display_needs_refreshed) {
    sprintf(candidates_string, "0:%c 2:%c  0:%c 2:%c", (char)0xE4, (char)0xB5, (char)0xDF, (char)0xB0);
    display_needs_refreshed = false;
    display_string(label_string, TOP_ROW);
    display_string(candidates_string, BOTTOM_ROW);
  }
  /* END OF CODE TO DETERMINE YOUR DISPLAY MODULE'S ROM CODE */


}

void control_cart(void) {
  static char top_line[17];
  static char bottom_line[17];
  if (display_needs_refreshed) {
    display_needs_refreshed = false;
    /* Add to create the strings to be displayed */


    display_string(top_line, TOP_ROW);
    display_string(bottom_line, BOTTOM_ROW);
  }
  /* Add any other code that you want to run each iteration of the main loop */

  
}


void handle_key_action(void) {
  debounce_interrupt({
    static char last_key = 0xF0;  // Whether we're getting ASCII characters or (hexa)decimal values, this initial value won't occur
    char key;
    while ((key = cowpi_get_keypress()) == last_key) {}   // busy-wait through the race condition
    /* Add code to respond to key presses and releases */

    
    last_key = key;
  });
}


ISR(TIMER2_COMPA_vect) {


}

