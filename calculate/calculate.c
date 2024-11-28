#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "../Modules/SeqStack/SeqStack.h"
#include "../Modules/SeqList/SeqList.h"
#include "calculate.h"
#include "../Error/Error.h"

void fuseParseRPM(const char* input, SeqList* output)
{
    /* This func read and parse the input string, output an RPM(SeqList)
     * Algorithm:
     * for each one in input:
     *   if ' ': continue
     *   if single op:
     */
    SeqStack s;
    initStack(&s);  // operator stack init

    const char *p = input;
    char *end;  // use for strtod

    while (*p != '\0')
    {
        /* All the cases:
         * - ' '(space)
         * - digit
         * - operator (+-*div^)
         * - function (exp()log())
         * - '('
         * - ')'
         */
        if (*p == ' ')
        {
            // Pass the space
            p++;
            continue;
        }
        else if (isdigit(*p))
        {
            // Parse the real number, save into the RPM
            double value = strtod(p, &end);
            p = end - 1;

            add_to_seqlist(output, buildElement(TYPE_NUMBER, &value));
        }
        else if (isOperator(p))
        {
            // Parse the operator, push in stack, pop
            /* When *p is an operator op:
             * - if stack is empty
             *     push(op)
             * - else
             *     - if precedence(op) > precedence(stack top)
             *         push(op)
             *     - else
             *         Loop
             *             { pop() }
             *         until precedence(op) > precedence(stack top)
             *         push(op)
             */
            Operator op = getOperator(p);

            if (isEmpty(&s))
            {
                push(&s, buildElement(TYPE_OPERATOR, &op));
            }
            else
            {
                while (!isEmpty(&s) && precedence(op) <= precedence(peek(&s).data.op))
                {
                    // while this op has a lower or same precedence than the stack top
                    // pop from the stack
                    add_to_seqlist(output, pop(&s));
                }
                push(&s, buildElement(TYPE_OPERATOR, &op));
            }
        }
        else if (isFunction(p))
        {
            /* Functions have the highest precedence, so push() always. */
            Operator op = getFunction(&p);
            push(&s, buildElement(TYPE_OPERATOR, &op));
        }
        else if (*p == '(')
        {
            Operator op = LEFT_PAREN;
            push(&s, buildElement(TYPE_OPERATOR, &op));
        }
        else if (*p == ')')
        {
            while (!isEmpty(&s) && peek(&s).data.op != LEFT_PAREN)
            {
                // pop into output until '('
                add_to_seqlist(output, pop(&s));
            }
            pop(&s);  // pop '('
        }
        p++;
        //printf("%c\n", *p);
        //printStack(&s);
        //print_seqlist(output);
    }

    while (!isEmpty(&s))
    {
        add_to_seqlist(output, pop(&s));
    }

    /* DEBUG
    printStack(&s);
    print_seqlist(output);
     */
}

void applyOperator(SeqStack* s, Operator op)
{
    /* if + - * div ^
     * value_out = value_2 op value_1
     * if exp log
     * value_out = op value_1
     */
    double value_1;
    double value_2;
    double value_out;
    switch (op)
    {
        case OP_ADD:
            value_1 = pop(s).data.number;
            value_2 = pop(s).data.number;
            value_out = value_2 + value_1;
            break;
        case OP_SUBTRACT:
            value_1 = pop(s).data.number;
            value_2 = pop(s).data.number;
            value_out = value_2 - value_1;
            break;
        case OP_MULTIPLY:
            value_1 = pop(s).data.number;
            value_2 = pop(s).data.number;
            value_out = value_2 * value_1;
            break;
        case OP_DIVIDE:
            value_1 = pop(s).data.number;
            value_2 = pop(s).data.number;
            value_out = value_2 / value_1;
            break;
        case OP_POW:
            value_1 = pop(s).data.number;
            value_2 = pop(s).data.number;
            value_out = pow(value_2, value_1);
            break;

        case FUNC_EXP:
            value_1 = pop(s).data.number;
            value_out = exp(value_1);
            break;
        case FUNC_LOG:
            value_1 = pop(s).data.number;
            value_out = log(value_1);
            break;

        default:
            raiseDataTypeError(UNKNOWN_OPERATOR);
    }

    push(s, buildElement(TYPE_NUMBER, &value_out));
}

int calculatePostfix(SeqList* postfix, double* outcome)
{
    /* This function calculatePostfix receives (SeqList) postfix
     * return the (double) outcome
     *
     * Algorithm:
     * for element in postfix:
     *   - if element is a number:
     *       push(element)
     *   - else (an operator)
     *       number_1 = pop()
     *       number_2 = pop()  ## if element is a function, only pop once
     *       push({number_1 element number_2})  { } means calculate
     *           ## if element is a function, push({element number_1})
     * outcome = pop()
     * if stack is empty: OK, return 0
     * else: Something wrong, return 1
     */
    SeqStack s;
    initStack(&s);  // stack init

    for (int i = 0; i < postfix->last; i++)
    {
        DataType element = postfix->data[i];
        if (element.type == TYPE_NUMBER)
        {
            push(&s, postfix->data[i]);
        }
        else if(element.type == TYPE_OPERATOR)
        {
            applyOperator(&s, element.data.op);

        }
        else
        {
            raiseDataTypeError(UNKNOWN_TYPE);
        }
    }

    *outcome = pop(&s).data.number;

    if (isEmpty(&s))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

double parse_and_calculate(const char *infix) {
    SeqList postfix;
    init_seqlist(&postfix);

    fuseParseRPM(infix, &postfix);

    double result;
    int stat = calculatePostfix(&postfix, &result);

    if (stat == 0)
    {
        return result;
    }
    else
    {
        printf("Stack not empty when finish calculation.");
        exit(40001);
    }
}