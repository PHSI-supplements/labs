/*
 * STUDENT: (Type your name here)
 */

/*
 * ConcurrencyLab (c) 2021 Christopher A. Bohn
 */

/******************************************************************************
 * This program has a traditional implementation of the Mergesort algorithm,
 * and it has a mostly-correct implementation of Parallel Mergesort. Students
 * will need to understand why only part of the array is sorted by
 * parallel_mergesort() and fix the bug.
 ******************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *merge(const int A[], int a_length, const int B[], int b_length, int output[]);
int *sequential_mergesort(int *array, int array_length);
int *parallel_mergesort(int *array, int array_length, int threadcount);
void *parallel_mergesort_helper(void *args);

int *merge(const int A[], int a_length, const int B[], int b_length, int output[]) {
    int a = 0, b = 0, i = 0;
    int output_length = a_length + b_length;
    while (i < output_length) {
        if (a == a_length) { // NOLINT(bugprone-branch-clone)
            output[i++] = B[b++];
        } else if (b == b_length) { // NOLINT(bugprone-branch-clone)
            output[i++] = A[a++];
        } else if (A[a] < B[b]) {
            output[i++] = A[a++];
        } else {
            output[i++] = B[b++];
        }
    }
    return output;
}


int *sequential_mergesort(int *array, int array_length) {
    if (array_length > 1) {
        int left_array_length = array_length / 2;
        int right_array_length = array_length - left_array_length;
        int *left_array = array;
        int *right_array = array + left_array_length;
        sequential_mergesort(left_array, left_array_length);
        sequential_mergesort(right_array, right_array_length);
        int *sorted_array = calloc((size_t)array_length, sizeof(int));
        sorted_array = merge(left_array, left_array_length, right_array, right_array_length, sorted_array);
        for (int i = 0; i < array_length; i++) {
            array[i] = sorted_array[i];
        }
        free(sorted_array);
    }
    return array;
}

int *parallel_mergesort(int *array, int array_length, int threadcount) {
    if (threadcount < 2)
        return sequential_mergesort(array, array_length);
    if (array_length > 1) {
        int left_array_length = array_length / 2;
        int right_array_length = array_length - left_array_length;
        int *left_array = array;
        int *right_array = array + left_array_length;
        int left_threadcount = threadcount / 2;
        int right_threadcount = threadcount - left_threadcount;
        pthread_t tid[2];
        int *args[3] = {left_array, &left_array_length, &left_threadcount};
        pthread_create(tid, NULL, parallel_mergesort_helper, args);
        parallel_mergesort(right_array, right_array_length, right_threadcount);
        int *sorted_array = calloc((size_t)array_length, sizeof(int));
        sorted_array = merge(left_array, left_array_length, right_array, right_array_length, sorted_array);
        for (int i = 0; i < array_length; i++) {
            array[i] = sorted_array[i];
        }
        free(sorted_array);
    }
    return array;
}

void *parallel_mergesort_helper(void *args) {
    int **typed_args = (int **)args;
    int *array = typed_args[0];
    int *array_length = typed_args[1];
    int *threadcount = typed_args[2];
    return parallel_mergesort(array, *array_length, *threadcount);
}


int *read_input(const char *filename, int *input_array, int array_size) {
    FILE *file = fopen(filename, "r");
    int i = 0;
    while (i < array_size && (fscanf(file, "%d", input_array + i) != EOF)) { // NOLINT(cert-err34-c)
        i++;
    }
    fclose(file);
    return input_array;
}


int main(int argc, const char **argv) {
    if (argc < 2) {
        printf("Usage: ./mergesort inputfile inputsize threadcount\n");
        return 1;
    }
    int inputsize = (argc > 2) ? atoi(argv[2]) : 1 << 10; // NOLINT(cert-err34-c)
    int *sequential_array = calloc(inputsize, sizeof(int));
    int *parallel_array = calloc(inputsize, sizeof(int));
    read_input(argv[1], sequential_array, inputsize);
    for (int i = 0; i < inputsize; i++) {
        printf(" %d  ", sequential_array[i]);
        parallel_array[i] = sequential_array[i];
    }
    printf("\n");
    double sequential_start, sequential_stop, parallel_start, parallel_stop;
    // sequential mergesort
    sequential_start = (double)clock() / CLOCKS_PER_SEC;
    sequential_mergesort(sequential_array, inputsize);
    sequential_stop = (double)clock() / CLOCKS_PER_SEC;
    printf(" %d", sequential_array[0]);
    for (int i = 1; i < inputsize; i++) {
        printf("%s%d", sequential_array[i - 1] <= sequential_array[i] ? " < " : " >\a ", sequential_array[i]);
    }
    printf("\n");
    free(sequential_array);
    // parallel mergesort
    int threadcount = (argc > 3) ? atoi(argv[3]) : 1; // NOLINT(cert-err34-c)
    parallel_start = (double)clock() / CLOCKS_PER_SEC;
    parallel_mergesort(parallel_array, inputsize, threadcount);
    parallel_stop = (double)clock() / CLOCKS_PER_SEC;
    printf(" %d", parallel_array[0]);
    for (int i = 1; i < inputsize; i++) {
        printf("%s%d", parallel_array[i - 1] <= parallel_array[i] ? " < " : " >\a ", parallel_array[i]);
    }
    printf("\n");
    free(parallel_array);
/*
    fprintf(stderr, "Parallel mergesort with %d threads executed %f times faster than sequential mergesort.\n", threadcount,
            (sequential_stop - sequential_start) / (parallel_stop - parallel_start));
*/
    return 0;
}

