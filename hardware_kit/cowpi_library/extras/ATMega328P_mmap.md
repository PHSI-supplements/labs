```
/* =================================
 * ARDUINO NANO and UNO (ATMega328P)
 * =================================
 *
 *
 * EXTERNAL PINS
 * Pins `D8_D13` `A0_A5` `D0_D7` cowpi_ioPortRegisters[] at cowpi_io_base + 0x03 (0x23)
 * * D8..D13 at cowpi_io_base + 0x03 (0x23)
 * * A0..A5  at cowpi_io_base + 0x06 (0x26)
 * * D0..D7  at cowpi_io_base + 0x09 (0x29)
 *
 *
 * PIN-BASED INTERRUPTS
 * cowpi_pinInterruptRegisters      at cowpi_io_base + 0x1B (0x3B)
 *
 *
 * PROTOCOLS
 * SPI           cowpi_spiRegisters at cowpi_io_base + 0x2C (0x4C)
 * I2C (aka TWI) cowpi_i2cRegisters at cowpi_io_base + 0x98 (0xB8)
 *
 *
 * TIMER/COUNTERS
 * Timer0 cowpi_timerRegisters8bit  at cowpi_io_base + 0x24 (0x44)
 * Timer1 cowpi_timerRegisters16bit at cowpi_io_base + 0x60 (0x80)
 * Timer2 cowpi_timerRegisters8bit  at cowpi_io_base + 0x90 (0xB0)
 *
 * Timer `0` `1` `2` Interrupt Mask Register uint8_t[] at cowpi_io_base + 0x4E (0x6E)
 * * TIMSKx
 * * 0 at (0x6E)
 * * 1 at (0x6F)
 * * 2 at (0x70)
 * Timer `0` `1` `2` Interrupt Flag Register uint8_t[] at cowpi_io_base + 0x15 (0x35)
 * * TIFRx
 * * 0 at (0x35)
 * * 1 at (0x36)
 * * 2 at (0x37)
 *
 * General Timer/Counter Control Register (Timer0 & Timer1) uint8_t at cowpi_io_base + 0x23 (0x4C)
 * * GTCCR
 * Asynchronous Status Register (Timer2 only)               uint8_t at cowpi_io_base + 0x96 (0xB6)
 * * ASSR
 */
```
