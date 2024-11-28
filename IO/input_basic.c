#include <stdio.h>
#include <string.h>

#include "IO.h"

void read_line(char *buffer)
{
    int flag = 0;
    printf("Your input: (Max length: %d)\n", MAX_INPUT_LENGTH - 2);
    for (int i = 0; i < MAX_INPUT_TRAILS; i++)
    {
        if (read_line_once(buffer) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        raiseIOError(INPUT_OVERFLOW_TOO_MANY_TIMES);
    }
}

int read_line_once(char *buffer)
{
    int total_length = 0;
    int if_overflow = 0;

    while (fgets(buffer, MAX_INPUT_LENGTH, stdin) != NULL)
    {
        /*  'fgets' read a line (max length = MAX_INPUT_LENGTH), save in buffer
         *  total_length += len(buffer)
         *  if '\n' at the end of input : valid
         *  else : continue
         *         read the other inputs, save in buffer
         *         total_length += len(buffer)
         *         !!! total_len > MAX_INPUT_LENGTH !!! --> Overflow
         */
        int len = (int) strlen(buffer);  // Considering length of input will not be over [int]
        total_length += len;

        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';  // replace '\n' with '\0' at the end of buffer
            if (total_length >= MAX_INPUT_LENGTH)
            {
                if_overflow = 1;
            }
            break;
        }

        if (total_length >= MAX_INPUT_LENGTH)
        {
            if_overflow = 1;
            break;
        }
    }

    int stat = 0;
    if (if_overflow)
    {
        // Error: Overflow
        printf("Overflow. ");
        printf("Max input length: %d\n", MAX_INPUT_LENGTH - 2);
        printf("Try once more:\n");
        stat = 1;
    }
    else if (ferror(stdin))
    {
        // Unknown error
        raiseIOError(OTHER_INPUT_ERROR);
    }
    else if (feof(stdin))
    {
        // EndOfFile
        raiseIOError(INPUT_END_OF_FILE);
    }
    else
    {
        printf("Your input:\n%s\n", buffer);
    }
    return stat;
}