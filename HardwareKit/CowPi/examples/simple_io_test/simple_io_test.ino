#include "cowpi.h"

void setup() {
    cowpi_stdio_setup(9600);
    char s[83];
    printf("%s", strcpy_P(s, PSTR("This demonstration makes no assumptions about your CowPi's display module,\n\r")));
    printf("%s", strcpy_P(s, PSTR("\tso your display module may display garbage -- that's okay.\n\r")));
    printf("%s", strcpy_P(s, PSTR("The `cowpi_setup` function will be called with either `SPI` or `I2C` so that\n\r")));
    printf("%s", strcpy_P(s, PSTR("\tthe CowPi library knows where your slider switches are.\n\r")));
    printf("%s", strcpy_P(s, PSTR("\tYour instructor should have told you which to use.\n\r")));

    cowpi_setup(SPI);
//    cowpi_setup(I2C);

    printf("%s", strcpy_P(s, PSTR("The simple I/O test will print the status of the keypad and of each\n\r")));
    printf("%s", strcpy_P(s, PSTR("\tbutton, switch, and LED every half-second.\n\r")));
    printf("%s", strcpy_P(s, PSTR("Press the Enter key on your host computer's keyboard to start.\n\r")));
    scanf("%c", s);
}

void loop() {
    bool internal_led, external_led;
    char c;
    printf("\n");
    printf("Keypad:       %c       Column pins:  %d%d%d%d    Keypad NAND: %d\n\r", (c = cowpi_get_keypress()) ? c : ' ',
           digitalRead(14), digitalRead(15), digitalRead(16), digitalRead(17), digitalRead(3));
    printf("Left switch:  %s   Right switch: %s\n\r",
           cowpi_left_switch_in_left_position() ? "LEFT " : "RIGHT",
           cowpi_right_switch_in_left_position() ? "LEFT " : "RIGHT");
    printf("Left button:  %s   Right button: %s",
           cowpi_left_button_is_pressed() ? "DOWN " : "UP   ",
           cowpi_right_button_is_pressed() ? "DOWN " : "UP   ");
#if defined ARDUINO_AVR_UNO || defined ARDUINO_AVR_NANO || defined ARDUINO_AVR_MEGA2560
    printf("   Button NAND: %d", digitalRead(2));
#endif
    printf("\n\r");
    if (cowpi_left_button_is_pressed() && cowpi_left_switch_in_right_position()) {
        internal_led = true;
        cowpi_illuminate_internal_led();
    } else {
        internal_led = false;
        cowpi_deluminate_internal_led();
    }
    if (cowpi_right_button_is_pressed() && cowpi_right_switch_in_right_position()) {
        external_led = true;
        cowpi_illuminate_external_led();
    } else {
        external_led = false;
        cowpi_deluminate_external_led();
    }
    printf("Internal LED: %s     External LED: %s\n\r", internal_led ? "ON " : "OFF", external_led ? "ON " : "OFF");
    delay(500);
}
