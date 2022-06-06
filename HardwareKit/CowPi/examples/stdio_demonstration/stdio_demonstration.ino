#include "cowpi.h"

void setup() {
    cowpi_stdio_setup(9600);
    cowpi_setup(0);

    printf("Unlike normal Arduino-based systems, CowPi lets you use `printf` & `scanf`,\n\r");
    printf("\tbut only if you call `cowpi_stdio_setup` first.\n\r");

    Serial.println(F("If you plan to use Arduino's `F()` macro to save RAM, use `Serial.print`"));
    Serial.println(F("\tand/or `Serial.println`."));

    char s[83];
    printf("%s", strcpy_P(s, PSTR("But using the avr-libc `PSTR()` macro and the pointer returned by the\n\r")));
    printf("%s", strcpy_P(s, PSTR("\t`strcpy_P` function is a way to put string constants in flash memory\n\r")));
    printf("%s", strcpy_P(s, PSTR("\tand use them with `printf`.\n\r")));

    printf("%s", strcpy_P(s, PSTR("Floating point conversion won't work with `printf`, but you really should think\n\r")));
    printf("%s", strcpy_P(s, PSTR("\ttwice about using floats on a microcontroller in the first place.\n\n\r")));
}

void loop() {
    char s[83];
    char c;
    int i;
    printf("%s", strcpy_P(s, PSTR("Enter an integer from the host computer's keyboard: ")));
    scanf("%d", &i);
    scanf("%c", &c);    // consume the linefeed character
    printf("\n\rYou entered: %d\n\r", i);
    printf("%s", strcpy_P(s, PSTR("Enter a character from the host computer's keyboard: ")));
    scanf("%c", &c);
    printf("\n\rYou entered: %c\n\r", c);
    printf("%s", strcpy_P(s, PSTR("Enter a string from the host computer's keyboard: ")));
    scanf("%80s", s);
    printf("\n\rYou entered: %s\n\r", s);
}
