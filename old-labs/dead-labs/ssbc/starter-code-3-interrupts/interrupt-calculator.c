/*
 * STUDENT: (Type your name here)
 * Evaluate for bonus credit: (yes/no)
 */

/*
 * SSBClab (c) 2020-21 Christopher A. Bohn
 */

/******************************************************************************
* In this file, students will implement a simple calculator using signal
* handlers (as simulated interrupt handlers) on the Simulated Single Board
* Computer.
******************************************************************************/

#include "ssbc.h"

int running = 1;

int main() {
    ssbc_launch();
    while (running) {
        ;
    }
    ssbc_terminate();
    return 0;
}
