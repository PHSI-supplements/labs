#include <CowPi.h>
#include "display.h"
#include "memory_measurement.h"
#include "cache_measurement.h"

struct option {
    char const *description;
    uint32_t (*function)(char destination[][22]);
};

struct option options[] = {
        {
//                .description = "Measure SRAM and Flash memory access times",
                .description = "Memory access time",
                .function = perform_memory_measurement,
        },
        {
//                .description = "Measure the size of the instruction cache using timing data",
                .description = "Cache size",
                .function = measure_cache_size,
        },
        {
//                .description = "Determine the size of a cache line using timing data",
                .description = "Cache line size",
                .function = measure_cache_line_by_time,
        },
        //  {
        //          .description = "Determine the size of a cache line using hit rate",
        //          .function = measure_cache_line_by_hits,
        //  },
};


static int const number_of_options = sizeof(options) / sizeof(struct option);

static inline void validate_input(bool valid, char input) {
    if (!valid) {
        printf("\nInvalid selection: %c. Please enter a value between 1 and %d.\n", input, number_of_options);
    }
}


void setup() {
    cowpi_setup(0,
                (cowpi_display_module_t) {.display_module = NO_MODULE},
                (cowpi_display_module_protocol_t) {.protocol = NO_PROTOCOL}
               );
    initialize_display(21);
    draw_logo();
    delay(1000);
}

void loop() {
    static char buffer[40][22];
    char choice = '\0';
    display_string(0, "      MemoryLab");
    for (int i = 1; i < 7; i++) {
        display_string(i, "");
    }
    display_string(1, "");
    for (int i = 0; i < number_of_options; i++) {
        sprintf(buffer[i + 2], "%1d. %-18s", i + 1, options[i].description);
        display_string(i + 2, buffer[i + 2]);
    }
    display_string(7, "Select choice");
    refresh_display();
    do {
        choice = cowpi_get_keypress();
    } while (choice < '1' || choice > number_of_options + '0');
    uint32_t number_of_lines_to_print = options[choice - '0' - 1].function(buffer);
    uint32_t i = 0;
    while (i < number_of_lines_to_print) {
        while (cowpi_debounce_byte(cowpi_left_button_is_pressed(), LEFT_BUTTON_DOWN)) {}
        int row = 0;
        while (i < number_of_lines_to_print && row < 6) {
            display_string(row, buffer[i]);
            buffer[i][0] = '\0';
            i++;
            row++;
        }
        while (row < 6) {
            display_string(row, "");
            row++;
        }
        display_string(6, "Press left button");
        display_string(7, "          to continue");
        refresh_display();
        while (!cowpi_debounce_byte(cowpi_left_button_is_pressed(), LEFT_BUTTON_DOWN)) {}
    }
} 
