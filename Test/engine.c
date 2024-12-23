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
    ThreadResult *result = malloc(sizeof(ThreadResult)); // 用于存储结果
    result->positive_count = 0;
    result->total_processed = 0;

    for (int i = data->start; i < data->end; i++) {
        result->total_processed++;
        char buffer[MAX_BUFFER_SIZE];
        double result_true = 0.0;
        double result_calculated = 0.0;

        // 读取行中的数据
        char *token = strtok(data->lines[i], ",");
        if (token != NULL) {
            strncpy(buffer, token, MAX_BUFFER_SIZE - 1);
            buffer[MAX_BUFFER_SIZE - 1] = '\0'; // 确保以 null 结尾
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

    char *lines[1000];  // 假设文件最多有1000行
    int line_count = 0;

    // 读取文件行
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) && line_count < 1000) {
        lines[line_count] = strdup(line);  // 复制行内容
        line_count++;
    }
    fclose(file);

    // 计算每个线程处理的行数
    int lines_per_thread = line_count / MAX_THREADS;
    int remaining_lines = line_count % MAX_THREADS;

    pthread_t threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];

    // 创建线程
    int start = 0;
    for (int i = 0; i < MAX_THREADS; i++) {
        int end = start + lines_per_thread + (i < remaining_lines ? 1 : 0);

        thread_data[i].lines = lines;
        thread_data[i].start = start;
        thread_data[i].end = end;

        pthread_create(&threads[i], NULL, process_lines, &thread_data[i]);
        start = end;
    }

    // 收集线程结果
    int all_threads_total_positive_count = 0;
    int all_threads_total_processed_count = 0;
    for (int i = 0; i < MAX_THREADS; i++) {
        ThreadResult *result;
        pthread_join(threads[i], (void **)&result);
        printf("Thread %d: Positive count = %d, Total processed = %d\n",
               i, result->positive_count, result->total_processed);
        all_threads_total_positive_count += result->positive_count;
        all_threads_total_processed_count += result->total_processed;
        free(result); // 释放分配的内存
    }
    printf("Total positive count: %d\n", all_threads_total_positive_count);
    printf("Total processed count: %d\n", all_threads_total_processed_count);

    // 释放内存
    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
}