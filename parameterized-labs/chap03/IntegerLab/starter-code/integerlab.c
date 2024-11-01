/*                       *
 * DO NOT EDIT THIS FILE *
 *                       */

/**************************************************************************//**
 *
 * @file integerlab.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Driver code for IntegerLab.
 *
 ******************************************************************************/

/*
 * IntegerLab (c) 2018-23 Christopher A. Bohn
 *
 * Starter code licensed under the Apache License, Version 2.0
 * (http://www.apache.org/licenses/LICENSE-2.0).
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "alu.h"
#include "authoritative_results.h"
#include "profiler.h"

bool read_evaluate_print() __attribute__ ((no_instrument_function));
char *parse_operand(const char *buffer, uint32_t *operand) __attribute__ ((no_instrument_function));
char *parse_operator(const char *buffer, char *operator) __attribute__ ((no_instrument_function));
void evaluate_print_one_bit_adder(const char *input_buffer) __attribute__ ((no_instrument_function));
void evaluate_print_thirty_two_bit_adder(const char *input_buffer) __attribute__ ((no_instrument_function));
void evaluate_print_power_of_two_multiplier(const char *input_buffer) __attribute__ ((no_instrument_function));
void evaluate_print_arithmetic(uint16_t operand1, char operator, uint16_t operand2) __attribute__ ((no_instrument_function));

int main() {
    bool running = true;
    while (running) {
        running = read_evaluate_print();
        printf("\n");
    }
    printf("Goodbye\n");
    return 0;
}

char *parse_operand(const char *buffer, uint32_t *operand) {
    char *end_pointer[1];
    while (*buffer == ' ' || *buffer == '\t') {
        buffer++;
    }
    *operand = strtol(buffer, end_pointer, (strncmp(buffer, "0x", 2) ? 10 : 16));
    return end_pointer[0];
}

char *parse_operator(const char *buffer, char operator[3]) {
    const char *end_pointer = buffer;
    while (*end_pointer == ' ' || *end_pointer == '\t') {
        end_pointer++;
    }
    operator[0] = *end_pointer++;
    if (*end_pointer == ' ' || *end_pointer == '\t' || isdigit(*end_pointer)) {
        operator[1] = '\0';
    } else {
        operator[1] = *end_pointer++;
        operator[2] = '\0';
    }
    return (char *) end_pointer;
}

void evaluate_print_one_bit_adder(const char *input_buffer) {
    /* !!! STUDENTS ARE NOT ALLOWED TO USE A LOOKUP TABLE FOR THEIR ONE-BIT ADDER !!! */
    bool sums[2][2][2] = {{{false, true},  {true,  false}},
                          {{true,  false}, {false, true}}};
    bool carries[2][2][2] = {{{false, false}, {false, true}},
                             {{false, true},  {true,  true}}};
    /* !!! STUDENTS ARE NOT ALLOWED TO USE A LOOKUP TABLE FOR THEIR ONE-BIT ADDER !!! */
    one_bit_adder_t input;
    uint32_t operand;
    char *next = parse_operand(input_buffer + 5, &operand);
    input.a = operand & 0x1;
    next = parse_operand(next, &operand);
    input.b = operand & 0x1;
    parse_operand(next, &operand);
    input.c_in = operand & 0x1;
    one_bit_adder_t result = one_bit_full_addition(input);
    printf("expected: %d + %d + %d = %d carry %d\n", input.a, input.b, input.c_in,
           sums[input.a][input.b][input.c_in], carries[input.a][input.b][input.c_in]);
    printf("actual:   %d + %d + %d = %d carry %d\n", result.a, result.b, result.c_in, result.sum, result.c_out);
}

void evaluate_print_thirty_two_bit_adder(const char *input_buffer) {
    reset_call_counts();
    uint32_t operand1, operand2;
    int carry_in;
    sscanf(input_buffer + 6, "%x %x %d", &operand1, &operand2, &carry_in); // NOLINT(cert-err34-c)
    uint32_t expected_result = operand1 + operand2 + (carry_in & 0x1);
    uint32_t actual_result = ripple_carry_addition(operand1, operand2, (uint8_t) carry_in);
    printf("expected: 0x%08X + 0x%08X + %d = 0x%08X\n", operand1, operand2, (carry_in & 0x1), expected_result);
    printf("actual:   0x%08X + 0x%08X + %d = 0x%08X\n", operand1, operand2, (carry_in & 0x1), actual_result);
    printf("\t\tNumber of calls to one_bit_full_addition:    %d\n", get_call_counts(one_bit_full_addition));
}

