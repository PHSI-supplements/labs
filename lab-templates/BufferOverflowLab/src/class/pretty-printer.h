#ifndef PRETTY_PRINTER_H
#define PRETTY_PRINTER_H

#include "../customization/randomization.h"

typedef struct {
    int requested_input_size;
    int actual_input_size;
    char string[BUFFER_SIZE];
    int font_size;
    int bar[3];
} pretty_printer_t;

pretty_printer_t *create_pretty_printer(int requested_input_size, int font_size);

#endif //PRETTY_PRINTER_H
