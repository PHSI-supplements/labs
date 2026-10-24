/*
 * hex2raw.c (c) 2021-26 Christopher A. Bohn
 */

#include <ctype.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


constexpr int INPUT_BUFFER_SIZE = 256;

enum {
    NO_ERROR = 0,
    INVALID_ARGUMENT,
    INVALID_ENDIAN,
    BYTE_COUNT_MISMATCH,
    TOO_LONG_WORD,
    TOO_LONG_INPUT,
    INVALID_HEXDIGIT,
    UNTERMINATED_BLOCK_COMMENT,
} error_condition;

int byte_order = __BYTE_ORDER__;


struct byte_buffer {
    size_t length;
    size_t capacity;
    uint8_t bytes[];
};


bool preprocess_line(char* line, bool block_comment_is_open) {
    char const *reader = line;
    char *writer = line;
    bool reached_inline_comment = false;
    while (*reader && !reached_inline_comment) {
        // block comment
        if (block_comment_is_open && reader[0] == '*' && reader[1] == '/') {
            block_comment_is_open = false;
            reader += 2;
        } else if (block_comment_is_open) {
            reader += 1;
        } else if (reader[0] == '/' && reader[1] == '*') {
            block_comment_is_open = true;
            *writer++ = ' ';
            reader += 2;
        } else if ((reader[0] == '/' && reader[1] == '/') || reader[0] == '#' || reader[0] == ';') {
            reached_inline_comment = true;
        // digit separator
        } else if (reader[0] == '\'' || reader[0] == '_') {
            reader += 1;
        // radix prefix
        } else if (reader[0] == '0' &&
                   (reader[1] == 'x' || reader[1] == 'X') &&
                   (reader == line || isspace(reader[-1]))) {
            reader += 2;
        // radix suffix
        } else if ((reader[0] == 'h' || reader[0] == 'H') && (reader[1] == '\0' || isspace(reader[1]))) {
            reader += 1;
        // everything else
        } else {
            *writer++ = *reader++;
        }
    }
    *writer = '\0';
    return block_comment_is_open;
}


struct byte_buffer *process_token(char const *token, struct byte_buffer *byte_buffer, int line_number) {
    if (!token || *token == '\0') {
        return byte_buffer;
    }
    size_t size = strlen(token) / 2;
    if (size < sizeof(unsigned char)) {
        size = CHAR_BIT;
        fprintf(stderr, "[WARNING] %s on line %d will be promoted to %zu byte.\n", token, line_number, size);
    } else if (size > sizeof(unsigned char) && size < sizeof(unsigned short)) {
        size = sizeof(unsigned short);
        fprintf(stderr, "[WARNING] %s on line %d will be promoted to %zu bytes.\n", token, line_number, size);
    } else if (size > sizeof(unsigned short) && size < sizeof(unsigned int)) {
        size = sizeof(unsigned int);
        fprintf(stderr, "[WARNING] %s on line %d will be promoted to %zu bytes.\n", token, line_number, size);
    } else if (size > sizeof(unsigned int) && size < sizeof(unsigned long)) {
        size = sizeof(unsigned long);
        fprintf(stderr, "[WARNING] %s on line %d will be promoted to %zu bytes.\n", token, line_number, size);
    } else if (size > sizeof(unsigned long)) {
        size = sizeof(unsigned long);
        fprintf(stderr,
            "[ERROR]   %s on line %d exceeds maximum allowable word size: %zu bytes.\n",
            token, line_number, size);
        error_condition = TOO_LONG_WORD;
    } else { /* just the right size -- no message or correction is needed */ }
    char const *hex_digit = token;
    while (*hex_digit) {
        if (!isxdigit(*hex_digit)) {
            fprintf(stderr,
                "[ERROR]   '%c' in token \"%s\" on line %d is not a valid hexdigit.\n",
                *hex_digit, token, line_number);
            error_condition = INVALID_HEXDIGIT;
        }
        hex_digit++;
    }
    unsigned long bytes = strtoul(token, nullptr, 16);
    unsigned long byte_mask = 0xFF;
    int byte_shift = 0;
    if (byte_order == __ORDER_BIG_ENDIAN__) {
        bytes <<= 8 * ((sizeof(unsigned long)) - size);
        byte_shift = 8 * ((sizeof(unsigned long)) - 1);
        byte_mask <<= byte_shift;
    }
    while (size && !error_condition) {
        uint8_t byte = (bytes & byte_mask) >> byte_shift;
        if (byte_order == __ORDER_LITTLE_ENDIAN__) {
            bytes >>= 8;
        } else {
            bytes <<= 8;
        }
        struct byte_buffer *p;
        if (byte_buffer->length < byte_buffer->capacity) {
            byte_buffer->bytes[byte_buffer->length] = byte;
            byte_buffer->length++;
        } else if ((p = realloc(byte_buffer, byte_buffer->capacity + 128))) {
            byte_buffer = p;
            byte_buffer->capacity += 128;
            byte_buffer->bytes[byte_buffer->length] = byte;
            byte_buffer->length++;
        } else {
            fprintf(stderr, "[ERROR]   The input is too long for allocatable memory.\n");
            error_condition = TOO_LONG_INPUT;
        }
        size--;
    }
    return byte_buffer;
}


