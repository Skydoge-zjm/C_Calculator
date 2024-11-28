#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "IO.h"

void checkExpressionValidity(const char* expr)
{
    int balance = 0;
    bool lastWasOperator = true;

    for (int i = 0; expr[i]; i++)
    {
        char c = expr[i];

        if (isspace(c)) continue;

        if (isdigit(c) || c == '.')
        {
            lastWasOperator = false;
            while (isdigit(expr[i]) || expr[i] == '.') i++;
            i--;
        }
        else if (c == '(')
        {
            balance++;
            lastWasOperator = true;
        }
        else if (c == ')')
        {
            balance--;
            if (balance < 0)
            {
                raiseExpressionInvalidityError(UNMATCHED_PARENTHESIS);
            }
            lastWasOperator = false;
        }
        else if (strchr("+-*/^", c))
        {
            if (lastWasOperator)
            {
                raiseExpressionInvalidityError(MISPLACED_OPERATOR);
            }
            lastWasOperator = true;
        }
        else if (strncmp(&expr[i], "exp", 3) == 0 || strncmp(&expr[i], "log", 3) == 0)
        {
            i += 2;
            lastWasOperator = true;
        }
        else
        {
            raiseExpressionInvalidityError(ILLEGAL_CHARACTER);
        }
    }

    if (balance != 0)
    {
        raiseExpressionInvalidityError(UNMATCHED_PARENTHESIS);
    }

    if (lastWasOperator)
    {
        raiseExpressionInvalidityError(MISPLACED_OPERATOR);
    }
}

