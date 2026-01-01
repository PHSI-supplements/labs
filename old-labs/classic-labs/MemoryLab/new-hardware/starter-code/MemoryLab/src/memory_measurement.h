#ifndef MEMORY_MEASUREMENT_H
#define MEMORY_MEASUREMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

uint32_t perform_memory_measurement(void);

uint32_t determine_baseline_time(void);
uint32_t time_register_access(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3);
uint32_t time_sram_access();
uint32_t time_flash_access();

#ifdef __cplusplus
} // extern "C"
#endif

#endif //MEMORY_MEASUREMENT_H