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

#define END_TEST    }

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
                    printf("%s: %s\n", strsignal(signal_number), test_cases[i].name);
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
        }
    }
    return exit_code;
}

#endif //UNIT_TESTS_H
