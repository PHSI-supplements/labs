#include <stdio.h>
#include "cache_measurement.h"

// 64 KB
#define MAX_WORKING_SET_SIZE (1 << 16)

uint8_t volatile *cache = (uint8_t *) (0x10001300);    // 0x1300 byes above start of XIP "normal cache operation" segment

static inline __attribute__((always_inline)) uint32_t get_microseconds(void)  {
    uint32_t volatile *timer_lower_word = (uint32_t *) (0x40054028);
    return *timer_lower_word;
}

static inline uint32_t flush_cache(void) {
    /* Write 1 to flush the cache.
     * This clears the tag memory, but the data memory retains its contents.
     * (This means cache-as-SRAM contents is not affected by flush or reset.)
     * Reading will hold the bus (stall the processor) until the flush completes.
     * Alternatively STAT can be polled until completion.
     */
    uint32_t volatile *cache_flush = (uint32_t *) (0x14000004);
    /* Bit0 is FLUSH_READY
     * Reads as 0 while a cache flush is in progress, and 1 otherwise.
     * The cache is flushed whenever the XIP block is reset, and also when requested via the FLUSH register.
     */
    uint32_t volatile *cache_status = (uint32_t *) (0x14000008);
    *cache_flush = 1;
    while (!(*cache_status & 0x1)) {}
    return 0;
}

static inline uint32_t fill_cache_with_junk(void) {
    // if flushing the cache crashes MBED OS,
    // then we'll fill the cache with *other* data that should occupy the same cache sets
    uint32_t sum = 0;
    int data_size = 1 << 10;   // 1 KB
    int stride = 2;
    uint8_t volatile *junk = cache + 0x500;
    uint8_t volatile *end_of_junk = junk + data_size;
    for (volatile uint8_t *data = junk; data < end_of_junk; data += stride) {
        sum += *data;
    }
    // do it again since the cache is 2-way set associative
    junk = junk + 0x500;
    end_of_junk = junk + data_size;
    for (volatile uint8_t *data = junk; data < end_of_junk; data += stride) {
        sum += *data;
    }
    return sum;
}


static uint32_t measure_helper(int working_set_size) {
    int stride = 8;
    uint32_t start, stop;
    uint32_t sum = 0;
    uint8_t volatile *end_of_data = cache + working_set_size;
    long long number_of_iterations = (1LL << 15) * stride / working_set_size;
    // we'll treat flash memory as read-only, so to prime the cache we'll copy whatever we find in flash
    // iterate backwards so that the start fo the "array" is in cache
    for (int i = working_set_size - 1; i >= 0; i--) {
        sum += cache[i];   // to prime the cache
    }
    // cache is now primed
    start = get_microseconds();
    for (long long i = 0; i < number_of_iterations; i++) {
        for (volatile uint8_t *data = cache; data < end_of_data; data += stride) {
            sum += data[i];
        }
    }
    stop = get_microseconds();
    printf("Time spent working with data when working set is %d bytes: %lu microseconds\n",
           working_set_size, (stop - start));
    return sum;
}


uint32_t measure_cache_size() {
    printf("\nTrying differently-sized working sets to determine cache sizes.\n");
    for (int working_set_size = 32; working_set_size < MAX_WORKING_SET_SIZE; working_set_size *= 2) {
        measure_helper(working_set_size);
        measure_helper(working_set_size + working_set_size / 4); // approximately +1dB
        measure_helper(working_set_size + working_set_size / 2); // approximately +2dB
    }
    measure_helper(MAX_WORKING_SET_SIZE);
    printf("\n");
    return 0;
}

uint32_t measure_cache_line_by_time() {
    /* Bit1 is FIFO_EMPTY
     * Reads as 1 when the XIP streaming FIFO is completely empty.
     */
    uint32_t volatile *cache_status = (uint32_t *) (0x14000008);

    printf("\nTrying different strides to determine cache line size.\n");
    uint32_t start, stop;
    uint32_t sum = 0;
    int data_size = 1 << 10;   // 1 KB
    int minimum_stride = 2;
    int maximum_stride = 64;
    uint8_t volatile *end_of_data = cache + data_size;
    for (int stride = minimum_stride; stride <= maximum_stride; stride *= 2) {
        int number_of_iterations = (1 << 10) * stride / minimum_stride;
//        flush_cache();              // This sometimes causes MBED OS to crash -- probably trying to do some OS work while the cache is being flushed
        fill_cache_with_junk();     // If we can't flush the cache, we can fill it with garbage instead
        start = get_microseconds();
        for (int i = 0; i < number_of_iterations; i++) {
            for (volatile uint8_t *data = cache; data < end_of_data; data += stride) {
                sum += *data;
                while(!(*cache_status & 0x2)) {}
            }
        }
        stop = get_microseconds();
        printf("Time spent working with data when stride is %d bytes: %lu microseconds\n", stride, (stop - start));
    }
    printf("\n");
    return sum;
}

uint32_t measure_cache_line_by_hits() {
    /* Bit1 is FIFO_EMPTY
     * Reads as 1 when the XIP streaming FIFO is completely empty.
     */
    uint32_t volatile *cache_status = (uint32_t *) (0x14000008);

//    uint32_t volatile *cache_hits = (uint32_t *) (0x1400000C);
//    uint32_t volatile *cache_accesses = (uint32_t *) (0x14000010);
    uint64_t volatile *cache_statistics = (uint64_t *) (0x1400000C);
    uint32_t hits = 0;
    uint32_t accesses = 0;
    uint8_t volatile *data = cache + 0x400;
    uint32_t sum = 0;
    flush_cache();
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 64; j++) {
            data += 0x100;
            sum += *data;
            while (!(*cache_status & 0x2)) {}
//            *cache_hits = 0;
//            *cache_accesses = 0;
            *cache_statistics = 0;
            sum += *(data + i);
//            hits += *cache_hits;
//            accesses += *cache_accesses;
            uint64_t statistics = *cache_statistics;
            hits += statistics & 0xFFFFFFFF;
            accesses += statistics >> 32;
        }
        printf("Accessing element x, then element x+%d, yielded %lu cache hits out of %lu reads\n", i, hits, accesses);
        hits = 0;
        accesses = 0;
    }
    return sum;
}
