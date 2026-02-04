#include <string.h>

char *caesar_cipher(char *restrict destination, char const *restrict text, int key) {
    char *target = destination;
    int reduced_character;
//    while (*text) {
    if (*text == 0) goto func1_done;
func1_loop:
    reduced_character = *text - 'A';
//    if (reduced_character <= 'Z' - 'A') {
    if (reduced_character > 25) goto func1_else_target;
    reduced_character = (reduced_character + key + 26) % 26;
    *target = (char) (reduced_character + 'A');
    goto func1_endif;
//    } else {
func1_else_target:
        *target = *text;
//    }
func1_endif:
    target++;
    text++;
    if (*text != 0) goto func1_loop;
//    }
func1_done:
    *target = '\0';
    return destination;
}

constexpr int upper[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
        ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
        '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
        '`', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '{', '|', '}', '~', 0x7F,
};

char *sentence_to_uppercase(char *restrict destination, char const *restrict sentence) {
    size_t length = strlen(sentence);
    if (length == 0) goto func2_done;
//    for (size_t i = 0; i < length; i++) {
    size_t i = 0;
func2_loop:
//    destination[i] = (char) toupper(sentence[i]);
    destination[i] = (char) upper[(size_t) sentence[i]];
//    }
    i++;
    if (i < length) goto func2_loop;
func2_done:
    destination[length] = '\0';
    return destination;
}

constexpr unsigned int MAXIMUM_INPUT_LENGTH = 256;

struct cipher_package {
    char *plaintext;
    char *ciphertext;
    int sentence_length;
    int key;
};

bool validate_cipher(struct cipher_package *package) {
    bool is_valid = (strlen(package->plaintext) == (size_t) package->sentence_length);
    is_valid = is_valid && (strlen(package->ciphertext) == (size_t) package->sentence_length);
    char deciphered_text[MAXIMUM_INPUT_LENGTH];
    caesar_cipher(deciphered_text, package->ciphertext, -(package->key));
    is_valid = is_valid && !strncmp(package->plaintext, deciphered_text, package->sentence_length);
    return is_valid;
}
