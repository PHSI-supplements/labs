/**************************************************************************//**
 *
 * @file duplicator.c
 *
 * @author (STUDENT -- TYPE YOUR NAME HERE)
 *
 * @brief Functions that students must modify for DuplicatorLab to eliminate
 * race conditions without starving a thread.
 *
 ******************************************************************************/

/*
 * DuplicatorLab assignment and starter code (c) 2022 Christopher A. Bohn
 * DuplicatorLab solution (c) the above-named student
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include "duplicator.h"

/*
 * Shared state between the threads
 */
volatile char shared_buffer[BUFFER_SIZE] = {0};
volatile enum {
    BUFFER_HAS_DATA, BUFFER_IS_EMPTY, FINISHED
} status = BUFFER_IS_EMPTY;
pthread_mutex_t mutex;

/**
 * Reads from the source file and places a line of text into the shared buffer.
 *
 * @param arg a <code>FILE<code> pointer to a file open for reading
 * @return <code>NULL</code>
 */
void *read_original(void *arg) {
    FILE *source_file = (FILE *) arg;
    char local_buffer[BUFFER_SIZE];
    bool copying = true;
    while (copying) {
        if (status == BUFFER_IS_EMPTY) {
            status = BUFFER_HAS_DATA;
            if (fgets(local_buffer, BUFFER_SIZE, source_file)) {
                memcpy((char *) shared_buffer, local_buffer, BUFFER_SIZE);
            } else {
                copying = false;
            }
        } else {
            ;
        }
    }
    status = FINISHED;
    return NULL;
}

/**
 * Places the contents of the shared buffer into the destination file. For threading efficiency, a local buffer is used
 * as an intermediary to make the shared buffer available while the file on secondary storage is accessed.
 *
 * @param arg a <code>FILE<code> pointer to a file open for writing
 * @return <code>NULL</code>
 */
void *write_copy(void *arg) {
    FILE *destination_file = (FILE *) arg;
    char local_buffer[BUFFER_SIZE];
    bool copying = true;
    while (copying) {
        if (status == BUFFER_HAS_DATA) {
            status = BUFFER_IS_EMPTY;
            memcpy(local_buffer, (char *) shared_buffer, BUFFER_SIZE);
            fputs(local_buffer, destination_file);
        } else if (status == FINISHED) {
            copying = false;
        } else {
            ;
        }
    }
    return NULL;
}

/**
 * Utility function that is responsible for managing the reading and writing threads.
 *
 * @param source_file       a <code>FILE<code> pointer to a file open for reading
 * @param destination_file  a <code>FILE<code> pointer to a file open for writing
 */
void duplicate(FILE *source_file, FILE *destination_file) {
    pthread_t source_thread, destination_thread;
    pthread_create(&source_thread, NULL, read_original, source_file);
    pthread_create(&destination_thread, NULL, write_copy, destination_file);
    pthread_join(source_thread, NULL);
    pthread_join(destination_thread, NULL);
}
