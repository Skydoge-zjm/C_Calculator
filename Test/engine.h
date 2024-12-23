//
// Created by Skydoge on 2024/12/23.
//

#ifndef CALCULATOR_ENGINE_H
#define CALCULATOR_ENGINE_H

#define MAX_THREADS 1
#define MAX_LINE_LENGTH 1024
#define MAX_BUFFER_SIZE 1024

#define TEST_FILE_PATH "../Test/test_data/math_expressions.csv"

#define TOLERABLE_RELATIVE_ERROR 0.000001
#define TOLERABLE_ABSOLUTE_ERROR 0.000001

typedef struct
{
    char **lines;
    int start;
    int end;
} ThreadData;

void read_and_test_from_file(const char *filename, double * acc);

#endif //CALCULATOR_ENGINE_H
