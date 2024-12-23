#include <stdio.h>

#include "IO/IO.h"
#include "calculate/calculate.h"
#include "Test/engine.h"


int calculator_main()
{
    while (1)
    {
        int prompt;

        printf("Press enter to continue.\nPress t and enter to test.\nPress q and enter to quit.\n");
        prompt = getchar();

        if (prompt == 't')
        {
            getchar();
            double acc;
            printf("Start to test from test set\n");
            read_and_test_from_file(TEST_FILE_PATH, &acc);
            continue;
        }
        else if (prompt == 'q')
        {
            printf("Thanks for using the calculator!\n");
            break;
        }
        else
        {
            char input[MAX_INPUT_LENGTH];
            read_line(input);

            checkExpressionValidity(input);

            double result = parse_and_calculate(input);
            printf("Result: %lf\n\n", result);
        }

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


