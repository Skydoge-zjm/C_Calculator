#include <stdio.h>

#include "SeqList.h"
#include "../../Error/Error.h"

void init_seqlist(SeqList* seqlist) {
    seqlist->last = 0;
}

void add_to_seqlist(SeqList* seqlist, DataType element) {
    if (seqlist->last >= MAX_LIST_SIZE)
    {
        raiseListError(SEQLIST_ADD_TO_FULL);
    }
    else
    {
        seqlist->data[seqlist->last] = element;
        seqlist->last++;
    }
}

void print_seqlist(SeqList* seqlist)
{
    if (seqlist->last == 0)
    {
        printf("Empty Sequenlist.");
    }
    else
    {
        printf("Length: %d\n", seqlist->last);
        for(int i = 0; i < seqlist->last; i++) {
            printElement(seqlist->data[i]);
        }
        printf("\n");
    }
}