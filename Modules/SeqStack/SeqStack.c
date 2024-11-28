#include <stdio.h>

#include "SeqStack.h"
#include "../../Error/Error.h"



void initStack(SeqStack *s)
{
    s->top = 0;
}

int isEmpty(SeqStack *s)
{
    return s->top == 0;
}

int isFull(SeqStack *s)
{
    return s->top == MAX_STACK_SIZE - 1;
}

void push(SeqStack *s, DataType element)
{
    if (isFull(s))
    {
        raiseStackError(SEQSTACK_PUSH_TO_FULL);
    }
    s->top++;
    s->data[s->top] = element;


}

DataType pop(SeqStack *s)
{
    if (isEmpty(s))
    {
        raiseStackError(SEQSTACK_POP_FROM_EMPTY);
    }
    return s->data[s->top--];
}

DataType peek(SeqStack *s)
{
    if (isEmpty(s))
    {
        raiseStackError(SEQSTACK_PEEK_FROM_EMPTY);
    }
    return s->data[s->top];
}

void printStack(SeqStack *s)
{
    printf("___Stack Top___\n");
    for (int i = s->top; i > 0; i--)
    {
        printElement(s->data[i]);
    }
    printf("___Stack Bottom___\n");
}