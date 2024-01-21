#include "ssbc.h"
#include <stdlib.h>
#include "display.h"
#include "input.h"
#include "debug.h"
#include "running.h"

#define SSBC_SEVEN_SEGMENT_DISPLAYS_UPPER_EDGE 2
#define SSBC_SEVEN_SEGMENT_DISPLAYS_LEFT_EDGE 10
#define SSBC_NUMBER_PAD_UPPER_EDGE 2
#define SSBC_NUMBER_PAD_LEFT_EDGE (80 - SSBC_NUMBER_PAD_WIDTH - 1)
#define SSBC_TOGGLES_UPPER_EDGE (SSBC_SEVEN_SEGMENT_DISPLAYS_UPPER_EDGE + SSBC_SEVEN_SEGMENT_DISPLAY_HEIGHT + 3)
#define SSBC_TOGGLES_LEFT_EDGE SSBC_SEVEN_SEGMENT_DISPLAYS_LEFT_EDGE

int ssbc_original_cursor_state;

void ssbc_initialize();
void ssbc_finalize();
void ssbc_finalize_without_exit();
void ssbc_finalize_on_error( int sig );
void *ssbc_monitor( void *ignored );

/* global variables */

struct {
    pthread_t display;
    pthread_t input;
    pthread_t monitor;
} ssbc_threads;
uint32_t ssbc_numberPadControl;
ssbc_NumberPad ssbc_numberPad;
uint16_t ssbc_toggleControl;
uint8_t *ssbc_displayControls;
ssbc_SevenSegmentDisplay *ssbc_displays;
ssbc_Toggle *ssbc_toggles;
int displayCount;
void **displayArgs;
void **inputArgs;

/* "public" functions */

void ssbc_launch() {
    ssbc_displayControls = calloc(SSBC_NUMBER_OF_SEVEN_SEGMENT_DISPLAYS, sizeof(uint8_t));
    ssbc_displays = calloc(SSBC_NUMBER_OF_SEVEN_SEGMENT_DISPLAYS, sizeof(ssbc_SevenSegmentDisplay));
    ssbc_toggles = calloc(SSBC_NUMBER_OF_TOGGLES, sizeof(ssbc_Toggle));
    ssbc_initialize();
    ssbc_numberPad = ssbc_createNumberPad(&ssbc_numberPadControl, SSBC_NUMBER_PAD_UPPER_EDGE, SSBC_NUMBER_PAD_LEFT_EDGE);
    for (int i = 0; i < SSBC_NUMBER_OF_TOGGLES; i++) {
        int toggleLeftEdge = SSBC_TOGGLES_LEFT_EDGE + (SSBC_NUMBER_OF_TOGGLES - i - 1) * (SSBC_TOGGLE_WIDTH + 1);
        ssbc_toggles[i] = ssbc_createToggle(&ssbc_toggleControl, i, SSBC_TOGGLES_UPPER_EDGE, toggleLeftEdge);
        char label[8];  // twice as much as needed;
        sprintf(label, "(%c)", ssbc_toggleKeys[i]);
        mvaddstr(SSBC_TOGGLES_UPPER_EDGE + SSBC_TOGGLE_HEIGHT + 1, toggleLeftEdge, label);
        refresh();
    }
    for (int i = 0; i < SSBC_NUMBER_OF_SEVEN_SEGMENT_DISPLAYS; i++) {
        int displayLeftEdge = SSBC_SEVEN_SEGMENT_DISPLAYS_LEFT_EDGE +
                              SSBC_SEVEN_SEGMENT_DISPLAY_PADDED_WIDTH * (SSBC_NUMBER_OF_SEVEN_SEGMENT_DISPLAYS - i - 1);
        ssbc_displayControls[i] = 0x00;
        ssbc_displays[i] = createDisplay(ssbc_displayControls + i, SSBC_SEVEN_SEGMENT_DISPLAYS_UPPER_EDGE, displayLeftEdge);
    }
    ssbc_createDebugWindow(3);
    displayCount = SSBC_NUMBER_OF_SEVEN_SEGMENT_DISPLAYS;
    displayArgs = calloc(2, sizeof(void *));
    displayArgs[0] = ssbc_displays;
    displayArgs[1] = &displayCount;
    inputArgs = calloc(2, sizeof(void *));
    inputArgs[0] = &ssbc_numberPad;
    inputArgs[1] = ssbc_toggles;
    pthread_create(&ssbc_threads.display, NULL, ssbc_launchDisplayThread, displayArgs);
    pthread_create(&ssbc_threads.input, NULL, ssbc_launchInputThread, inputArgs);
    pthread_create(&ssbc_threads.monitor, NULL, ssbc_monitor, NULL);
}

void ssbc_terminate() {
    ssbc_running = false;
    ssbc_finalize_without_exit();
}

pthread_mutex_t *ssbc_get_mutex() {
    return &ssbc_mutex;
}

int ssbc_print( const char *fmt, ... ) {
    int bufferSize = COLS * LINES + 1;
    char buffer[bufferSize];  // I *really* doubt anyone would produce a string that files a full terminal window!
    va_list args;
    va_start(args, fmt);
    int charactersCopied = vsnprintf(buffer, bufferSize, fmt, args);
    va_end(args);
    wprintw(ssbc_DebugWindow, buffer);
    wrefresh(ssbc_DebugWindow);
    return charactersCopied;
}

void *ssbc_get_7_segment_address() {
    return ssbc_displayControls;
}

void *ssbc_get_keypad_address() {
    return &ssbc_numberPadControl;
}

void *ssbc_get_toggle_address() {
    return &ssbc_toggleControl;
}


/* "private" functions */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedLocalVariable"

void *ssbc_monitor( void *ignored ) {
    while (ssbc_running) napms(500);
    ssbc_finalize();
    return NULL;
}
#pragma clang diagnostic pop

void ssbc_initialize() {
    ssbc_running = true;
    pthread_mutex_init(&ssbc_mutex, NULL);
    initscr();
    ssbc_original_cursor_state = curs_set(0);
    crmode();
    noecho();
    sigset(SIGINT, ssbc_finalize);
    sigset(SIGABRT, ssbc_finalize_on_error);
    sigset(SIGSEGV, ssbc_finalize_on_error);
    // initially, we'll ignore SIGUSR1 -- the application developer should be able to override this default
    sigset(SIGUSR1, SIG_IGN);
}

void ssbc_finalize_without_exit() {
    ssbc_running = false;
    sigset(SIGINT, SIG_IGN);
    sigset(SIGSEGV, SIG_IGN);
    curs_set(ssbc_original_cursor_state);
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();
}

void ssbc_finalize() {
    ssbc_running = false;
    sigset(SIGINT, SIG_IGN);
    sigset(SIGSEGV, SIG_IGN);
    curs_set(ssbc_original_cursor_state);
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();
    exit(0);
}

void ssbc_finalize_on_error( int sig ) {
    ssbc_running = false;
    sigset(SIGINT, SIG_IGN);
    sigset(SIGABRT, SIG_IGN);
    sigset(SIGSEGV, SIG_IGN);
    curs_set(ssbc_original_cursor_state);
    char *error_message;
    switch (sig) {
        case SIGABRT:
            error_message = "SSBC terminated due to abort signal.";
            break;
        case SIGSEGV:
            error_message = "SSBC terminated due to segmentation fault.";
            break;
        default:
            error_message = "SSBC terminated due to unknown memory error.";
    }
    refresh();
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();
    printf("%s\n", error_message);
    exit(sig);
}
