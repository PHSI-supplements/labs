/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

/******************************************************************************
 * This header has utility functions for peripherals driven by MAX7219.
 ******************************************************************************/

#ifndef COWPI_MAX7219_H
#define COWPI_MAX7219_H


#ifdef __cplusplus
extern "C" {
#endif
void cowpi_max7219_send(uint8_t address, uint8_t data);
void cowpi_max7219_shutdown();
void cowpi_max7219_startup();
void cowpi_max7219_no_decode();
void cowpi_max7219_bcd_decode();
void cowpi_max7219_set_intensity(uint8_t intensity);
#ifdef __cplusplus
} // extern "C"
#endif


inline void cowpi_max7219_shutdown() {
    cowpi_max7219_send(0xC, 0);
}

inline void cowpi_max7219_startup() {
    cowpi_max7219_send(0xC, 1);
}

inline void cowpi_max7219_no_decode() {
    cowpi_max7219_send(0x9, 0);
}

inline void cowpi_max7219_bcd_decode() {
    cowpi_max7219_send(0x9, 0xF);
}

inline void cowpi_max7219_set_intensity(uint8_t intensity) {
    cowpi_max7219_send(0xA, intensity & 0xF);
}

#endif //COWPI_MAX7219_H
