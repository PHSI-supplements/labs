/*
 * STUDENTS: (Type your names here)
 */

/*
 * CombinationLock GroupLab (c) 2022 Christopher A. Bohn
 */

#include <EEPROM.h>
#include "cowpi.h"

void setup() {
  Serial.begin(9600);
  cowpi_setup(SPI | MAX7219);
  ;  
}

void loop() {
  ;
}
