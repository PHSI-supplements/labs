/**************************************************************************//**
 *
 * @file unit-tests.c
 *
 * @author Christopher A. Bohn
 *
 * @brief Example tests for DuplicatorLab, from the write-up's example test cases.
 *
 * These tests are not sufficient to establish correctness.
 *
 * IMPORTANT: One run of these tests is not sufficient to establish the absence
 *      of a race condition!
 *
 ******************************************************************************/

/*
 * DuplicatorLab assignment and starter code (c) 2022-25 Christopher A. Bohn
 */

#include <stdint.h>
#include <stdio.h>
#include "unit-tests.h"
#include "../src/duplicator.h"

int main() {
    return run_tests(5);
}

/*****************/
/* TESTS GO HERE */
/*****************/

// we'll set up file streams to memory, so file system problem won't cause a test to fail

char const threelines[] = {
#embed "../data/threelines.txt"
};

char const paleolama[] = {
#embed "../data/paleolama.txt"
};

char data_sink[sizeof(threelines) + sizeof(paleolama)];   // guaranteed to be big enough for either source, regardless of which is bigger

char const zeroes[sizeof(threelines) + sizeof(paleolama)];

struct files {
    FILE *source;
    FILE *destination;
};

/**
 * Zeroizes `data_sink`, and opens file streams to `data_sink` and to the specified data source.
 *
 * @param destination The struct that will hold the FILE pointers
 * @param data_source The array that serves as the data source
 * @param size The size of the data source array
 * @return `destination`, with the FILE pointers assigned
 */
struct files *get_file_streams(struct files *destination, char const *restrict data_source, size_t size) {
    memset(data_sink, 0, sizeof(data_sink));
    destination->destination = fmemopen(data_sink, sizeof(data_sink), "w");
    destination->source = fmemopen((char *)data_source, size, "r");
    ASSERT_TRUE(destination->destination != nullptr);
    ASSERT_TRUE(destination->source != nullptr);
    return destination;
}


TEST(test_threelines)
    struct files files;
    get_file_streams(&files, threelines, sizeof(threelines));
    duplicate(files.source, files.destination);
//    fprintf(stderr, "%s\n", data_sink);
    ASSERT_EQUAL_MEMORY(threelines, data_sink, sizeof(threelines));
    ASSERT_EQUAL_MEMORY(zeroes, data_sink + sizeof(threelines), sizeof(data_sink) - sizeof(threelines));
    fclose(files.source);
    fclose(files.destination);
END_TEST

TEST(test_paleolama)
    struct files files;
    get_file_streams(&files, paleolama, sizeof(paleolama));
    duplicate(files.source, files.destination);
//    fprintf(stderr, "%s\n", data_sink);
    ASSERT_EQUAL_MEMORY(paleolama, data_sink, sizeof(paleolama));
    ASSERT_EQUAL_MEMORY(zeroes, data_sink + sizeof(paleolama), sizeof(data_sink) - sizeof(paleolama));
    fclose(files.source);
    fclose(files.destination);
END_TEST