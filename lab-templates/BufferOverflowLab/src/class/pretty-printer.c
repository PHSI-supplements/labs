#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pretty-printer.h"

static int maximum_input_size = BUFFER_SIZE;

pretty_printer_t *create_pretty_printer(int requested_input_size, int font_size) {
    pretty_printer_t *new_object = malloc(sizeof(pretty_printer_t));
    if (!new_object) {
        // TODO handle the error
        return nullptr;
    }
    new_object->requested_input_size = requested_input_size;
    if (requested_input_size < 0 || requested_input_size + 1 > maximum_input_size) {
        fgets(new_object->string, requested_input_size, stdin);     // TODO replace with f_get_s
    }
    new_object->actual_input_size = (int) strlen(new_object->string);
    return new_object;
}
