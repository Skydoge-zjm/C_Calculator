#ifndef DATA_STRUCTURE_ERROR_H
#define DATA_STRUCTURE_ERROR_H

typedef enum
{
    INVALID_INDEX_OUT_OF_RANGE,
    INVALID_INDEX_WRONG_DATATYPE
} RangeErrorType;

void raiseRangeError(RangeErrorType errorType, ...);


typedef enum
{
    INPUT_OVERFLOW_TOO_MANY_TIMES,
    INPUT_END_OF_FILE,
    OTHER_INPUT_ERROR
} IOErrorType;

void raiseIOError(IOErrorType errorType);


typedef enum
{
    ILLEGAL_CHARACTER,  // 21001
    UNMATCHED_PARENTHESIS,  // 21002
    MISPLACED_OPERATOR  // 21003
} ExpressionInvalidityErrorType;

void raiseExpressionInvalidityError(ExpressionInvalidityErrorType errorType);


typedef enum
{
    UNKNOWN_TYPE,  // 22001
    UNKNOWN_OPERATOR,  // 22002
} DataTypeErrorType;

void raiseDataTypeError(DataTypeErrorType errorType);

typedef enum
{
    SEQSTACK_POP_FROM_EMPTY,  // 30001
    SEQSTACK_PEEK_FROM_EMPTY,  // 30002
    SEQSTACK_PUSH_TO_FULL,  // 30003
} StackErrorType;

void raiseStackError(StackErrorType errorType);

typedef enum
{
    SEQLIST_ADD_TO_FULL,  // 31001
} ListErrorType;

void raiseListError(ListErrorType errorType);

#endif //DATA_STRUCTURE_ERROR_H

