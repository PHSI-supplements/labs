uint8_t digit = 8;
int8_t step = 0;

void sendData(uint8_t address, uint8_t value) {
  // Sends data to MAX7219 using shiftOut, not using SPI hardware
  // address is register address (1-8 for digits; otherwise see datasheet Table 2)
  // value is the value to place in the register
  digitalWrite(SS, LOW);
  shiftOut(MOSI, SCK, MSBFIRST, address);
  shiftOut(MOSI, SCK, MSBFIRST, value);
  digitalWrite(SS, HIGH);
}

void setup() {
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  /*
  pinMode(SS, OUTPUT);    // pin 10: serial select, aka CS
  pinMode(MOSI, OUTPUT);  // pin 11: MOSI, aka DIN
  pinMode(SCK, OUTPUT);   // pin 13: serial clock, aka CLK
  for (int i = 1; i <= 8; i++)
    sendData(i, 0xFF);     // fill all digit registers
  sendData(0xA, 0xF);     // intensity at 31/32
  sendData(0xB, 0x7);     // scan all eight digits
  sendData(0xC, 0x1);     // take display out of shutdown mode
  sendData(0xF, 0x0);     // Put display into test mode
  */
}

void loop() {
}
