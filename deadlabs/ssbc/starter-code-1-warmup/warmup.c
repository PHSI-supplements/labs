/*
 * STUDENT: (Type your name here)
 */

/*
 * SSBClab (c) 2020-21 Christopher A. Bohn
 */

/******************************************************************************
* This file will demonstrate a simple familiarity with the SSBC library to
* prepare students for desigining solutions to problems on the Simulated
* Single Board Computer.
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
