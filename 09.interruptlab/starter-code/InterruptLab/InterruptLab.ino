/*
 * STUDENT: (Type your name here)
 */

/*
 * InterruptLab (c) 2021-22 Christopher A. Bohn
 */

#include "cowpi.h"

#define DEBOUNCE_TIME 20u
#define NUMBER_OF_DIGITS 8

void setupTimer();
void handleButtonAction();
void handleKeyPress();
void displayData(uint8_t address, uint8_t value);

/* Memory-mapped I/O */
cowpi_ioPortRegisters *ioPorts;     // an array of I/O ports
cowpi_spiRegisters *spi;            // a pointer to the single set of SPI registers
cowpi_timerRegisters16bit *timer1;  // a pointer to one 16-bit timer
cowpi_timerRegisters8bit *timer2;   // a pointer to one 8-bit timer

/* Variables for software debouncing */
unsigned long lastLeftButtonAction = 0;
unsigned long lastRightButtonAction = 0;
unsigned long lastLeftSwitchSlide = 0;
unsigned long lastRightSwitchSlide = 0;
unsigned long lastKeypadPress = 0;


// Layout of Matrix Keypad
//        1 2 3 A
//        4 5 6 B
//        7 8 9 C
//        * 0 # D
// This array holds the values we want each keypad button to correspond to
const uint8_t keys[4][4] = {
  {},
  {},
  {},
  {}
};

// Seven Segment Display mapping between segments and bits
// Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
//  DP   A    B    C    D    E    F    G
// This array holds the bit patterns to display each hexadecimal numeral
const uint8_t sevenSegments[16] = {

};

void setup() {
  Serial.begin(9600);
  cowpi_setup(SPI | MAX7219);
  // ioPorts = ...
  // spi = ...
  setupTimer();
}

void loop() {
  // You can have code here while you're working on the assignment,
  // but be sure there isn't any code here by the time that you're finished.
  ;
}

void setupTimer() {
  // timer1 = ...
  // timer2 = ...
  // ...
}

void handleButtonAction() {
  // ...
}

void handleKeyPress() {
  unsigned long now = millis();
  if (now - lastKeypadPress > DEBOUNCE_TIME) {
    uint8_t keyPressed;
    lastKeypadPress = now;
    // ...
  }
}

void displayData(uint8_t address, uint8_t value) {
  // address is MAX7219's register address (1-8 for digits; otherwise see MAX7219 datasheet Table 2)
  // value is the bit pattern to place in the register
  cowpi_spiEnable;
  // ...
  cowpi_spiDisable;
}
