/*
 * Simulated Single Board Computer, (c) 2020 Christopher A. Bohn
 *
 * Student: <place your name here>
 */

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
