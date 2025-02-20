/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file InterruptLab.ino
 *
 * @author Christopher A. Bohn
 *
 * @brief Driver code for InterruptLab.
 *
 ******************************************************************************/

/*
 * InterruptLab (c) 2021-24 Christopher A. Bohn
 *
 * Assignment and starter code licensed under the Apache License,
 * Version 2.0 (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include <CowPi.h>
#include "character_selector.h"
#include "message_editor.h"
#include "inputs.h"
#include "outputs.h"

void setup() {
    initialize_display();
    initialize_editor();
    initialize_selector();
    initialize_interrupts();
}

#if defined (ARDUINO_RASPBERRY_PI_PICO)
void refresh_display(void);
#endif // PICO

void loop() {
#if defined (ARDUINO_RASPBERRY_PI_PICO)
    count_visits(5);
    refresh_display();
#endif // PICO
}
