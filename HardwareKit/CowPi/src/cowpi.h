/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

/******************************************************************************
 * This header provides the base address for memory-mapped I/O and
 * data structures to conveniently access the I/O registers.
 ******************************************************************************/

#ifndef COWPI_H
#define COWPI_H

#include "Arduino.h"


/* Public-facing function prototypes */

void cowpi_setup(unsigned int configuration);
void cowpi_stdio_setup(unsigned long baud);
char cowpi_get_keypress();
void cowpi_send_data_to_max7219(uint8_t address, uint8_t value);
void cowpi_send_data_to_spi_lcd1602(uint8_t address, uint8_t value);
bool cowpi_left_button_is_pressed();
bool cowpi_right_button_is_pressed();
bool cowpi_left_switch_in_left_position();
bool cowpi_right_switch_in_left_position();
bool cowpi_left_switch_in_right_position();
bool cowpi_right_switch_in_right_position();
void illuminate_led();
void deluminate_led();


/* Use to create argument to cowpi_setup() */

#define SPI                     0x01
#define I2C                     0x02
#define MAX7219                 0x80
#define LCD1602                 0x40


/* Board-specific definitions */

#if defined ARDUINO_AVR_UNO || defined ARDUINO_AVR_NANO
uint8_t * const cowpi_io_base = (uint8_t *)0x20;

#define cowpi_spi_enable do {                           \
    /* Enable SPI, Controller, set clock rate fck/16 */ \
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);      \
} while(0)

#define cowpi_spi_disable do {                          \
    SPCR = 0;                                           \
} while(0)

#elif defined ARDUINO_AVR_NANO_EVERY
uint8_t * const cowpi_io_base = (uint8_t *)0x0;
#error Arduino Nano Every is not yet supported for CowPi
#elif defined ARDUINO_NANO33BLE
// double-check whether Nano 33 BLE Sense is a distinct board wrt IDE
#error Arduino Nano 33 BLE is not yet supported for CowPi
#elif defined ARDUINO_SAMD_NANO_33_IOT
#error Arduino Nano 33 IOT is not yet supported for CowPi
#elif defined ARDUINO_NANO_RP2040_CONNECT
#error Arduino Nano RP2040 is not yet supported for CowPi
#elif defined ARDUINO_AVR_MEGA2560
#error Arduino Mega 2560 is not yet supported for CowPi
#elif defined ARDUINO_RASPBERRY_PI_PICO
#error Raspberry Pi Pico Arduino core is not yet supported for CowPi
#else
#error Your microcontroller board is not yet supported for CowPi.
#endif //MICROCONTROLLER BOARD






#if defined ARDUINO_AVR_UNO || defined ARDUINO_AVR_NANO

#define D8_D13  0                 // PINB/DDRB/PORTB / PCMSK0
#define A0_A5   1                 // PINC/DDRC/PORTC / PCMSK1
#define D0_D7   2                 // PIND/DDRD/PORTD / PCMSK2
#define PORT_B  0                 // PINB/DDRB/PORTB / PCMSK0
#define PORT_C  1                 // PINC/DDRC/PORTC / PCMSK1
#define PORT_D  2                 // PIND/DDRD/PORTD / PCMSK2

typedef struct {
  volatile uint8_t input;                   // PINx
  volatile uint8_t direction;               // DDRx
  volatile uint8_t output;                  // PORTx
} cowpi_ioPortRegisters;

typedef struct {
  volatile uint8_t control;                 // SPCR
  volatile uint8_t status;                  // SPSR
  volatile uint8_t data;                    // SPDR
} cowpi_spiRegisters;

typedef struct {
  volatile uint8_t bit_rate;                // TWBR
  volatile uint8_t status;                  // TWSR
  volatile uint8_t address;                 // TWAR
  volatile uint8_t data;                    // TWBB
  volatile uint8_t control;                 // TWCR
  volatile uint8_t peripheral_address_mask; // TWAMR
} cowpi_i2cRegisters;

typedef struct {
  // pci = pin change interrupt
  // ei  = external interrupt
  volatile uint8_t pci_flags;               // PCIFR
  volatile uint8_t ei_flags;                // EIFR
  volatile uint8_t ei_mask;                 // EIMSK
  volatile uint8_t __DO_NOT_TOUCH_1__[0x2A];// padding
  volatile uint8_t pci_control;             // PCICR
  volatile uint8_t ei_control;              // EICRA
  volatile uint8_t __DO_NOT_TOUCH_2__;      // padding
  volatile uint8_t pci_mask[3];             // PCMSKx
                  // * D8..D13 at (0x6B)
                  // * A0..A5  at (0x6C)
                  // * D0..D7  at (0x6D)
} cowpi_pinInterruptRegisters;

typedef struct {
  volatile uint16_t control;                // TCCRxB TCCRxA
  volatile uint8_t  counter;                // TCNTx
  volatile uint8_t  compareA;               // OCRxA
  volatile uint8_t  compareB;               // OCRxB
} cowpi_timerRegisters8bit;

typedef struct {
  volatile uint32_t control;                // Reserved TCCRxC TCCRxB TCCRxA
  volatile uint16_t counter;                // TCNTxH TCNTxL
  volatile uint16_t capture;                // ICRxH ICRxL
  volatile uint16_t compareA;               // OCRxAH OCRxAL
  volatile uint16_t compareB;               // OCRxBH OCRxBL
} cowpi_timerRegisters16bit;

#endif //NANO



#endif //COWPI_H
