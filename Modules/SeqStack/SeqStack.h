#ifndef CALCULATOR_SEQSTACK_H
#define CALCULATOR_SEQSTACK_H

#define MAX_STACK_SIZE 1024

#include "../DataType/DataType.h"

typedef struct
{
    DataType data[MAX_STACK_SIZE];
    int top;
} SeqStack;

void initStack(SeqStack *s);
int isEmpty(SeqStack *s);
int isFull(SeqStack *s);
void push(SeqStack *s, DataType value);
DataType pop(SeqStack *s);
DataType peek(SeqStack *s);
void printStack(SeqStack *s);

#endif //CALCULATOR_SEQSTACK_H
