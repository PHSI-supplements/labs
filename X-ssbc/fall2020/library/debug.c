#include <string.h>
#include "debug.h"

/* "public" functions */

WINDOW *ssbc_createDebugWindow( int height ) {
    int debugUpperEdge = LINES - height - 1;
    WINDOW *window = newwin(0, 0, debugUpperEdge, 0);
    scrollok(window, true);
    refresh();
    for (int i = 0; i < COLS; i++)
        mvaddch(debugUpperEdge - 1, i, '=');
    char label[] = "DEBUG WINDOW";
    unsigned long labelLeftEdge = (COLS - strlen(label)) / 2;
    mvaddstr(debugUpperEdge - 1, labelLeftEdge, label);
    refresh();
    ssbc_DebugWindow = window;
    return window;
}


