#include <curses.h>
#include <stdint.h>

#ifndef SSBC_DISPLAY_H
#define SSBC_DISPLAY_H

typedef struct {
    WINDOW *window;
    volatile uint8_t *controlBits;
    uint8_t lastControlBits;
} ssbc_SevenSegmentDisplay;

#define SSBC_NUMBER_OF_SEVEN_SEGMENT_DISPLAYS 4

#define SSBC_SEVEN_SEGMENT_DISPLAY_HEIGHT 7
#define SSBC_SEVEN_SEGMENT_DISPLAY_WIDTH (5 + 2) /* including the dot */
#define SSBC_SEVEN_SEGMENT_DISPLAY_PADDED_WIDTH (SSBC_SEVEN_SEGMENT_DISPLAY_WIDTH + 2)


ssbc_SevenSegmentDisplay createDisplay( uint8_t *controlBits, int y, int x );

void *ssbc_launchDisplayThread( void *args );
// 0th argument is the display array
// 1st argument is a pointer to int, the size of the array

#endif //SSBC_DISPLAY_H
