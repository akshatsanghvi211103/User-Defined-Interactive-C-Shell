#include "lib.h"
#include "cd.h"
extern void err(char *command);
void cd(char *rand, char *command)
{
    command = strtok_r(NULL, " \t", &rand);
    char *command2 = strtok_r(NULL, " \t", &rand);
    if (command2 != NULL)
    {
        err("cd");
        return;
    }
    if (command == NULL)
    {
        count++;
        chdir(mainname);
        strcpy(prevdir, directory);
        return;
    }
    else if (!strcmp(command, "-"))
    {
        if (count == 0)
        {
            printf("cd: OLDPWD not set\n");
            return;
        }
        count++;
        printf("%s\n", prevdir);
        chdir(prevdir);
        strcpy(prevdir, directory);
        return;
    }
    else if (command[0] == '~')
    {
        count++;
        char tempdir[201];
        strcpy(prevdir, directory);
        strcpy(tempdir, mainname);
        strcat(tempdir, &command[1]);
        chdir(tempdir);
        // printf("%s\n", tempdir);
        return;
    }
    if (chdir(command) == 0)
    {
        strcpy(prevdir, directory);
        count++;
    }
    else
    {
        perror("cd: ");
    }
}