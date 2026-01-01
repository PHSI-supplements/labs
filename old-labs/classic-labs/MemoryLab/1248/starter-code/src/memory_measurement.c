#include <stdio.h>
#include "memory_measurement.h"

#define NUMBER_OF_ITERATIONS (20000)

static inline __attribute__((always_inline)) uint32_t get_microseconds(void) {
    uint32_t volatile *timer_lower_word = (uint32_t *) (0x40054028);
    return *timer_lower_word;
}

static uint32_t register_access_time = 0;
static uint32_t sram_access_time = 0;
static uint32_t flash_access_time = 0;


uint32_t time_register_access(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3) {
    uint32_t start, stop;
    uint32_t sum = 0;
    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        for (int j = 0; j < 8; j++) {
            start = get_microseconds();
            sum += a0;
            sum += a1;
            sum += a2;
            sum += a3;
            stop = get_microseconds();
            register_access_time += (stop - start);
        }
    }
    return sum;
}

uint32_t time_sram_access(void) {
    uint32_t volatile *sram_array = (uint32_t *) (0x20000100);       // 0x100 bytes above start of SRAM
    uint32_t start, stop;
    uint32_t sum = 0;
    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        for (int j = 0; j < 8; j++) {
            unsigned long volatile *p = sram_array + j;
            start = get_microseconds();
            sum += *p;
            sum += *(p + 8);
            sum += *(p + 16);
            sum += *(p + 24);
            stop = get_microseconds();
            sram_access_time += (stop - start);
        }
    }
    return sum;
}

uint32_t time_flash_access(void) {
    uint32_t volatile *flash_array = (uint32_t *) (0x13000100);      // 0x100 byes above start of XIP "cache bypass" segment
    uint32_t start, stop;
    uint32_t sum = 0;
    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        for (int j = 0; j < 8; j++) {
            unsigned long volatile *p = flash_array + j;
            start = get_microseconds();
            sum += *p;
            sum += *(p + 8);
            sum += *(p + 16);
            sum += *(p + 24);
            stop = get_microseconds();
            flash_access_time += (stop - start);
        }
    }
    return sum;
}


uint32_t perform_memory_measurement(char destination[][22]) {
    uint32_t sum = 0;
    sum += time_register_access(0, 1, 2, 3);
    sum += time_sram_access();
    sprintf(destination[0], "SRAM:");
    sprintf(destination[1], " %.5fus/read",
            ((sram_access_time - register_access_time)) / (32.0 * NUMBER_OF_ITERATIONS)
           );
    sum += time_flash_access();
    destination[2][0] = '\0';
    sprintf(destination[3], "Flash:");
    sprintf(destination[4], " %.5fus per read\n",
           ((flash_access_time - register_access_time)) / (32.0 * NUMBER_OF_ITERATIONS)
          );
    register_access_time = 0;
    sram_access_time = 0;
    flash_access_time = 0;
//    return sum;
    sprintf(destination[5], "%lu", sum);    // throw-away, but forces compiler not to optimize-away the function calls
    return 5;
}
