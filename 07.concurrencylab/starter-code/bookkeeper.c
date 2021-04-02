/*
 * STUDENT: (Type your name here)
 */

/*
 * ConcurrencyLab (c) 2021 Christopher A. Bohn
 */

/******************************************************************************
 * This program simulates the Pleistocene Petting Zoo's revenues (such as
 * visitors paying admission) and expenses (such as visitors obtaining a
 * refund). The revenues and expenses arrive concurrently and are recorded in
 * the bookkeeping ledger. Unfortunately, the sum of the revenues and expenses
 * don't add up to the sum of the ledger entries. Students will need to
 * understand why this happens and will need to correct it.
 ******************************************************************************/

#define _XOPEN_SOURCE 500

#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define LINEAR_BUFFER_SIZE          (2*1024)
#define CIRCULAR_BUFFER_SIZE        32
#define THREAD_COUNT                5
#define TIME_SCALE                  128

typedef struct {
    const char *location;
    const char *description;
    clock_t timestamp;
    int value;
    int gain_loss;
} entry;

volatile entry ledger[LINEAR_BUFFER_SIZE];

bool uses_circular_buffer;
int ledger_size;
volatile unsigned int write_position;
volatile unsigned int read_position;
volatile bool running;


/**
 * Simulates a recurring revenue or expense for the Zoo. This function will semi-periodically generate a revenue/expense, print it
 * to the console, and record it in the ledger.
 * @param args the runtime arguments for this thread:
 *      <ul>
 *      <li>args[0] (char *) the name of the zoo location</li>
 *      <li>args[1] (char *) the description of the revenue/expense</li>
 *      <li>args[2] (int *) the lower bound for the value</li>
 *      <li>args[3] (int *) the upper bound for the value</li>
 *      <li>args[4] (int *) the mean duration between revenues/expenses being generated</li>
 *      <li>args[5] (int *) the <i>local</i> gain/loss, to be used as a return value
 *      </ul>
 * @return the <i>local</i> gain/loss
 */
void *revenue_expense_generator(void *args) {
    const char *location = ((char **)args)[0];
    const char *description = ((char **)args)[1];
    int lower_bound = *((int **)args)[2];
    int upper_bound = *((int **)args)[3];
    int difference = upper_bound - lower_bound;
    int mean_pause = *((int **)args)[4] * TIME_SCALE;
    int *gain_loss;
    gain_loss = ((int **)args)[5];
    *gain_loss = 0;
    bool reached_end_of_ledger = false;
    struct timespec real_time;
    clock_gettime(CLOCK_REALTIME, &real_time);
    long now = 1000000000 * real_time.tv_sec + real_time.tv_nsec;
    unsigned int seed = (unsigned int)(now + (long)pthread_self());
    while (running && !reached_end_of_ledger) {
        clock_gettime(CLOCK_REALTIME, &real_time);
        now = 1000000000 * real_time.tv_sec + real_time.tv_nsec;
        int value = difference == 0 ? lower_bound : rand_r(&seed) % difference + lower_bound;
        int pause = rand_r(&seed) % (2 * TIME_SCALE) - TIME_SCALE + mean_pause;
        unsigned int my_write_position = write_position;
        ledger[my_write_position].location = location;
        ledger[my_write_position].description = description;
        ledger[my_write_position].timestamp = now;
        ledger[my_write_position].value = value;
        ledger[my_write_position].gain_loss += value;
        *gain_loss += value;
        write_position++;
        if (uses_circular_buffer) {
            write_position = write_position % ledger_size;
        } else {
            reached_end_of_ledger = (write_position >= ledger_size - THREAD_COUNT + 1);
        }
        printf("%ld (%d) - %s, %dzm\n", (unsigned long)now, my_write_position, description, value);
        fflush(stdout);
        usleep(pause);
    }
    running = false;
    return gain_loss;
}

/**
 * Reads ledger entries and maintains a running tally of the total gain/loss.
 * @param args the runtime arguments for this thread:
 *      <ul>
 *      <li>args[0] ignored</li>
 *      <li>args[1] (char *) the description of the accountant</li>
 *      <li>args[2] ignored</li>
 *      <li>args[3] ignored</li>
 *      <li>args[4] (int *) the mean duration between ledger entries being read</li>
 *      <li>args[5] (int *) the gain/loss tally, to be used as a return value
 *      </ul>
 * @return
 */
