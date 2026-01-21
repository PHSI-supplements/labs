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
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

constexpr size_t MAXIMUM_NUMBER_OF_TESTS = 128;

typedef bool (*test_function)(void);

typedef struct {
    test_function function;
    char const *name;
} test_case_t;

static test_case_t test_cases[MAXIMUM_NUMBER_OF_TESTS];
static size_t number_of_tests = 0;

static inline void register_test(test_function function, char const *name) {
    assert(number_of_tests < MAXIMUM_NUMBER_OF_TESTS);
    test_cases[number_of_tests].function = function;
    test_cases[number_of_tests].name = name;
    number_of_tests++;
}

#define TEST(name)                          \
    static bool name(void);                 \
    [[gnu::constructor]]                    \
    static void register_##name(void) {     \
        register_test(name, #name);         \
    }                                       \
    static bool name(void) {

#define END_TEST    return true; }

#define FORMAT(x) _Generic((x),     \
    char: "%c",                     \
    signed char: "%hhd",            \
    unsigned char: "%hhu",          \
    short: "%hd",                   \
    unsigned short: "%hu",          \
    int: "%d",                      \
    unsigned int: "%u",             \
    long: "%ld",                    \
    unsigned long: "%lu",           \
    long long: "%lld",              \
    unsigned long long: "%llu",     \
    float: "%f",                    \
    double: "%f",                   \
    default: "%p"                   \
)

#define PRINT_HEX(x) _Generic((x),                                              \
    char:               fprintf(stderr, " (0x%02hhX)", (unsigned char)(x)),     \
    signed char:        fprintf(stderr, " (0x%02hhX)", (unsigned char)(x)),     \
    unsigned char:      fprintf(stderr, " (0x%02hhX)", (signed char)(x)),       \
    short:              fprintf(stderr, " (0x%04hX)", (unsigned short)(x)),     \
    unsigned short:     fprintf(stderr, " (0x%04hX)", (unsigned short)(x)),     \
    int:                fprintf(stderr, " (0x%08X)", (unsigned int)(x)),        \
    unsigned int:       fprintf(stderr, " (0x%08X)", (unsigned int)(x)),        \
    long:               fprintf(stderr, " (0x%lX)", (unsigned long)(x)),        \
    unsigned long:      fprintf(stderr, " (0x%lX)", (unsigned long)(x)),        \
    long long:          fprintf(stderr, " (0x%llX)", (unsigned long long)(x)),  \
    unsigned long long: fprintf(stderr, " (0x%llX)", (unsigned long long)(x)),  \
    default:            ((void)0)                                               \
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
        auto _expected = (expected);                                \
        auto _actual = (actual);                                    \
        if (_expected != _actual) {                                 \
            fprintf(stderr, "Expected ");                           \
            fprintf(stderr, FORMAT(_expected), _expected);          \
            PRINT_HEX(_expected);                                   \
            fprintf(stderr, ", got ");                              \
            fprintf(stderr, FORMAT(_actual), _actual);              \
            PRINT_HEX(_actual);                                     \
            fprintf(stderr, " at %s:%d.\n", __FILE__, __LINE__);    \
            return false;                                           \
        }                                                           \
    } while (0)

#define ASSERT_ALMOST_EQUAL(expected, actual, delta) do {                           \
        auto _expected = (expected);                                                \
        auto _actual = (actual);                                                    \
        auto _delta = (delta);                                                      \
        if ((_actual < _expected - _delta) ||                                       \
            (_actual > _expected + _delta)) {                                       \
            fprintf(stderr, "Expected ");                                           \
            fprintf(stderr, FORMAT(_expected), _expected);                          \
            fprintf(stderr, " ± ");                                                 \
            fprintf(stderr, FORMAT(_delta), _delta);                                \
            fprintf(stderr, ", got ");                                              \
            fprintf(stderr, FORMAT(_actual), _actual);                              \
            fprintf(stderr, " at %s:%d.\n", __FILE__, __LINE__);                    \
            return false;                                                           \
        }                                                                           \
    } while (0)

#define ASSERT_EQUAL_STRINGS(expected, actual) do {                 \
        char const * _expected = expected;                          \
        char const * _actual = actual;                              \
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
    for (size_t i = 0; i < number_of_tests; i++) {
        pid_t pid = fork();
        if (!pid) {
            // test runs in the child process
            alarm(timeout_seconds);
            bool test_passes = test_cases[i].function();
            _exit(!test_passes);    // ctest follows Unix convention of exit status 0 for success
        }
        // the parent process waits for the result
        int status;
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) {
            int signal_number = WTERMSIG(status);
            switch (signal_number) {
                case SIGALRM:
                    printf("TIMEOUT:      %s\n", test_cases[i].name);
                    break;
                case SIGBUS:
                case SIGSEGV:
                    printf("MEMORY ERROR: %s\n", test_cases[i].name);
                    break;
                case SIGABRT:
                    printf("ABORT:        %s\n", test_cases[i].name);
                    break;
                case SIGFPE:
                    printf("MATH ERROR:   %s\n", test_cases[i].name);
                    break;
                case SIGPIPE:
                    printf("BROKEN PIPE:  %s\n", test_cases[i].name);
                    break;
                case SIGTERM:
                    printf("TERMINATED:   %s\n", test_cases[i].name);
                    break;
                default:
                    // printf("%s: %s\n", strsignal(signal_number), test_cases[i].name);
                    // nuros doesn't seem to have the POSIX strsignal() function -- that's odd
                    printf("Signal %d: %s\n", signal_number, test_cases[i].name);
            }
            exit_code = 1;
        } else if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0) {
                printf("PASS:         %s\n", test_cases[i].name);
            } else {
                printf("FAIL:         %s\n", test_cases[i].name);
                exit_code = 1;
            }
        } else {
            printf("ABNORMAL TEST TERMINATION: %s\n", test_cases[i].name);
            exit_code = 1;
        }
    }
    return exit_code;
}

#endif //UNIT_TESTS_H
