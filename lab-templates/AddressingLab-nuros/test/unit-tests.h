/**************************************************************************//**
 *
 * @file unit-tests.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Test function structure and runner.
 *
 ******************************************************************************/

/*
 * Minimalistic Unit Test Framework (c) 2026 Christopher A. Bohn
 */


#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include <assert.h>
#include <inttypes.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>

//constexpr size_t MAXIMUM_NUMBER_OF_TESTS = 128;

typedef bool (*test_function)(void);

typedef struct {
    test_function function;
    char const *name;
} test_case_t;

static test_case_t *test_cases = nullptr;

static inline void register_test(test_function function, char const *name) {
    constexpr size_t growth_rate = 64;
    static size_t number_of_tests = 0;
    static size_t test_cases_length = 0;
    // is there room for one more test case plus a sentinel?
    if (test_cases_length < number_of_tests + 2) {
        size_t new_length = test_cases_length + growth_rate;
        test_case_t *new_allocation = realloc(test_cases, new_length * sizeof(test_case_t));
        if (new_allocation) {
            test_cases = new_allocation;
            test_cases_length = new_length;
        } else {
            fprintf(stderr, "Warning: Unable to register more than %zu test cases.\n", number_of_tests);
            return;
        }
    }
    test_cases[number_of_tests].function = function;
    test_cases[number_of_tests].name = name;
    number_of_tests++;
    test_cases[number_of_tests].function = nullptr;
    test_cases[number_of_tests].name = nullptr;
}

#define TEST(name)                          \
    static bool name(void);                 \
    [[gnu::constructor]]                    \
    static void register_##name(void) {     \
        register_test(name, #name);         \
    }                                       \
    static bool name(void) {

#define END_TEST    return true; }

#define PRINT_VALUE(x) _Generic((x),                                                                            \
    bool:               fprintf(stderr, "%s",               (bool)(x) ? "true" : "false"),                      \
    char:               fprintf(stderr, "%c (0x%02hhX)",    (char)(x), (unsigned char)(x)),                     \
    signed char:        fprintf(stderr, "%hhd (0x%02hhX)",  (signed char)(x), (unsigned char)(x)),              \
    unsigned char:      fprintf(stderr, "%hhu (0x%02hhX)",  (unsigned char)(x), (unsigned char)(x)),            \
    short:              fprintf(stderr, "%hd (0x%04hX)",    (short)(x), (unsigned short)(x)),                   \
    unsigned short:     fprintf(stderr, "%hu (0x%04hX)",    (unsigned short)(x), (unsigned short)(x)),          \
    int:                fprintf(stderr, "%d (0x%08X)",      (int)(x), (unsigned int)(x)),                       \
    unsigned int:       fprintf(stderr, "%u (0x%08X)",      (unsigned int)(x), (unsigned int)(x)),              \
    long:               fprintf(stderr, "%ld (0x%lX)",      (long)(x), (unsigned long)(x)),                     \
    unsigned long:      fprintf(stderr, "%lu (0x%lX)",      (unsigned long)(x), (unsigned long)(x)),            \
    long long:          fprintf(stderr, "%lld (0x%llX)",    (long long)(x), (unsigned long long)(x)),           \
    unsigned long long: fprintf(stderr, "%llu (0x%llX)",    (unsigned long long)(x), (unsigned long long)(x)),  \
    _Float16:           fprintf(stderr, "%.5g (%a)",        (double)(x), (double)(x)),                          \
    float:              fprintf(stderr, "%.8g (%a)",        (double)(x), (double)(x)),                          \
    double:             fprintf(stderr, "%.17g (%a)",       (double)(x), (double)(x)),                          \
    default:            fprintf(stderr, "Unsupported type")                                                     \
)

#define ASSERT_TRUE(expression) do {                                                        \
        if (!(expression)) {                                                                \
            fprintf(stderr, "Expected true, got false at %s:%d.\n", __FILE__, __LINE__);    \
            return false;                                                                   \
        }                                                                                   \
    } while (0)

#define ASSERT_FALSE(expression) do {                                                       \
        if ((expression)) {                                                                 \
            fprintf(stderr, "Expected false, got true at %s:%d.\n", __FILE__, __LINE__);    \
            return false;                                                                   \
        }                                                                                   \
    } while (0)

