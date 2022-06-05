/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

#include "cowpi.h"
#include "cowpi_internal.h"


static unsigned int cowpi_display_device_and_dialect = ADAFRUIT;
static uint8_t display_i2c_address = 255;


/******************************************************************************
 * Setup functions
 ******************************************************************************/

static void cowpi_setup_max7219(unsigned int configuration);
static void cowpi_setup_lcd1602(unsigned int configuration);

void cowpi_setup(unsigned int configuration) {
    /* Simple I/O */
    pinMode( 8, INPUT_PULLUP);  // left button
    pinMode( 9, INPUT_PULLUP);  // right button
    pinMode(18, INPUT_PULLUP);  // aka A4 -- left switch (default, unless using I2C on "standard" variant)
    pinMode(10, INPUT_PULLUP);  // left(TODO?) switch (alternate, unless using SPI on "standard" variant)
    pinMode(19, INPUT_PULLUP);  // aka A5 -- right switch (default, unless using I2C on "standard" variant)
    pinMode(11, INPUT_PULLUP);  // right(TODO?) switch (alternate, unless using SPI on "standard" variant)
    pinMode(12, OUTPUT);        // external LED
    pinMode(13, OUTPUT);        // internal LED
    /* Keypad */
    pinMode( 4, OUTPUT);        // row 1
    pinMode( 5, OUTPUT);        // row 4
    pinMode( 6, OUTPUT);        // row 7
    pinMode( 7, OUTPUT);        // row *
    pinMode(14, INPUT_PULLUP);  // aka A0 -- column 1
    pinMode(15, INPUT_PULLUP);  // aka A1 -- column 2
    pinMode(16, INPUT_PULLUP);  // aka A2 -- column 3
    pinMode(17, INPUT_PULLUP);  // aka A3 -- column A
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    /* External Interrupts */
    pinMode(2, INPUT);          // pushbutton NAND
    pinMode(3, INPUT);          // keypad NAND
    /* Display Module */
    if (configuration & SPI) {
        pinMode(10, OUTPUT);    // we'll always use 10 for chip select when using SPI
        pinMode(MOSI, OUTPUT);  // but 11 isn't COPI for Mega2560
        pinMode(SCK, OUTPUT);   // and 13 isn't SCK for Mega2560
        digitalWrite(10, HIGH);
        digitalWrite(MOSI, LOW);
        digitalWrite(SCK, LOW);
        /* Enabling and disabling SPI must happen just-in-time
         * because enabling SPI overrides DDR for CIPO pin
         * (D12 except on Mega), setting it to input.
         * See cowpi_spi_enable and cowpi_spi_disable. */
    }
    if (configuration & I2C) {
        pinMode(SDA, OUTPUT);   // similarly, D18 aka A4 isn't SDA on Mega2560
        pinMode(SCL, OUTPUT);   // likewise with D19 aka A5 and SCL
        digitalWrite(SDA, HIGH);
        digitalWrite(SCL, HIGH);
        cowpi_initialize_i2c;
    }
    if (configuration & MAX7219) {
        cowpi_display_device_and_dialect |= MAX7219;
        cowpi_setup_max7219(configuration);
    }
    if (configuration & LCD1602) {
        cowpi_display_device_and_dialect |= LCD1602;
        cowpi_setup_lcd1602(configuration);
    }
}

bool cowpi_is_spi_lsbfirst() {
    return ((cowpi_display_device_and_dialect & (DISPLAY_DIALECT_MASK | DISPLAY_DEVICE_MASK)) == (ADAFRUIT | MAX7219));
}

void cowpi_set_display_dialect(unsigned int dialect) {
    cowpi_display_device_and_dialect = (cowpi_display_device_and_dialect & ~DISPLAY_DIALECT_MASK) | dialect;
}

unsigned int cowpi_get_display_dialect() {
    return (cowpi_display_device_and_dialect & DISPLAY_DIALECT_MASK);
}

void cowpi_set_display_i2c_address(uint8_t peripheral_address) {
    if ((peripheral_address < 8) || (peripheral_address > 127)) {
        char s[61];
        cowpi_error(strcpy_P(s, PSTR("I2C Peripheral address must be between 8 and 127, inclusive.")));
    }
    display_i2c_address = peripheral_address;
}

uint8_t cowpi_get_display_i2c_address() {
    return display_i2c_address;
}

static void cowpi_setup_max7219(unsigned int configuration) {
    if (!(configuration & SPI)) {
        char s[79];
        cowpi_error(strcpy_P(s, PSTR("MAX7219 can only be used with SPI protocol. Use `cowpi_setup(MAX7219 | SPI);`.")));
    }
    /* Clear all digit registers */
    for (int i = 1; i <= 8; i++) {
        cowpi_max7219_send(i, 0);
    }
    /* Take display out of decode mode */
    cowpi_max7219_no_decode();
    /* Intensity at 7/32 */
    cowpi_max7219_set_intensity(3);
    /* Scan all eight digits */
    cowpi_max7219_send(0xB, 7);
    /* Take display out of shutdown mode */
    cowpi_max7219_startup();
    /* Take display out of test mode */
    cowpi_max7219_send(0xF, 0);
}

