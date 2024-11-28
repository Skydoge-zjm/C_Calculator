#include <string.h>

#include "operator.h"

int precedence(Operator op)
{
    switch (op)
    {
        case OP_ADD:
        case OP_SUBTRACT:
            return 1;

        case OP_MULTIPLY:
        case OP_DIVIDE:
            return 2;

        case OP_POW:
            return 3;

        case FUNC_EXP:
        case FUNC_LOG:
            return 4;

        case LEFT_PAREN:
        case RIGHT_PAREN:
            return 0;

        case OP_NONE:
            return -1;
    }
}

int isOperator(const char *str)
{
    return (*str == '+' || *str == '-' ||
            *str == '*' || *str == '/' ||
            *str == '^');
}

Operator getOperator(const char* str)
{
    /* This function getOperator is recommended to used with isOperator.
     * Because it does NOT have a strict check of type.
     */
    switch (*str)
    {
        case '+':
            return OP_ADD;
        case '-':
            return OP_SUBTRACT;
        case '*':
            return OP_MULTIPLY;
        case '/':
            return OP_DIVIDE;
        case '^':
            return OP_POW;
        default:
            return OP_NONE;
    }
}

int isFunction(const char *str)
{
    return (strncmp(str, "log", 3) == 0 || strncmp(str, "exp", 3) == 0);
}

Operator getFunction(const char** str)
{
    /* !!!!!!
     * This function getFunction is recommended to used with isFunction.
     * Because it does NOT have a strict check of type.
     * !!!!!!
     *
     * Differ from getOperator(), after parse the function name, the pointer should go ahead.
     * example: if next is 'exp' or 'log', let the pointer +2,
     * as there is always pointer +1 at the end of loop. (+3 in total)
     */
    if (strncmp(*str, "log", 3) == 0)
    {
        *str += 2;
        return FUNC_LOG;
    }
    else if (strncmp(*str, "exp", 3) == 0)
    {
        *str += 2;
        return FUNC_EXP;
    }
    else
    {
        return OP_NONE;
    }
}