#define ASSERT_EQUAL(expected, actual) do {                         \
        typeof_unqual(expected) _expected = (expected);             \
        typeof_unqual(actual) _actual = (actual);                   \
        if (_expected != _actual) {                                 \
            fprintf(stderr, "Expected ");                           \
            PRINT_VALUE(_expected);                                 \
            fprintf(stderr, ", got ");                              \
            PRINT_VALUE(_actual);                                   \
            fprintf(stderr, " at %s:%d.\n", __FILE__, __LINE__);    \
            return false;                                           \
        }                                                           \
    } while (0)

#define ASSERT_ALMOST_EQUAL(expected, actual, delta) do {           \
        typeof_unqual(expected) _expected = (expected);             \
        typeof_unqual(actual) _actual = (actual);                   \
        typeof_unqual(delta) _delta = (delta);                      \
        if ((_actual < _expected - _delta) ||                       \
            (_actual > _expected + _delta)) {                       \
            fprintf(stderr, "Expected ");                           \
            PRINT_VALUE(_expected);                                 \
            fprintf(stderr, " ± ");                                 \
            PRINT_VALUE(_delta);                                    \
            fprintf(stderr, ", got ");                              \
            PRINT_VALUE(_actual);                                   \
            fprintf(stderr, " at %s:%d.\n", __FILE__, __LINE__);    \
            return false;                                           \
        }                                                           \
    } while (0)

#define ASSERT_EQUAL_STRINGS(expected, actual) do {                 \
        char const * _expected = (expected);                        \
        char const * _actual = (actual);                            \
        if (strcmp(_expected, _actual) != 0) {                      \
            fprintf(stderr, "Expected: %s\n", _expected);           \
            fprintf(stderr, "Got:      %s\n", _actual);             \
            fprintf(stderr, "At %s:%d.\n", __FILE__, __LINE__);     \
            return false;                                           \
        }                                                           \
    } while (0)

#define ASSERT_EQUAL_MEMORY(expected_ptr, actual_ptr, size_bytes) do {                                  \
        if (memcmp((expected_ptr), (actual_ptr), size_bytes) != 0) {                                    \
            fprintf(stderr, "The specified memory regions differ at %s:%d.\n", __FILE__, __LINE__);     \
            return false;                                                                               \
        }                                                                                               \
    } while(0)

static inline int run_tests(unsigned int timeout_seconds) {
    int exit_code = 0;
    if (!test_cases) {
        printf("No tests registered.\n");
        return exit_code;
    }
    for (test_case_t *test_case = test_cases ; test_case->function; test_case++) {
        pid_t pid = fork();
        if (!pid) {
            // test runs in the child process
            alarm(timeout_seconds);
            bool test_passes = test_case->function();
            _exit(!test_passes);    // ctest follows Unix convention of exit status 0 for success
        }
        // the parent process waits for the result
        int status;
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) {
            int signal_number = WTERMSIG(status);
            switch (signal_number) {
                case SIGALRM:
                    printf("TIMEOUT:             %s\n", test_case->name);
                    break;
                case SIGBUS:
                case SIGSEGV:
                    printf("MEMORY ERROR:        %s\n", test_case->name);
                    break;
                case SIGABRT:
                    printf("ABORT:               %s\n", test_case->name);
                    break;
                case SIGFPE:
                    printf("MATH ERROR:          %s\n", test_case->name);
                    break;
                case SIGPIPE:
                    printf("BROKEN PIPE:         %s\n", test_case->name);
                    break;
                case SIGTERM:
                    printf("TERMINATED:          %s\n", test_case->name);
                    break;
                case SIGILL:
                    printf("ILLEGAL INSTRUCTION: %s\n", test_case->name);
                    break;
                default:
                    // printf("%s: %s\n", strsignal(signal_number), test_case->name);
                    // nuros doesn't seem to have the POSIX strsignal() function -- that's odd
                    printf("Signal %d: %s\n", signal_number, test_case->name);
            }
            exit_code = 1;
        } else if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0) {
                printf("PASS:         %s\n", test_case->name);
            } else {
                printf("FAIL:         %s\n", test_case->name);
                exit_code = 1;
            }
        } else {
            printf("ABNORMAL TEST TERMINATION: %s\n", test_case->name);
            exit_code = 1;
        }
    }
    return exit_code;
}

#endif //UNIT_TESTS_H
