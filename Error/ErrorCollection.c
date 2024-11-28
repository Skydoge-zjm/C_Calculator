#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "Error.h"
#include "../IO/IO.h"

void raiseRangeError(RangeErrorType errorType, ...)
{
    /*  This function receives an RangeErrorType and some available params.
     *  PARAMS:
     *  -- INVALID_INDEX_OUT_OF_RANGE
     *      -- (RangeErrorType) errorType, (int)min, (int)max, (int)index
     *  -- INVALID_INDEX_WRONG_DATATYPE
     *      -- (RangeErrorType) errorType
     */
    va_list args;
    va_start(args, errorType);
    switch (errorType)
    {
        case INVALID_INDEX_OUT_OF_RANGE:
            printf("Error: Index out of range.\n");
            int min_range = va_arg(args, int);
            int max_range = va_arg(args, int);
            int ind = va_arg(args, int);
            printf("- ErrorDetail: index %d is out of range [%d, %d]\n", ind, min_range, max_range);
            printf("- Tips: Please check if the index is in the valid range.\n");
            exit(10001);
        case INVALID_INDEX_WRONG_DATATYPE:
            printf("Error: Wrong index datatype.\n");
            printf("- Please check if the index is Positive Integers (or -1).\n");
            exit(10002);
        default:
            printf("Unknown Range error happens.");
            exit(10999);
    }
}

void raiseIOError(IOErrorType errorType)
{
    switch (errorType)
    {
        case INPUT_OVERFLOW_TOO_MANY_TIMES:
            printf("Error: Your input is too long. \n");
            printf("You tried %d times before.\n", MAX_INPUT_TRAILS);
            printf("Notice: The max length of your input is %d", MAX_INPUT_LENGTH - 2);
            exit(20001);
        case INPUT_END_OF_FILE:
            printf("Error: An EoF in your input, which is invalid. \n");
            exit(20002);
        case OTHER_INPUT_ERROR:
            printf("Error: Unknown error occurred when input. \n");
            exit(20003);
        default:
            printf("Unknown IO error happens.");
            exit(20999);
    }
}

void raiseExpressionInvalidityError(ExpressionInvalidityErrorType errorType)
{
    switch (errorType)
    {
        case ILLEGAL_CHARACTER:
            printf("Error: An illegal character exist in your expression. \n");
            exit(21001);
        case UNMATCHED_PARENTHESIS:
            printf("Error: The parenthesis ( ) in your expression not match. \n");
            exit(21002);
        case MISPLACED_OPERATOR:
            printf("Error: Operator misplaced. \n");
            exit(21003);
        default:
            printf("Unknown Expression Invalidity error happens.");
            exit(21999);
    }
}

void raiseDataTypeError(DataTypeErrorType errorType)
{
    switch (errorType)
    {
        case UNKNOWN_TYPE:
            printf("Error: Unknown DataType. \n");
            exit(22001);
        case UNKNOWN_OPERATOR:
            printf("Error: Unknown operator. \n");
            exit(22002);
        default:
            printf("Unknown DataType error happens.");
            exit(22999);
    }
}

void raiseStackError(StackErrorType errorType)
{
    switch (errorType)
    {
        case SEQSTACK_POP_FROM_EMPTY:
            printf("Error: Trying to pop from empty seqstack.");
            exit(30001);
        case SEQSTACK_PEEK_FROM_EMPTY:
            printf("Error: Trying to peek from empty seqstack.");
            exit(30002);
        case SEQSTACK_PUSH_TO_FULL:
            printf("Error: Trying to push to full seqstack.");
            exit(30003);
        default:
            printf("Unknown Stack error happens.");
            exit(30999);
    }
}

void raiseListError(ListErrorType errorType)
{
    switch (errorType)
    {
        case SEQLIST_ADD_TO_FULL:
            printf("Error: Trying to add to full seqlist.");
            exit(31001);
        default:
            printf("Unknown List error happens.");
            exit(31999);

    }
}