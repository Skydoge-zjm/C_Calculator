#ifndef CALCULATOR_OPERATOR_H
#define CALCULATOR_OPERATOR_H

#include "../Modules/DataType/DataType.h"

int precedence(Operator op);

int isOperator(const char *str);
Operator getOperator(const char* str);
int isFunction(const char *str);
Operator getFunction(const char** str);

#endif //CALCULATOR_OPERATOR_H
