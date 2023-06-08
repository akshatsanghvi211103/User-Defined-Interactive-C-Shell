#include "lib.h"
#include "pwd.h"
extern void err(char *command);
void pwd(char *rand, char *command)
{
    char *command2 = strtok_r(NULL, " \t", &rand);
    if (command2 != NULL)
    {
        err("pwd"); // are we supposed to do this?
        return;
    }
    char direc[2001];
    printf("%s\n", getcwd(direc, sizeof(direc)));
}