#ifndef CALCULATOR_IO_H
#define CALCULATOR_IO_H

#define PATH_FILE_user_instruction "../IO/user_instruction.txt"

#define MAX_INPUT_LENGTH 1024
#define MAX_INPUT_TRAILS 3

#include "../Error/Error.h"
#include "../Modules/DataType/DataType.h"
#include "../calculate/calculate.h"

void read_line(char *buffer);
int read_line_once(char *buffer);
void print_user_instruction();

void checkExpressionValidity(const char* expr);



#endif //CALCULATOR_IO_H
