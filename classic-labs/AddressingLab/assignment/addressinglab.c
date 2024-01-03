/*                *
 * CODE GENERATOR *
 *                */

/*
 * AddressingLab (c) 2021 Christopher A. Bohn
 */

/******************************************************************************
 * This code exists to generate the assembly code that students will edit.
 * After compiling down to assembly, remove the instructions' sources and
 * destinations that students should complete.
 ******************************************************************************/

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "addressinglab.h"


char *caesar_cipher(char *destination, const char *text, int key) {
    char *target = destination;
    int reduced_character;
    while (*text) {
        if ('A' <= *text && *text <= 'Z') {
            reduced_character = *text - 'A';
            reduced_character = (reduced_character + key + 26) % 26;
            *target = (char)(reduced_character + 'A');
        } else {
            *target = *text;
        }
        target++;
        text++;
    }
    *target = '\0';
    return destination;
}

char *sentence_to_uppercase(char *destination, const char *sentence) {
    unsigned long length = strlen(sentence);
    for (int i = 0; i < length; i++) {
        destination[i] = (char)toupper(sentence[i]);
    }
    return destination;
}

bool validate_cipher(struct cipher_package *package) {
    bool is_valid = (strlen(package->plaintext) == package->sentence_length);
    is_valid = is_valid && (strlen(package->ciphertext) == package->sentence_length);
    char *deciphered_text = malloc(MAXIMUM_INPUT_LENGTH);
    deciphered_text = caesar_cipher(deciphered_text, package->ciphertext, -(package->key));
    is_valid = is_valid && !strncmp(package->plaintext, deciphered_text, package->sentence_length);
    return is_valid;
}