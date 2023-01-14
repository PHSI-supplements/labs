#include <curses.h>
#include <stdint.h>

#ifndef SSBC_DEBUG_H
#define SSBC_DEBUG_H

WINDOW *ssbc_DebugWindow;

WINDOW *ssbc_createDebugWindow( int height );

#endif //SSBC_DEBUG_H