void evaluate_print_power_of_two_multiplier(const char *input_buffer) {
    uint16_t operand1, operand2;
    sscanf(input_buffer + 5, "%hx %hx", &operand1, &operand2); // NOLINT(*-err34-c)
    uint32_t expected_result = (int32_t) operand1 * (int32_t) operand2;
    uint32_t actual_result = multiply_by_power_of_two(operand1, operand2);
    if ((operand2 == 0) || (__builtin_popcount(operand2) == 1)) {       // when we migrate to C23, we'll change this to stdc_popcount()
        printf("expected: 0x%04X * 0x%04X = 0x%08X\n", operand1, operand2, expected_result);
    } else {
        printf("[WARNING] 0x%04X is not a power of two!\n", operand2);
    }
    printf("actual:   0x%04X * 0x%04X = 0x%08X\n", operand1, operand2, actual_result);
}

void evaluate_print_arithmetic(uint16_t operand1, char operator, uint16_t operand2) {
    reset_call_counts();
    alu_result_t actual_result;
    struct authoritative_result *expected_result = malloc(sizeof(struct authoritative_result));
    switch (operator) {
        case '+':
        case '-':
            if (operator == '+') {
                evaluate_addition(operand1, operand2, expected_result);
                actual_result = add(operand1, operand2);
            } else {
                evaluate_subtraction(operand1, operand2, expected_result);
                actual_result = subtract(operand1, operand2);
            }
            printf("UNSIGNED %s\n", operator == '+' ? "ADDITION" : "SUBTRACTION");
            printf("\texpected result (hexadecimal): 0x%04X %c 0x%04X = 0x%04X\n",
                   operand1, operator, operand2, expected_result->result);
            printf("\texpected result (unsigned):    %u %c %u = %u\toverflow: %s\n",
                   operand1, operator, operand2, expected_result->result,
                   expected_result->c_flag ? "true" : "false");
            printf("\tactual result (hexadecimal):   0x%04X %c 0x%04X = 0x%04X\n",
                   operand1, operator, operand2, actual_result.result);
            printf("\tactual result (unsigned):      %u %c %u = %u\toverflow: %s\n",
                   operand1, operator, operand2, actual_result.result,
                   actual_result.unsigned_overflow ? "true" : "false");
            printf("SIGNED %s\n", operator == '+' ? "ADDITION" : "SUBTRACTION");
            printf("\texpected result (hexadecimal): 0x%04X %c 0x%04X = 0x%04X\n",
                   operand1, operator, operand2, expected_result->result);
            printf("\texpected result (signed):      %d %c %d = %d\toverflow: %s\n",
                   (int16_t) operand1, operator, (int16_t) operand2, (int16_t) expected_result->result,
                   expected_result->o_flag ? "true" : "false");
            printf("\tactual result (hexadecimal):   0x%04X %c 0x%04X = 0x%04X\n",
                   operand1, operator, operand2, actual_result.result);
            printf("\tactual result (signed):        %d %c %d = %d\toverflow: %s\n",
                   (int16_t) operand1, operator, (int16_t) operand2, (int16_t) actual_result.result,
                   actual_result.signed_overflow ? "true" : "false");
            printf("\t\tNumber of calls to ripple_carry_addition:    %d\n", get_call_counts(ripple_carry_addition));
            break;
        case '*':
            printf("UNSIGNED MULTIPLICATION\n");
            evaluate_unsigned_multiplication(operand1, operand2, expected_result);
            actual_result = unsigned_multiply(operand1, operand2);
            printf("\texpected result (hexadecimal): 0x%04X * 0x%04X = 0x%04X'%04X\n",
                   operand1, operand2, expected_result->supplemental_result, expected_result->result);
            printf("\texpected result (unsigned):    %u * %u = %u (%u)\n", operand1, operand2, expected_result->result,
                   ((uint32_t) expected_result->supplemental_result << 16) | expected_result->result);
            printf("\tactual result (hexadecimal):   0x%04X * 0x%04X = 0x%04X'%04X\n",
                   operand1, operand2, actual_result.supplemental_result, actual_result.result);
            printf("\tactual result (unsigned):      %u * %u = %u (%u)\n", operand1, operand2, actual_result.result,
                   ((uint32_t) actual_result.supplemental_result << 16) | actual_result.result);
            printf("SIGNED MULTIPLICATION\n");
            evaluate_signed_multiplication(operand1, operand2, expected_result);
            actual_result = signed_multiply(operand1, operand2);
            printf("\texpected result (hexadecimal): 0x%04X * 0x%04X = 0x%04X'%04X\n",
                   operand1, operand2, expected_result->supplemental_result, expected_result->result);
            printf("\texpected result (signed):      %d * %d = %d (%d)\n",
                   (int16_t) operand1, (int16_t) operand2, (int16_t) expected_result->result,
                   (int32_t) (((uint32_t) expected_result->supplemental_result << 16) | expected_result->result));
            printf("\tactual result (hexadecimal):   0x%04X * 0x%04X = 0x%04X'%04X\n",
                   operand1, operand2, actual_result.supplemental_result, actual_result.result);
            printf("\tactual result (signed):        %d * %d = %d (%d)\n",
                   (int16_t) operand1, (int16_t) operand2, (int16_t) actual_result.result,
                   (int32_t) (((uint32_t) actual_result.supplemental_result << 16) | actual_result.result));
            printf("\t\tNumber of calls to ripple_carry_addition:    %d\n", get_call_counts(ripple_carry_addition));
            printf("\t\tNumber of calls to multiply_by_power_of_two: %d\n", get_call_counts(multiply_by_power_of_two));
            break;
        case '/':
        case '%':
            if (operand2 > 0 && operand2 != 1 << lg(operand2)) {
                printf("[NOTE] 0x%04X is not a power-of-two; the assignment only requires division by powers-of-two.\n",
                       operand2);
            }
            printf("UNSIGNED DIVISION\n");
            reset_call_counts();
            if (operand2 == 0) {
                printf("expected result: divide-by-zero\n");
            } else {
                evaluate_unsigned_division(operand1, operand2, expected_result);
                printf("\texpected result (hexadecimal): 0x%04X / 0x%04X = 0x%04X    0x%04X %% 0x%04X = 0x%04X\n",
                       operand1, operand2, expected_result->result,
                       operand1, operand2, expected_result->supplemental_result);
                printf("\texpected result (unsigned):    %u / %u = %u    %u %% %u = %u\n",
                       operand1, operand2, expected_result->result,
                       operand1, operand2, expected_result->supplemental_result);
            }
            actual_result = unsigned_divide(operand1, operand2);
            if (actual_result.divide_by_zero) {
                printf("actual result:   divide-by-zero\n");
            } else {
                printf("\tactual result (hexadecimal):   0x%04X / 0x%04X = 0x%04X    0x%04X %% 0x%04X = 0x%04X\n",
                       operand1, operand2, actual_result.result,
                       operand1, operand2, actual_result.supplemental_result);
                printf("\tactual result (unsigned):      %u / %u = %u    %u %% %u = %u\n",
                       operand1, operand2, actual_result.result,
                       operand1, operand2, actual_result.supplemental_result);
            }
            printf("\t\tNumber of calls to ripple_carry_addition:    %d\n", get_call_counts(ripple_carry_addition));
            printf("\t\tNumber of calls to multiply_by_power_of_two: %d\n", get_call_counts(multiply_by_power_of_two));
            printf("SIGNED DIVISION\n");
            reset_call_counts();
            if (operand2 == 0) {
                printf("expected result: divide-by-zero\n");
            } else {
                evaluate_signed_division(operand1, operand2, expected_result);
                printf("\texpected result (hexadecimal): 0x%04X / 0x%04X = 0x%04X    0x%04X %% 0x%04X = 0x%04X\n",
                       operand1, operand2, expected_result->result,
                       operand1, operand2, expected_result->supplemental_result);
                printf("\texpected result (signed):      %d / %d = %d    %d %% %d = %d\n",
                       (int16_t) operand1, (int16_t) operand2, (int16_t) expected_result->result,
                       (int16_t) operand1, (int16_t) operand2, (int16_t) expected_result->supplemental_result);
            }
            actual_result = signed_divide(operand1, operand2);
            if (actual_result.divide_by_zero) {
                printf("actual result:   divide-by-zero\n");
            } else {
                printf("\tactual result (hexadecimal):   0x%04X / 0x%04X = 0x%04X    0x%04X %% 0x%04X = 0x%04X\n",
                       operand1, operand2, actual_result.result,
                       operand1, operand2, actual_result.supplemental_result);
                printf("\tactual result (signed):        %d / %d = %d    %d %% %d = %d\n",
                       (int16_t) operand1, (int16_t) operand2, (int16_t) actual_result.result,
                       (int16_t) operand1, (int16_t) operand2, (int16_t) actual_result.supplemental_result);
            }
            printf("\t\tNumber of calls to ripple_carry_addition:    %d\n", get_call_counts(ripple_carry_addition));
            printf("\t\tNumber of calls to multiply_by_power_of_two: %d\n", get_call_counts(multiply_by_power_of_two));
            break;
        default:
            printf("Unknown operator: %c\n", operator);
    }
}

