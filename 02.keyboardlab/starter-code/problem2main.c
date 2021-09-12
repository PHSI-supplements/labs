/*             *
 * CODE DRIVER *
 *             */

/*
 * KeyboardLab (c) 2021 Christopher A. Bohn
 */

#include <stdio.h>
#include <ctype.h>

char is_digit(char character);
char to_lowercase(char character);

int main() {
    char c = (char)0xFF;
    while (c != '\t') {
        if (c != '\n') printf("Enter character (enter tab to end): ");
        c = (char)getchar();
        if (c != '\n') {
            printf("isdigit('%c') =  %d\t\ttolower('%c') =      %c\n", c, isdigit(c), c, tolower(c));
            printf("is_digit('%c') = %d\t\tto_lowercase('%c') = %c\n", c, is_digit(c), c, to_lowercase(c));
        }
    }
    return 0;
}