void *accounting(void *args) {
    const char *description = ((char **)args)[1];
    int mean_pause = *((int **)args)[4] * TIME_SCALE;
    struct timespec real_time;
    clock_gettime(CLOCK_REALTIME, &real_time);
    long now = 1000000000 * real_time.tv_sec + real_time.tv_nsec;
    unsigned int seed = (unsigned int)(now + (long)pthread_self());
    int tally = 0;
    while (running) {
        if (read_position != write_position) {
            int pause = rand_r(&seed) % (2 * TIME_SCALE) - TIME_SCALE + mean_pause;
            printf("\t%s (%d) - %s, %dzm\n", description, read_position,
                   ledger[read_position].description, ledger[read_position].value);
            fflush(stdout);
            tally += ledger[read_position].value;
            read_position++;
            if (uses_circular_buffer) {
                read_position = read_position % ledger_size;
            }
            usleep(pause);
        }
    }
    *((int **)args)[5] = tally;
    return ((int **)args)[5];
}

void terminate() {
    running = false;
}

int main(int argc, const char **argv) {
    // INITIALIZATION
    uses_circular_buffer = false;
    ledger_size = LINEAR_BUFFER_SIZE;
    if (argc > 1) {
        long requested_ledger_size = strtol(argv[1], NULL, 10);
        if (requested_ledger_size < ledger_size) {
            ledger_size = (int)requested_ledger_size;
        } else {
            fprintf(stderr, "Requested ledger size %ld is too great; setting ledger size to %d.\n",
                    requested_ledger_size, ledger_size);
        }
    }
    printf("Ledger is a %d-entry %s buffer\n", ledger_size, uses_circular_buffer ? "circular" : "linear");
    write_position = read_position = 0;
    running = true;
    sigset(SIGINT, terminate);
    // PREPARING THREAD PARAMETERS
    pthread_t tid[THREAD_COUNT];
    char *locations[THREAD_COUNT] = {"Admissions-1", "Admissions-2", "Admissions-3", "Customer Service", "Accountant"};
    char *descriptions[THREAD_COUNT] = {"visitor buys admission at gate 1",
                                        "visitor buys admission at gate 2",
                                        "visitor buys admission at gate 3",
                                        "refund issued at Customer Service",
                                        "Accounting reviews ledger"};
    int lower_bounds[THREAD_COUNT] = {10, 10, 10, -15, 0};
    int upper_bounds[THREAD_COUNT] = {10, 10, 10, -5, 0};
    int pauses[THREAD_COUNT] = {500, 450, 600, 5000, 400};
    int gains_losses[THREAD_COUNT];
    // CREATING THREADS FOR REVENUE/EXPENSE GENERATORS
    int i;
    for (i = 0; i < THREAD_COUNT - 1; i++) {
        void **args = calloc(6, sizeof(void *));
        args[0] = locations[i];
        args[1] = descriptions[i];
        args[2] = lower_bounds + i;
        args[3] = upper_bounds + i;
        args[4] = pauses + i;
        args[5] = gains_losses + i;
        pthread_create(tid + i, NULL, revenue_expense_generator, args);
        printf("Created thread %ld for %s\n", (long)tid[i], ((char **)args)[0]);
    }
    // CREATING THREAD FOR ACCOUNTANT
    void **args = calloc(6, sizeof(void *));
    args[0] = locations[i];
    args[1] = descriptions[i];
    args[2] = lower_bounds + i;
    args[3] = upper_bounds + i;
    args[4] = pauses + i;
    args[5] = gains_losses + i;
    pthread_create(tid + i, NULL, accounting, args);
    printf("Created thread %ld for %s\n", (long)tid[i], ((char **)args)[0]);
    // WAIT UNTIL THE END OF THE LEDGER IS REACHED OR THE USER INTERRUPTS EXECUTION
    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(tid[i], NULL);
        printf("Thread %ld terminated.\n", (long)tid[i]);
    }
    // FINISH READING THE LEDGER
    int ledger_tally = gains_losses[THREAD_COUNT - 1];
    while (read_position != write_position) {
        printf("\t%s (%d) - %s, %dzm\n", descriptions[THREAD_COUNT - 1], read_position,
               ledger[read_position].description, ledger[read_position].value);
        ledger_tally += ledger[read_position].value;
        read_position++;
        if (uses_circular_buffer) {
            read_position = read_position % ledger_size;
        }
    }
    // ACCOUNTING REPORT
    int gain_loss = 0;
    printf("Revenue/Expense Report\n");
    for (i = 0; i < THREAD_COUNT - 1; i++) {
        printf("%20s   %10dzm\n", locations[i], gains_losses[i]);
        gain_loss += gains_losses[i];
    }
    printf("                       ------------\n");
    printf("Total gains/losses:    %10dzm\n", gain_loss);
    printf("Accounting crosscheck: %10dzm\n", ledger_tally);
}
