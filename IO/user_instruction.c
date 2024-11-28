#include <stdio.h>
#include <stdlib.h>

#include "IO.h"

void print_user_instruction()
{
    FILE *file = fopen(PATH_FILE_user_instruction, "r");
    if (file == NULL)
    {
        exit(20001);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file))
    {
        printf("%s", buffer);
    }

    fclose(file);
}