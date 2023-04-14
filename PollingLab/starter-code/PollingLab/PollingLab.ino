/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file PollingLab.ino
 *
 * @author Christopher A. Bohn
 *
 * @brief Driver code for PollingLab.
 *
 ******************************************************************************/

/*
 * PollingLab (c) 2021-23 Christopher A. Bohn
 *
 * Assignment and starter code licensed under the Apache License,
 * Version 2.0 (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include <CowPi.h>
#include "i2c_address.h"
#include "io_functions.h"
#include "number_builder.h"

static bool test_mode;

void setup() {
  cowpi_stdio_setup(9600);
  cowpi_set_display_i2c_address(I2C_ADDRESS);
  cowpi_setup(LCD1602 | I2C);
  cowpi_lcd1602_set_backlight(true);
  initialize_io();
  initialize_number_system();
  test_mode = digitalRead(11);   // Arduino function doesn't depend on correctness of student code
}

void loop() {
  if (test_mode) {
    test_io();
  } else {
    build_number();
  }
}