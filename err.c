#include "lib.h"
#include "err.h"

void err(char *command)
{
    printf("%s: too many arguments\n", command);
}