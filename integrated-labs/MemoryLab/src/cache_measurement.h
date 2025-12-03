#ifndef CACHE_MEASUREMENT_H
#define CACHE_MEASUREMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

uint32_t measure_cache_size(char destination[][22]);
uint32_t measure_cache_line_by_time(char destination[][22]);
//uint32_t measure_cache_line_by_hits(char destination[][22]);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //CACHE_MEASUREMENT_H