void hex2raw(void) {
    char line[INPUT_BUFFER_SIZE];
    struct byte_buffer *byte_buffer = malloc(sizeof(struct byte_buffer) + 128);
    byte_buffer->length = 0;
    byte_buffer->capacity = 128;
    int line_number = 0;
    bool block_comment_is_open = false;
    while (!error_condition && fgets(line, INPUT_BUFFER_SIZE, stdin)) {
        line_number++;
        size_t end_of_line = strlen(line) - 1;
        if (line[end_of_line] != '\n') {
            fprintf(stderr, "[WARNING] Line %d truncated to %zu characters\n", line_number, end_of_line);
            int c;
            while ((c = fgetc(stdin)) != '\n' && c != EOF) {}
        }
        while (isspace(line[end_of_line])) {
            // shed the '\n' and possibly '\r'
            line[end_of_line] = '\0';
            end_of_line--;
        }
        block_comment_is_open = preprocess_line(line, block_comment_is_open);
        char *token;
        if (strpbrk(line, ":")) {
            token = strtok(line, ":");
            unsigned long displacement = strtoul(token, nullptr, 16);
            if (displacement != byte_buffer->length) {
                fprintf(stderr,
                        "[ERROR]   Displacement %#zx reported on line %d does not match cumulative bytes %zu (%#zx) on lines %d-%d.\n",
                        displacement, line_number, byte_buffer->length, byte_buffer->length, 1, line_number - 1);
                error_condition = BYTE_COUNT_MISMATCH;
            }
            token = strtok(nullptr, " \t");
        } else {
            token = strtok(line, " \t");
        }
        while (token) {
            byte_buffer = process_token(token, byte_buffer, line_number);
            token = strtok(nullptr, " \t");
        }
    }
    if (block_comment_is_open) {
        fprintf(stderr, "[ERROR]   The input ends with an unterminated block comment.\n");
        error_condition = UNTERMINATED_BLOCK_COMMENT;
    }
    if (!error_condition) {
        for (size_t i = 0; i < byte_buffer->length; i++) {
            printf("%c", byte_buffer->bytes[i]);
        }
    }
}


int main(int argc, char const *argv[]) {
    error_condition = NO_ERROR;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--little-endian")) {
            byte_order = __ORDER_LITTLE_ENDIAN__;
        } else if (!strcmp(argv[i], "--big-endian")) {
            byte_order = __ORDER_BIG_ENDIAN__;
        } else {
            fprintf(stderr, "[ERROR]   Unrecognized argument: %s\n", argv[i]);
            error_condition = INVALID_ARGUMENT;
        }
    }
    if (error_condition) {
        fprintf(stderr, "Usage: %s [--little-endian | --big-endian]\n", argv[0]);
    }
    if (byte_order == __ORDER_PDP_ENDIAN__) {
        fprintf(stderr, "[ERROR]   Middle endian not supported.\n");
        error_condition = INVALID_ENDIAN;
    } else if (byte_order != __ORDER_LITTLE_ENDIAN__ &&
               byte_order != __ORDER_BIG_ENDIAN__) {
        fprintf(stderr, "[ERROR]   Unrecognized byte order.\n");
        error_condition = INVALID_ENDIAN;
    } else {
        hex2raw();
    }
    return error_condition;
}
