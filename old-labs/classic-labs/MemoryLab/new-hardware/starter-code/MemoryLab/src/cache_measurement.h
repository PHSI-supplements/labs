#ifndef CACHE_MEASUREMENT_H
#define CACHE_MEASUREMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

uint32_t measure_cache_size();
uint32_t measure_cache_line_by_hits();
uint32_t measure_cache_line_by_time();

#ifdef __cplusplus
} // extern "C"
#endif

#endif //CACHE_MEASUREMENT_H