bool read_evaluate_print() {
    char input_buffer[72];
    uint32_t operand1, operand2;
    char operator[3];
    bool keep_going = true;
    printf("Enter a one- or two-operand logical expression, \n"
           "    a two-operand comparison expression, a two-operand arithmetic expression,\n"
           "    \"lg <value>\" or \"exponentiate <value>\" to test your powers-of-two code,\n"
           "    \"is_negative <value>\" to determine if 2's complement value is negative,\n"
           "    \"add1 <binary_value1> <binary_value2> <carry_in>\" for 1-bit full adder,\n"
           "    \"add32 <hex_value1> <hex_value2> <carry_in>\" for 32-bit ripple-carry adder,\n"
           "    \"mul2 <hex_value> <hex_power_of_two>\" for power-of-two multiplier,\n"
           "    or \"quit\": ");
    if (!fgets(input_buffer, 72, stdin)) {
        printf("Failed to read input.\n");
        input_buffer[0] = '\0';
    };
    // string to lowercase, to simplify a couple of the comparisons
    for (char *s = input_buffer; (*s = (char) tolower(*s)); s++) {}
    if (!strncmp(input_buffer, "quit", 4)) {
        keep_going = false;
    } else if (!strncmp(input_buffer, "lg", 2)) {
        parse_operand(input_buffer + 2, &operand1);
        printf("expected: log2 %u == log2 0x%08X == %d\n", operand1, operand1, (int) log2(operand1));
        printf("actual:   log2 %u == log2 0x%08X == %d\n", operand1, operand1, lg(operand1));
    } else if (!strncmp(input_buffer, "exponentiate", 12)) {
        parse_operand(input_buffer + 12, &operand1);
        printf("expected: 2**%d == 0x%08X == %u\n",
               operand1, (unsigned int) pow(2, operand1), (unsigned int) pow(2, operand1));
        printf("actual:   2**%d == 0x%08X == %u\n",
               operand1, exponentiate((int) operand1), exponentiate((int) operand1));
    } else if (!strncmp(input_buffer, "is_negative", 11)
               || !strncmp(input_buffer, "is-negative", 11)
               || !strncmp(input_buffer, "is negative", 11)
               || !strncmp(input_buffer, "isnegative", 10)) {
        parse_operand(input_buffer + 11, &operand1);
        printf("expected: %hd (0x%04hX) %s negative\n",
               (int16_t) operand1, (uint16_t) operand1, ((int16_t) operand1 < 0 ? "is" : "is not"));
        printf("actual:   %hd (0x%04hX) %s negative\n",
               (int16_t) operand1, (uint16_t) operand1, (is_negative((uint16_t) operand1) ? "is" : "is not"));
    } else if (!strncmp(input_buffer, "add1", 4)) {
        evaluate_print_one_bit_adder(input_buffer);
    } else if (!strncmp(input_buffer, "add32", 5)) {
        evaluate_print_thirty_two_bit_adder(input_buffer);
    } else if (!strncmp(input_buffer, "mul2", 4)) {
        evaluate_print_power_of_two_multiplier(input_buffer);
    } else {
        char *next;
        if (isdigit(input_buffer[0]) || input_buffer[0] == '-') {
            next = parse_operand(input_buffer, &operand1);
        } else {
            next = input_buffer;
            operand1 = 0;
        }
        next = parse_operator(next, operator);
        parse_operand(next, &operand2);
        switch (operator[0]) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
                evaluate_print_arithmetic((uint16_t) operand1, operator[0], (uint16_t) operand2);
                break;
            case '!':
                if (operator[1] == '\0') {
                    printf("expected: !%d = %d\n", operand2, !operand2);
                    printf("actual:   !%d = %d\n", operand2, logical_not(operand2));
                } else if (operator[1] == '=') {
                    printf("expected: (%hd != %hd) = %d\n",
                           (uint16_t) operand1, (uint16_t) operand2,
                           (uint16_t) operand1 != (uint16_t) operand2);
                    printf("actual:   (%hd != %hd) = %d\n",
                           (uint16_t) operand1, (uint16_t) operand2,
                           not_equal((uint16_t) operand1, (uint16_t) operand2));
                } else {
                    printf("Unknown operator: %s\n", operator);
                }
                break;
            case '&':
                printf("expected: %d && %d = %d\n", operand1, operand2, operand1 && operand2);
                printf("actual:   %d && %d = %d\n", operand1, operand2, logical_and(operand1, operand2));
                break;
            case '|':
                printf("expected: %d || %d = %d\n", operand1, operand2, operand1 || operand2);
                printf("actual:   %d || %d = %d\n", operand1, operand2, logical_or(operand1, operand2));
                break;
            case '=':
                printf("expected: (%hd == %hd) = %d\n",
                       (uint16_t) operand1, (uint16_t) operand2,
                       (uint16_t) operand1 == (uint16_t) operand2);
                printf("actual:   (%hd == %hd) = %d\n",
                       (uint16_t) operand1, (uint16_t) operand2,
                       equal((uint16_t) operand1, (uint16_t) operand2));
                break;
            case '<':
                if (operator[1] == '\0') {
                    printf("expected: (%hd < %hd) = %d\n",
                           (int16_t) operand1, (int16_t) operand2,
                           ((int16_t) operand1) < ((int16_t) operand2));
                    printf("actual:   (%hd < %hd) = %d\n",
                           (int16_t) operand1, (int16_t) operand2,
                           signed_less_than((uint16_t) operand1, (uint16_t) operand2));
                } else if (operator[1] == '=') {
                    printf("expected: (%hd <= %hd) = %d\n",
                           (int16_t) operand1, (int16_t) operand2,
                           ((int16_t) operand1) <= ((int16_t) operand2));
                    printf("actual:   (%hd <= %hd) = %d\n",
                           (int16_t) operand1, (int16_t) operand2,
                           signed_at_most((uint16_t) operand1, (uint16_t) operand2));
                } else {
                    printf("Unknown operator: %s\n", operator);
                }
                break;
            case '>':
                if (operator[1] == '\0') {
                    printf("expected: (%hd > %hd) = %d\n",
                           (int16_t) operand1, (int16_t) operand2,
                           ((int16_t) operand1) > ((int16_t) operand2));
                    printf("actual:   (%hd > %hd) = %d\n",
                           (int16_t) operand1, (int16_t) operand2,
                           signed_greater_than((uint16_t) operand1, (uint16_t) operand2));
                } else if (operator[1] == '=') {
                    printf("expected: (%hd >= %hd) = %d\n",
                           (int16_t) operand1, (int16_t) operand2,
                           ((int16_t) operand1) >= ((int16_t) operand2));
                    printf("actual:   (%hd >= %hd) = %d\n",
                           (int16_t) operand1, (int16_t) operand2,
                           signed_at_least((uint16_t) operand1, (uint16_t) operand2));
                } else {
                    printf("Unknown operator: %s\n", operator);
                }
                break;
            default:
                printf("Unknown operator: %s\n", operator);
        }
    }
    return keep_going;
}
