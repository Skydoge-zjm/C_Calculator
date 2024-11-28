#ifndef DATA_STRUCTURE_DATATYPE_H
#define DATA_STRUCTURE_DATATYPE_H

#define MAX_CONTENT_LENGTH 1024

typedef enum {
    TYPE_NUMBER,
    TYPE_OPERATOR,
} ElementType;

typedef enum
{
    OP_ADD,         // +
    OP_SUBTRACT,    // -
    OP_MULTIPLY,    // *
    OP_DIVIDE,      // /
    OP_POW,         // ^
    LEFT_PAREN,     // (
    RIGHT_PAREN,    // )

    /* Here we put the func in the Operator */
    FUNC_EXP,       // exp
    FUNC_LOG,       // log

    OP_NONE
} Operator;


typedef struct
{
    ElementType type;
    union
    {
        double number;
        Operator op;
    } data;
} DataType;

DataType buildElement(ElementType type, void *value);
void printElement(DataType x);
char *operatorIntoString(Operator op);

#endif //DATA_STRUCTURE_DATATYPE_H
