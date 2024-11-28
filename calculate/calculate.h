
#ifndef CALCULATOR_CALCULATE_H
#define CALCULATOR_CALCULATE_H

#include "../Modules/DataType/DataType.h"
#include "../Modules/SeqList/SeqList.h"

#include "operator.h"



// calculate.c
void fuseParseRPM(const char* infix, SeqList* postfix);

double parse_and_calculate(const char *infix);

#endif //CALCULATOR_CALCULATE_H
