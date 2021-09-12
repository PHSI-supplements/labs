#include <pthread.h>
#include <stdint.h>
#include "display.h"
#include "running.h"

void ssbc_drawDisplay( ssbc_SevenSegmentDisplay *display );
void ssbc_runDisplays( ssbc_SevenSegmentDisplay *displays, int displayCount );

/* "public" functions */

ssbc_SevenSegmentDisplay createDisplay( uint8_t *controlBits, int y, int x ) { // NOLINT(readability-non-const-parameter)
    WINDOW *window = newwin(SSBC_SEVEN_SEGMENT_DISPLAY_HEIGHT, SSBC_SEVEN_SEGMENT_DISPLAY_WIDTH, y, x);
    // TODO: add size/position validation
    refresh();
    ssbc_SevenSegmentDisplay display = {.window=window, .controlBits = controlBits, .lastControlBits = *controlBits};
    ssbc_drawDisplay(&display);
    return display;
}

void *ssbc_launchDisplayThread( void *args ) {
    // 0th argument is the display array
    // 1st argument is a pointer to int, the size of the array
    ssbc_SevenSegmentDisplay *displays;
    int *displayCount;
    displays = ((ssbc_SevenSegmentDisplay **)args)[0];
    displayCount = ((int **)args)[1];
    ssbc_runDisplays(displays, *displayCount);
    return NULL;
}

/* "private" functions */

static const char ssbc_horizontal[] = "---";
static const char ssbc_vertical_partial[] = "|";
static const char ssbc_dot = '.';

static const uint8_t SSBC_UPPER_RIGHT = 0x01;
static const uint8_t SSBC_LOWER_RIGHT = 0x02;
static const uint8_t SSBC_BOTTOM = 0x04;
static const uint8_t SSBC_LOWER_LEFT = 0x08;
static const uint8_t SSBC_UPPER_LEFT = 0x10;
static const uint8_t SSBC_TOP = 0x20;
static const uint8_t SSBC_MIDDLE = 0x40;
static const uint8_t SSBC_DOT = 0x80;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
void ssbc_drawDisplay( ssbc_SevenSegmentDisplay *display ) {
    if (SSBC_TOP & *(display->controlBits)) {
        wstandout(display->window);
    }
    mvwaddstr(display->window, 0, 1, ssbc_horizontal);
    wstandend(display->window);
    if (SSBC_MIDDLE & *(display->controlBits)) {
        wstandout(display->window);
    }
    mvwaddstr(display->window, 3, 1, ssbc_horizontal);
    wstandend(display->window);
    if (SSBC_BOTTOM & *(display->controlBits)) {
        wstandout(display->window);
    }
    mvwaddstr(display->window, 6, 1, ssbc_horizontal);
    wstandend(display->window);
    if (SSBC_UPPER_LEFT & *(display->controlBits)) {
        wstandout(display->window);
    }
    mvwaddstr(display->window, 1, 0, ssbc_vertical_partial);
    mvwaddstr(display->window, 2, 0, ssbc_vertical_partial);
    wstandend(display->window);
    if (SSBC_UPPER_RIGHT & *(display->controlBits)) {
        wstandout(display->window);
    }
    mvwaddstr(display->window, 1, 4, ssbc_vertical_partial);
    mvwaddstr(display->window, 2, 4, ssbc_vertical_partial);
    wstandend(display->window);
    if (SSBC_LOWER_LEFT & *(display->controlBits)) {
        wstandout(display->window);
    }
    mvwaddstr(display->window, 4, 0, ssbc_vertical_partial);
    mvwaddstr(display->window, 5, 0, ssbc_vertical_partial);
    wstandend(display->window);
    if (SSBC_LOWER_RIGHT & *(display->controlBits)) {
        wstandout(display->window);
    }
    mvwaddstr(display->window, 4, 4, ssbc_vertical_partial);
    mvwaddstr(display->window, 5, 4, ssbc_vertical_partial);
    wstandend(display->window);
    if (SSBC_DOT & *(display->controlBits)) {
        wstandout(display->window);
    }
    mvwaddch(display->window, 5, 6, ssbc_dot);
    wstandend(display->window);
    wrefresh(display->window);
}
#pragma clang diagnostic pop

void ssbc_runDisplays( ssbc_SevenSegmentDisplay *displays, int displayCount ) {
    while (ssbc_running) {
        for (int i = 0; i < displayCount; i++) {
            pthread_mutex_lock(&ssbc_mutex);
            if (*(displays[i].controlBits) != displays[i].lastControlBits) {
                ssbc_drawDisplay(displays + i);
                displays[i].lastControlBits = *(displays[i].controlBits);
            }
            pthread_mutex_unlock(&ssbc_mutex);
        }
    }
}