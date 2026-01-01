#include <curses.h>
#include <stdint.h>

#ifndef SSBC_INPUT_H
#define SSBC_INPUT_H

typedef struct {
    WINDOW *windows[10];
    volatile uint16_t *signalBits;
    uint16_t *bcdBits;
} ssbc_NumberPad;

typedef struct {
    WINDOW *window;
    uint16_t *toggleBits;
    uint16_t masks[2]; // off & on masks
    uint8_t currentPosition; // 0 or 1
} ssbc_Toggle;

#define SSBC_NUMBER_OF_TOGGLES 4

#define SSBC_NUMBER_KEY_HEIGHT 4
#define SSBC_NUMBER_KEY_WIDTH 5
#define SSBC_NUMBER_KEY_ROWS 4
#define SSBC_NUMBER_KEY_COLUMNS 3
// unused: #define SSBC_NUMBER_PAD_HEIGHT (SSBC_NUMBER_KEY_HEIGHT * SSBC_NUMBER_KEY_ROWS) /* no padding between rows */
#define SSBC_NUMBER_PAD_WIDTH (SSBC_NUMBER_KEY_WIDTH * SSBC_NUMBER_KEY_COLUMNS + (SSBC_NUMBER_KEY_COLUMNS - 1)) /* padding between columns */

#define SSBC_TOGGLE_HEIGHT 2
#define SSBC_TOGGLE_WIDTH 3
static const char ssbc_toggleKeys[] = {'f', 'd', 's', 'a'};


ssbc_NumberPad ssbc_createNumberPad( uint32_t *controlBits, int y, int x );
ssbc_Toggle ssbc_createToggle( uint16_t *toggleBits, unsigned int bitOffset, int y, int x);

void *ssbc_launchInputThread( void *args );
// 0th argument is a pointer to the number pad
// 1st argument is the toggle array

#endif //SSBC_INPUT_H
