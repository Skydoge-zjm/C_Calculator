#include <stdio.h>
#include "DataType.h"

DataType buildElement(ElementType type, void *value) {
    DataType element;
    element.type = type;
    if (type == TYPE_NUMBER) {
        element.data.number = *(double *)value;
    } else if (type == TYPE_OPERATOR) {
        element.data.op = *(Operator *)value;
    }
    return element;
}

void printElement(DataType x)
{
    switch (x.type)
    {
        case TYPE_NUMBER:
            printf(" [Value] : %lf\n", x.data.number);
            break;
        case TYPE_OPERATOR :
            printf(" [Operator] : %s\n", operatorIntoString(x.data.op));
            break;
    }
}

char *operatorIntoString(Operator op)
{
    switch (op)
    {
        case OP_ADD:
            return "+";
        case OP_SUBTRACT:
            return "-";
        case OP_MULTIPLY:
            return "*";
        case OP_DIVIDE:
            return "/";
        case LEFT_PAREN:
            return "(";
        case RIGHT_PAREN:
            return ")";
        case FUNC_EXP:
            return "exp()";
        case OP_POW:
            return "pow()";
        case FUNC_LOG:
            return "log()";
        default:
            return "NONE";
    }
}
