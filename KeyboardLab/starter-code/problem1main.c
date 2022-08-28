/*             *
 * CODE DRIVER *
 *             */

/*
 * KeyboardLab (c) 2021-22 Christopher A. Bohn
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *generate_email(char *destination, size_t destination_size);

int main() {
    const char desired_message[] =  // I'm looking forward to the C23 `#embed` feature
            "TO\tArchie\n"
            "RE\tI Need a Working Keyboard\n"
            "\n"
            "Please order a new keyboard for me. This one is broken.\n";
    const int buffer_length = 3 * sizeof(desired_message);  // this works because desired_message is constant
    char *buffer = calloc(buffer_length,
                          sizeof(char)); // pre-fills buffer with `\0`s so students don't need to worry about that
    buffer = generate_email(buffer, buffer_length);
    char *terminator = strchr(buffer, '\0');                // strchr will eventually find a NUL character
    if (terminator - buffer >= buffer_length) {             // does the NUL appear within the buffer?
        printf("Your string is much too long!");
        return 1;
    }
    printf("%s\n", buffer);     // The extra LF is there just in case students forget the last LF
    if (!strcmp(desired_message, buffer)) {
        printf("Your string matches the desired message.\n");
        printf("Be sure to run ./constraint-check.sh\n");
    } else {
        printf("Your string (%ld characters) differs from the desired message (%ld characters):\n",
               strlen(buffer), strlen(desired_message));
        printf("%s", desired_message);
    }

    return 0;
}
