/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file floatlab.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Driver code for FloatLab.
 *
 ******************************************************************************/

/*
 * FloatLab (c) 2019-23 Christopher A. Bohn
 *
 * Assignment and starter code licensed under the Apache License,
 * Version 2.0 (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include "fpu.h"
#include "unnormal.h"

union float_converter {
    uint32_t bit_vector;
    float reference_value;
};

bool read_evaluate_print();
char *parse_operand(const char *buffer, union float_converter *operand);
char *parse_operator(const char *buffer, char *operator);

int main() {
    bool running = true;
    while (running) {
        running = read_evaluate_print();
        printf("\n");
    }
    printf("Goodbye\n");
    return 0;
}

char *parse_operand(const char *buffer, union float_converter *operand) {
    char *end_pointer[1];
    while (*buffer == ' ' || *buffer == '\t') {
        buffer++;
    }
    if (!strncmp(buffer, "0x", 2)) {
        (*operand).bit_vector = strtol(buffer, end_pointer, 16);
    } else {
        (*operand).reference_value = strtof(buffer, end_pointer);
    }
    return end_pointer[0];
}

char *parse_operator(const char *buffer, char *operator) {
    const char *end_pointer = buffer;
    while (*end_pointer == ' ' || *end_pointer == '\t') {
        end_pointer++;
    }
    *operator = *end_pointer;
    if (*operator == '\n') {
        *operator = '\0';
    }
    return (char *) (++end_pointer);
}

bool read_evaluate_print() {
    char input_buffer[72];
    char output_buffer[72];
    union float_converter operand1, operand2, result;
    char operator;
    printf("Enter a value, a two-operand arithmetic expression,\n"
//           "    \"decode <value> <change exponent amount>\",\n"
//           "    \"recode <value> <change exponent amount>\",\n"
        // for now, we'll hide the option to specify the exponent shift amount, but leave the code to look for it
        // if no exponent shift amount is specified, `strtol` will produce 0, which is exactly what we want.
           "    \"decode <value>\", \"recode <value>\",\n"
           "    or \"quit\": ");
    fgets(input_buffer, 72, stdin);
    for (char *s = input_buffer; (*s = (char) tolower(*s)); s++) {}    // string to lowercase, to simplify comparisons
    if (!strncmp(input_buffer, "quit", 4)) {
        return false;
    } else if (!strncmp(input_buffer, "decode", 6)) {
        char *next = parse_operand(input_buffer + 6, &operand1);
        int16_t amount = (int16_t) strtol(next, NULL, 10);
        if (amount > 0) {
            printf("%s\n", unnormal_to_string(output_buffer, shift_right(decode(operand1.bit_vector), amount)));
        } else {
            amount = (int16_t) (-amount);
            printf("%s\n", unnormal_to_string(output_buffer, shift_left(decode(operand1.bit_vector), amount)));
        }
        return true;
    } else if (!strncmp(input_buffer, "recode", 6)) {
        char *next = parse_operand(input_buffer + 6, &operand1);
        int16_t amount = (int16_t) strtol(next, NULL, 10);
        printf("expected: %.10f_{10}\t", operand1.reference_value);
        printf("%s\n", ieee754_to_string(output_buffer, operand1.bit_vector));
        unnormal_t number;
        if (amount > 0) {
            number = shift_right(decode(operand1.bit_vector), amount);
        } else {
            amount = (int16_t) (-amount);
            number = shift_left(decode(operand1.bit_vector), amount);
        }
        ieee754_t recoded_number = encode(number);
        result.bit_vector = recoded_number;
        printf("actual:   %.10f_{10}\t", result.reference_value);
        printf("%s\n", ieee754_to_string(output_buffer, recoded_number));
        return true;
    } else {
        char *next = parse_operand(input_buffer, &operand1);
        printf("%s\n", ieee754_to_string(output_buffer, operand1.bit_vector));
        if (*next != '\0' && *next != '\n') {
            next = parse_operator(next, &operator);
            printf("%c\n", operator);
            parse_operand(next, &operand2);
            printf("%s\n", ieee754_to_string(output_buffer, operand2.bit_vector));
            switch (operator) {
                case '+':
                    result.reference_value = operand1.reference_value + operand2.reference_value;
                    printf("expected: %.10f_{10}\t", result.reference_value);
                    printf("%s\n", ieee754_to_string(output_buffer, result.bit_vector));
                    result.bit_vector = add(operand1.bit_vector, operand2.bit_vector);
                    break;
                case '-':
                    result.reference_value = operand1.reference_value - operand2.reference_value;
                    printf("expected: %.10f_{10}\t", result.reference_value);
                    printf("%s\n", ieee754_to_string(output_buffer, result.bit_vector));
                    result.bit_vector = subtract(operand1.bit_vector, operand2.bit_vector);
                    break;
                case '*':
                    result.reference_value = operand1.reference_value * operand2.reference_value;
                    printf("expected: %.10f_{10}\t", result.reference_value);
                    printf("%s\n", ieee754_to_string(output_buffer, result.bit_vector));
                    result.bit_vector = multiply(operand1.bit_vector, operand2.bit_vector);
                    break;
                case '/':
                    result.reference_value = operand1.reference_value / operand2.reference_value;
                    printf("expected: %.10f_{10}\t", result.reference_value);
                    printf("%s\n", ieee754_to_string(output_buffer, result.bit_vector));
                    result.bit_vector = divide(operand1.bit_vector, operand2.bit_vector);
                    break;
                default:
                    printf("Unknown operator: %c\n", operator);
            }
            printf("actual:   %.10f_{10}\t", result.reference_value);
            printf("%s\n", ieee754_to_string(output_buffer, result.bit_vector));
        }
        return true;
    }
}

char *bits_to_string(char *destination, uint64_t bits, int start_bit,
                     int end_bit, enum bit_divider_direction bit_dividers) {
    assert(start_bit < 64 && start_bit >= 0 && end_bit < 64 && end_bit >= 0);
    if (start_bit < end_bit) {
        int placeholder = start_bit;
        start_bit = end_bit;
        end_bit = placeholder;
    }
    uint64_t mask = (uint64_t) 1 << start_bit;
    char *destination_bit = destination;
    int place_counter = (bit_dividers == FROM_LEFT) ? 0 : (end_bit - start_bit - 1) % 4;
    for (int bit = start_bit; bit >= end_bit; bit--) {
        *destination_bit++ = (bits & mask) ? '1' : '0';
        mask = mask >> 1;
        place_counter = (place_counter + 1) % 4;
        if (!place_counter && (bit_dividers != NONE)) {
            *destination_bit++ = ',';
        }
    }
    if (*(destination_bit - 1) == ',') {
        destination_bit--;
    }
    *destination_bit = '\0';
    return destination;
}

