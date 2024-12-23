#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

#include "../calculate/calculate.h"
#include "../IO/IO.h"
#include "engine.h"

typedef struct {
    int positive_count;
    int total_processed;
} ThreadResult;

void *process_lines(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    ThreadResult *result = malloc(sizeof(ThreadResult));
    result->positive_count = 0;
    result->total_processed = 0;

    for (int i = data->start; i < data->end; i++) {
        result->total_processed++;
        char buffer[MAX_BUFFER_SIZE];
        double result_true = 0.0;
        double result_calculated = 0.0;

        // read
        char *token = strtok(data->lines[i], ",");
        if (token != NULL) {
            strncpy(buffer, token, MAX_BUFFER_SIZE - 1);
            buffer[MAX_BUFFER_SIZE - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            result_true = atof(token);
        }

        checkExpressionValidity(buffer);

        result_calculated = parse_and_calculate(buffer);

        if (fabs(result_true - result_calculated) / result_true <= TOLERABLE_RELATIVE_ERROR ||
            fabs(result_true - result_calculated) <= TOLERABLE_ABSOLUTE_ERROR)
        {
            result->positive_count++;
        }
        else
        {
            printf("Wrong line %d: %s cal: %lf true: %lf\n", i, data->lines[i], result_calculated, result_true);
        }
    }

    return result;
}

void read_and_test_from_file(const char *filename, double *acc) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char *lines[1000];
    int line_count = 0;

    // read all lines
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) && line_count < 1000) {
        lines[line_count] = strdup(line);
        line_count++;
    }
    fclose(file);

    // cal lines per thread
    int lines_per_thread = line_count / MAX_THREADS;
    int remaining_lines = line_count % MAX_THREADS;

    pthread_t threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];

    // create thread
    int start = 0;
    for (int i = 0; i < MAX_THREADS; i++) {
        int end = start + lines_per_thread + (i < remaining_lines ? 1 : 0);

        thread_data[i].lines = lines;
        thread_data[i].start = start;
        thread_data[i].end = end;

        pthread_create(&threads[i], NULL, process_lines, &thread_data[i]);
        start = end;
    }

    // collect
    int all_threads_total_positive_count = 0;
    int all_threads_total_processed_count = 0;
    for (int i = 0; i < MAX_THREADS; i++) {
        ThreadResult *result;
        pthread_join(threads[i], (void **)&result);
        printf("Thread %d: Positive count = %d, Total processed = %d\n",
               i, result->positive_count, result->total_processed);
        all_threads_total_positive_count += result->positive_count;
        all_threads_total_processed_count += result->total_processed;
        free(result);
    }
    printf("Total positive count: %d\n", all_threads_total_positive_count);
    printf("Total processed count: %d\n", all_threads_total_processed_count);

    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
}