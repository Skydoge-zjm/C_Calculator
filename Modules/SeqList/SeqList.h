#ifndef CALCULATOR_SEQLIST_H
#define CALCULATOR_SEQLIST_H

#define MAX_LIST_SIZE 1024

#include "../DataType/DataType.h"

typedef struct
{
    DataType data[MAX_LIST_SIZE];
    int last;
} SeqList;

void init_seqlist(SeqList* seqlist);
void add_to_seqlist(SeqList* seqlist, DataType element);
void print_seqlist(SeqList* seqlist);

#endif //CALCULATOR_SEQLIST_H
