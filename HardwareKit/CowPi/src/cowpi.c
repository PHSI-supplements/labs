/*
 * CowPi (c) 2021-22 Christopher A. Bohn
 */

#include "cowpi.h"
#include "cowpi_internal.h"


static unsigned int cowpi_display_device_and_dialect = STANDARD;
static uint8_t display_i2c_address = 255;


/******************************************************************************
 * Setup functions
 ******************************************************************************/

static void cowpi_setup_max7219(unsigned int configuration);
static void cowpi_setup_lcd1602(unsigned int configuration);

void cowpi_setup(unsigned int configuration) {
    /* Switches and Buttons */
    pinMode( LEFT_BUTTON, INPUT_PULLUP);
    pinMode( RIGHT_BUTTON, INPUT_PULLUP);
    pinMode(LEFT_SWITCH_DEFAULT, INPUT_PULLUP);     // When using SPI or when no protocol is specified
    pinMode(LEFT_SWITCH_ALTERNATE, INPUT_PULLUP);   // When using I2C
    pinMode(RIGHT_SWITCH_DEFAULT, INPUT_PULLUP);    // When using SPI or when no protocol is specified
    pinMode(RIGHT_SWITCH_ALTERNATE, INPUT_PULLUP);  // When using I2C
    pinMode(LED_EXTERNAL, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    /* Keypad */
    pinMode( KEYPAD_ROW_1, OUTPUT);
    pinMode( KEYPAD_ROW_4, OUTPUT);
    pinMode( KEYPAD_ROW_7, OUTPUT);
    pinMode( KEYPAD_ROW_STAR, OUTPUT);
    pinMode(KEYPAD_COLUMN_1, INPUT_PULLUP);
    pinMode(KEYPAD_COLUMN_2, INPUT_PULLUP);
    pinMode(KEYPAD_COLUMN_3, INPUT_PULLUP);
    pinMode(KEYPAD_COLUMN_A, INPUT_PULLUP);
    digitalWrite(KEYPAD_ROW_1, LOW);
    digitalWrite(KEYPAD_ROW_4, LOW);
    digitalWrite(KEYPAD_ROW_7, LOW);
    digitalWrite(KEYPAD_ROW_STAR, LOW);
    /* External Interrupts */
    pinMode(PUSHBUTTON_NAND, INPUT);
    pinMode(KEYPAD_NAND, INPUT);
    /* Display Module */
    if (configuration & SPI) {
        pinMode(SPI_CHIP_SELECT, OUTPUT);
        pinMode(MOSI, OUTPUT);
        pinMode(SCK, OUTPUT);
        digitalWrite(SPI_CHIP_SELECT, HIGH);
        digitalWrite(MOSI, LOW);
        digitalWrite(SCK, LOW);
        /* Enabling and disabling SPI must happen just-in-time
         * because enabling SPI overrides DDR for CIPO pin
         * (D12 except D50 on Mega2560), setting it to input.
         * See `cowpi_spi_enable` and `cowpi_spi_disable`. */
    }
    if (configuration & I2C) {
        pinMode(SDA, OUTPUT);
        pinMode(SCL, OUTPUT);
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
    return ((cowpi_display_device_and_dialect & (DISPLAY_DIALECT_MASK | DISPLAY_DEVICE_MASK)) == (ADAFRUIT | LCD1602));
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
        digitalWrite(LED_EXTERNAL, HIGH);
        digitalWrite(LED_BUILTIN, HIGH);
        /* if interrupts are disabled then both LEDs lit is the best warning we can give */
        delay(1);
        digitalWrite(LED_EXTERNAL, HIGH);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        digitalWrite(LED_EXTERNAL, LOW);
        digitalWrite(LED_BUILTIN, HIGH);
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
    // (it also won't work right on Mega 2560, but we can fix that)
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
    return !digitalRead(LEFT_BUTTON);
}

bool cowpi_right_button_is_pressed() {
    return !digitalRead(RIGHT_BUTTON);
}

bool cowpi_left_switch_in_left_position() {
    return cowpi_switch_in_left_position(LEFT_SWITCH_DEFAULT, LEFT_SWITCH_ALTERNATE);
}

bool cowpi_right_switch_in_left_position() {
    return cowpi_switch_in_left_position(RIGHT_SWITCH_DEFAULT, RIGHT_SWITCH_ALTERNATE);
}

bool cowpi_left_switch_in_right_position() {
    return cowpi_switch_in_right_position(LEFT_SWITCH_DEFAULT, LEFT_SWITCH_ALTERNATE);
}

bool cowpi_right_switch_in_right_position() {
    return cowpi_switch_in_right_position(RIGHT_SWITCH_DEFAULT, RIGHT_SWITCH_ALTERNATE);
}

void cowpi_illuminate_external_led() {
    digitalWrite(LED_EXTERNAL, HIGH);
}

void cowpi_illuminate_internal_led() {
    digitalWrite(LED_BUILTIN, HIGH);
}

void cowpi_deluminate_external_led() {
    digitalWrite(LED_EXTERNAL, LOW);
}

void cowpi_deluminate_internal_led() {
    digitalWrite(LED_BUILTIN, LOW);
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
