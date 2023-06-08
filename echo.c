#include "lib.h"
#include "echo.h"

void echo(char *rand, char *command)
{
    command = strtok_r(NULL, " \t", &rand);
    while (command != NULL)
    {
        printf("%s ", command);
        command = strtok_r(NULL, " \t", &rand);
    }
    printf("\b\n"); // to remove the last extra space at the end!
}