static void cowpi_setup_lcd1602(unsigned int configuration) {
    if (!(configuration & (SPI | I2C))) {
        char s[115];
        cowpi_error(strcpy_P(s, PSTR("CowPi must use a serial protocol with LCD1602. "
                                     "Use `cowpi_setup(LCD1602 | SPI);` or `cowpi_setup(LCD1602 | I2C);`.")));
        // That may not always be the case -- for example, Arduino Mega 2560, Raspberry Pi, or Raspberry Pi Pico
    }
    /* HD44780U datasheet says LCD needs 40ms after Vcc=2.7V, or 15ms after Vcc=4.5V */
    delayMicroseconds(12500);   // Don't want to use delay(50) just in case interrupts are disabled.
    delayMicroseconds(12500);   // Don't want to use delayMicroseconds(50000) because that's 3x longer than
    delayMicroseconds(12500);   // delayMicroseconds is safe for. Note that 16383 == 2**14 - 1 -- this suggests
    delayMicroseconds(12500);   // that while there will be some drift, the real problem is integer overflow
    /* Place in 4-bit mode because 74HC595 is an 8-bit shift register, and we need RS & EN bits, too */
    cowpi_lcd1602_set_4bit_mode(configuration);
    /* 4-bit mode, 2 line display, 5x8 dot matrix */
    cowpi_lcd1602_send_command(0x28);
    /* with each character: increment location, do not shift display (0x06) */
    cowpi_lcd1602_send_command(LCDENTRY_CURSORMOVESRIGHT | LCDENTRY_TEXTNOSHIFT);
    /* display on, cursor off, no blink (0x0C) */
    cowpi_lcd1602_send_command(LCDONOFF_DISPLAYON | LCDONOFF_CURSOROFF | LCDONOFF_BLINKOFF);
    /* clear display */
    cowpi_lcd1602_clear_display();
}

void cowpi_error(const char *message) {
    /* Try to give useful information */
    if (stdout) {
        printf("%s\n", message);
    }
    for (;;) {
        digitalWrite(12, HIGH);
        digitalWrite(13, HIGH);
        /* if interrupts are disabled then both LEDs lit is the best warning we can give */
        delay(1);
        digitalWrite(12, HIGH);
        digitalWrite(13, LOW);
        delay(500);
        digitalWrite(12, LOW);
        digitalWrite(13, HIGH);
        delay(500);
    }
}


/******************************************************************************
 * I/O Functions -- students will re-implement these using memory-mapped I/O
 ******************************************************************************/

static bool cowpi_pin_is_output(uint8_t pin);
static bool cowpi_switch_in_left_position(uint8_t default_pin, uint8_t alternate_pin);
static bool cowpi_switch_in_right_position(uint8_t default_pin, uint8_t alternate_pin);

char cowpi_get_keypress() {
    // returns character corresponding to that on a 4x4 matrix keypad's face (0-9, A-D, *, #)
    // this function is intentionally unreadable
    int8_t a = 0;
    int8_t b = 14;
    uint16_t c;
    char d = '\0';
    e:
    digitalWrite(4, a == 0 ? LOW : HIGH);
    digitalWrite(5, a == 1 ? LOW : HIGH);
    digitalWrite(6, a == 2 ? LOW : HIGH);
    digitalWrite(7, a == 3 ? LOW : HIGH);
    switch (c = !digitalRead(b) * (b + 256 * a + 1024)) {
        case 00000:     if ((a = (int8_t) ((a + 1) & 0x3)) || (++b < 18)) goto e;  else break;
        case 02016: case 02017: case 02020:                 d = (char)(    c - 001735); break;
        case 02416: case 02417: case 02420:                 d = (char)(    c - 002332); break;
        case 03016: case 03017: case 03020:                 d = (char)(    c - 002727); break;
        case 02021: case 02421: case 03021: case 03421:     d = (char)(    a + 000101); break;
        case 03416: case 03417:                             d = (char)(6 * c - 025052); break;
        case 03420:                                         d =                 000043; break;
        default:                                            d =                 000130; break;
    }
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    return d;
}

bool cowpi_left_button_is_pressed() {
    return !digitalRead(8);
}

bool cowpi_right_button_is_pressed() {
    return !digitalRead(9);
}

bool cowpi_left_switch_in_left_position() {
    return cowpi_switch_in_left_position(18, 10);
}

bool cowpi_right_switch_in_left_position() {
    return cowpi_switch_in_left_position(19, 11);
}

bool cowpi_left_switch_in_right_position() {
    return cowpi_switch_in_right_position(18, 10);
}

bool cowpi_right_switch_in_right_position() {
    return cowpi_switch_in_right_position(19, 11);
}

void cowpi_illuminate_external_led() {
    digitalWrite(12, HIGH);
}

void cowpi_illuminate_internal_led() {
    digitalWrite(13, HIGH);
}

void cowpi_deluminate_external_led() {
    digitalWrite(12, LOW);
}

void cowpi_deluminate_internal_led() {
    digitalWrite(13, LOW);
}

static inline bool cowpi_pin_is_output(uint8_t pin) {
    return *portModeRegister(digitalPinToPort(pin)) & digitalPinToBitMask(pin);
}

static bool cowpi_switch_in_left_position(uint8_t default_pin, uint8_t alternate_pin) {
    if (!cowpi_pin_is_output(default_pin)) {            // if default isn't used for I2C then it's used for the switch
        return !digitalRead(default_pin);
    } else if (!cowpi_pin_is_output(alternate_pin)) {   // not using default but make sure alternate not used for SPI
        return !digitalRead(alternate_pin);
    } else {                                            // if both SPI and I2C are in use then there isn't a switch here
        return false;
    }
}

static bool cowpi_switch_in_right_position(uint8_t default_pin, uint8_t alternate_pin) {
    if (!cowpi_pin_is_output(default_pin)) {            // if default isn't used for I2C then it's used for the switch
        return digitalRead(default_pin);
    } else if (!cowpi_pin_is_output(alternate_pin)) {   // not using default but make sure alternate not used for SPI
        return digitalRead(alternate_pin);
    } else {                                            // if both SPI and I2C are in use then there isn't a switch here
        return false;
    }
}
