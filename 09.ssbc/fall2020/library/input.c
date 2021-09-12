#include <pthread.h>
#include <signal.h>
#include "input.h"
#include "running.h"

WINDOW *ssbc_createNumberKey( int number, int base_y, int base_x );
void ssbc_drawNumberKey( WINDOW *numberKeyWindow, int number );
void ssbc_pressNumberKey( ssbc_NumberPad *numberPad, int number );
void ssbc_slideToggle( ssbc_Toggle *toggle );
void ssbc_runInputs( ssbc_NumberPad *numberPad, ssbc_Toggle *toggles );

/* "public" functions */

ssbc_NumberPad ssbc_createNumberPad( uint32_t *controlBits, int y, int x ) { // NOLINT(readability-non-const-parameter)
    uint16_t *bits;
    bits = (uint16_t *)controlBits;
    ssbc_NumberPad numberPad = {.signalBits = bits, .bcdBits = bits + 1};
    *(numberPad.bcdBits) = 0x000F;
    *(numberPad.signalBits) = 0x0000;
    for (int number = 0; number < 10; number++) {
        numberPad.windows[number] = ssbc_createNumberKey(number, y, x);
    }
    return numberPad;
}

ssbc_Toggle
ssbc_createToggle( uint16_t *toggleBits, unsigned int bitOffset, int y, int x ) { // NOLINT(readability-non-const-parameter)
    WINDOW *window = newwin(SSBC_TOGGLE_HEIGHT, SSBC_TOGGLE_WIDTH, y, x);
    // TODO: add size/position validation
    refresh();
    uint16_t onMask = 0x1u << bitOffset;
    uint16_t offMask = ~onMask;
    ssbc_Toggle toggle = {.window=window, .toggleBits = toggleBits, .masks = {offMask, onMask}, .currentPosition = 1};
    ssbc_slideToggle(&toggle);
    return toggle;
}

void *ssbc_launchInputThread( void *args ) {
    // 0th argument is a pointer to the number pad
    // 1st argument is the toggle array
    ssbc_NumberPad *numberPad;
    numberPad = ((ssbc_NumberPad **)args)[0];
    ssbc_Toggle *toggles;
    toggles = ((ssbc_Toggle **)args)[1];
    ssbc_runInputs(numberPad, toggles);
    return NULL;
}

/* "private" functions */

static const char *ssbc_letters[] = {"opr", "   ", "ABC", "DEF", "GHI", "JKL", "MNO", "PRS", "TUV", "WXY"};
static const char SSBC_KEY_PRESS_PAUSE_MS = 100;

WINDOW *ssbc_createNumberKey( int number, int base_y, int base_x ) {
    int row, column;
    if (!number) {
        row = SSBC_NUMBER_KEY_ROWS - 1;
        column = SSBC_NUMBER_KEY_COLUMNS / 2;
    } else {
        row = (number - 1) / (SSBC_NUMBER_KEY_ROWS - 1);
        column = (number - 1) % SSBC_NUMBER_KEY_COLUMNS;
    }
    WINDOW *numberKeyWindow = newwin(SSBC_NUMBER_KEY_HEIGHT, SSBC_NUMBER_KEY_WIDTH,
                                     base_y + row * SSBC_NUMBER_KEY_HEIGHT, base_x + column * SSBC_NUMBER_KEY_WIDTH + column);
    refresh();
    box(numberKeyWindow, '|', '-');
    ssbc_drawNumberKey(numberKeyWindow, number);
    return numberKeyWindow;
}

void ssbc_drawNumberKey( WINDOW *numberKeyWindow, int number ) {
    mvwaddstr(numberKeyWindow, 1, 1, ssbc_letters[number]);
    mvwaddch(numberKeyWindow, 2, SSBC_NUMBER_KEY_WIDTH / 2, (char)number + '0');
    wrefresh(numberKeyWindow);
}

void ssbc_pressNumberKey( ssbc_NumberPad *numberPad, int number ) {
    // TODO: bounds check for number (0..9)
    *(numberPad->bcdBits) = number;
    WINDOW *numberKeyWindow = numberPad->windows[number];
    wstandout(numberKeyWindow); // NOLINT(hicpp-signed-bitwise)
    ssbc_drawNumberKey(numberKeyWindow, number);
    napms(SSBC_KEY_PRESS_PAUSE_MS);
    wstandend(numberKeyWindow);
    ssbc_drawNumberKey(numberKeyWindow, number);
    // set dirty bit
    *(numberPad->signalBits) |= 0x2u;
    // if the interrupt-enable bit is set, issue an "interrupt"
    if (*(numberPad->signalBits) & 0x1u) {
        pthread_mutex_unlock(&ssbc_mutex);
        raise(SIGUSR1);
        pthread_mutex_lock(&ssbc_mutex);
    }
}

static const char ssbc_toggleString[2][2][SSBC_TOGGLE_HEIGHT * (SSBC_TOGGLE_WIDTH + 1)] = {{" | ", "{|}"},
                                                                                           {"{|}", " | "}};

void ssbc_slideToggle( ssbc_Toggle *toggle ) {
    toggle->currentPosition = !toggle->currentPosition;
    if (toggle->currentPosition) {
        *(toggle->toggleBits) |= toggle->masks[1];
    } else {
        *(toggle->toggleBits) &= toggle->masks[0];
    }
    mvwaddstr(toggle->window, 0, 0, ssbc_toggleString[toggle->currentPosition][0]);
    mvwaddstr(toggle->window, 1, 0, ssbc_toggleString[toggle->currentPosition][1]);
    wrefresh(toggle->window);
}

void ssbc_runInputs( ssbc_NumberPad *numberPad, ssbc_Toggle *toggles ) {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
    char input = 0;
#pragma clang diagnostic pop
    int toggleMap[26];
    toggleMap['f' - 'a'] = 0;
    toggleMap['d' - 'a'] = 1;
    toggleMap['s' - 'a'] = 2;
    toggleMap['a' - 'a'] = 3;
    timeout(100);   // we don't need to immediately return, but we also don't want to completely block
    while (ssbc_running) {
        input = getch();
        if (input >= 0) {
            pthread_mutex_lock(&ssbc_mutex);
            switch (input) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    ssbc_pressNumberKey(numberPad, (int)input - '0');
                    break;
                case 'a':
                case 's':
                case 'd':
                case 'f':
                    ssbc_slideToggle(toggles + toggleMap[input - 'a']);
                    break;
                case ' ':
                    wrefresh(curscr);
                    break;
                case 'q':
                    timeout(500);
                    if (getch() == 'u')
                        if (getch() == 'i')
                            if (getch() == 't')
                                ssbc_running = false;
                    timeout(100);
                    break;
                default:
                    beep();
                    flash();
            }
            pthread_mutex_unlock(&ssbc_mutex);
        }
    }
}