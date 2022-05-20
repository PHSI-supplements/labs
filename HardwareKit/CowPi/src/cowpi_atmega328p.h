/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

/******************************************************************************
 * This header provides the base address for memory-mapped I/O and
 * data structures to conveniently access the I/O registers.
 ******************************************************************************/

#ifndef COWPI_ATMEGA328P_H
#define COWPI_ATMEGA328P_H

#include <Arduino.h>


uint8_t *const cowpi_io_base = (uint8_t *) 0x20;


#define cowpi_spi_enable do {                           \
    /* Enable SPI, Controller, set clock rate fck/16 */ \
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);      \
} while(0)

#define cowpi_spi_disable do {                          \
    SPCR = 0;                                           \
} while(0)


#define COWPI_PB  0                 // PINB/DDRB/PORTB / PCMSK0
#define D8_D13    0
#define COWPI_PC  1                 // PINC/DDRC/PORTC / PCMSK1
#define A0_A5     1
#define D14_D19   1
#define A0_A7     1
#define D14_D21   1
#define COWPI_PD  2                 // PIND/DDRD/PORTD / PCMSK2
#define D0_D7     2

typedef struct {
    uint8_t input;                      // PINx
    uint8_t direction;                  // DDRx
    uint8_t output;                     // PORTx
} cowpi_ioport_t;

typedef struct {
    uint8_t control;                    // SPCR
    uint8_t status;                     // SPSR
    uint8_t data;                       // SPDR
} cowpi_spi_t;

typedef struct {
    uint8_t bit_rate;                   // TWBR
    uint8_t status;                     // TWSR
    uint8_t address;                    // TWAR
    uint8_t data;                       // TWBB
    uint8_t control;                    // TWCR
    uint8_t peripheral_address_mask;    // TWAMR
} cowpi_i2c_t;

typedef struct {
        // pci = pin change interrupt
        // ei  = external interrupt
    uint8_t pci_flags;                  // PCIFR
    uint8_t ei_flags;                   // EIFR
    uint8_t ei_mask;                    // EIMSK
    uint8_t DO_NOT_TOUCH[0x2A];         // padding
    uint8_t pci_control;                // PCICR
    uint8_t ei_control;                 // EICRA
    uint8_t :8;                         // padding
    uint8_t pci_mask[3];                // PCMSKx
} cowpi_pininterrupt_t;

typedef struct {
    uint16_t control;                   // TCCRxB TCCRxA
    uint8_t counter;                    // TCNTx
    uint8_t compareA;                   // OCRxA
    uint8_t compareB;                   // OCRxB
} cowpi_timer8bit_t;

typedef struct {
    uint32_t control;                 // Reserved TCCRxC TCCRxB TCCRxA
    uint16_t counter;                 // TCNTxH TCNTxL
    uint16_t capture;                 // ICRxH ICRxL
    uint16_t compareA;                // OCRxAH OCRxAL
    uint16_t compareB;                // OCRxBH OCRxBL
} cowpi_timer16bit_t;

#endif //COWPI_ATMEGA328P_H
