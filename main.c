#include <stdio.h>

#include "IO/IO.h"
#include "calculate/calculate.h"


int calculator_main()
{
    while (1)
    {
        printf("Press enter to continue. Press q and enter to quit.\n");

        if (getchar() == 'q')
        {
            printf("Thanks for using the calculator!\n");
            break;
        }

        char input[MAX_INPUT_LENGTH];
        read_line(input);

        checkExpressionValidity(input);

        double result = parse_and_calculate(input);
        printf("Result: %lf\n\n", result);
    }
    return 0;
}

int main()
{
    print_user_instruction();

    int stat;
    stat = calculator_main();

    return stat;
}


