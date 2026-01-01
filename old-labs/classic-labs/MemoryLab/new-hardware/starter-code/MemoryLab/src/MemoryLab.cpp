#include <Arduino.h>
#include <ctype.h>
#include <CowPi_stdio.h>
#include "memory_measurement.h"
#include "cache_measurement.h"


struct option {
    char const *description;
    uint32_t (*function)(void);
};

struct option options[] = {
        {
                .description = "Measure SRAM and Flash memory access times",
                .function = perform_memory_measurement,
        },
         {
                 .description = "Measure the size of the instruction cache using timing data",
                 .function = measure_cache_size,
         },
         {
                 .description = "Determine the size of a cache line using timing data",
                 .function = measure_cache_line_by_time,
         },
        //  {
        //          .description = "Determine the size of a cache line using hit rate",
        //          .function = measure_cache_line_by_hits,
        //  },
};


static int number_of_options = sizeof(options) / sizeof(option);

static inline void validate_input(bool valid, char input) {
    if (!valid) {
        printf("\nInvalid selection: %c. Please enter a value between 1 and %d.\n", input, number_of_options);
    }
}


void setup() {
    cowpi_stdio_setup(9600);
}

void loop() {
    int choice;
    char input = '\0';
    do {
        do {
            printf("\n");
            for (int i = 0; i < number_of_options; i++) {
                printf("%3d. %s\n", i + 1, options[i].description);
            }
            printf("Please choose the measurement you wish to take: ");
            fflush(stdout);
            scanf("%c", &input);
            printf("\n");
            validate_input(isdigit(input), input);
        } while (!isdigit(input));
        choice = input - '0';
        validate_input(0 < choice && choice <= number_of_options, input);
    } while (choice == 0 || choice > number_of_options);
    printf("\n");
    options[choice - 1].function();
} 
