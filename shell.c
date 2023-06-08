#include "lib.h"
#include "cd.h"
#include "discover.h"
#include "echo.h"
#include "history.h"
#include "ls.h"
#include "pinfo.h"
#include "pwd.h"
#include "prompt.h"
#include "signal.h"
#include "reset.h"
#include "err.h"
char mainname[2001];
char username[2001];
char hostname[2001];
char command[2001];
char directory[2001];
char prevdir[2001];
int count = 0;
int size;
int numbg = 0;
int num = 0;
int times = 0;
int bgpid[1000];
char bgcommand[1000][201];
int main()
{
    for (int i = 0; i < 1000; i++)
    {
        bgpid[i] = -1;
    }
    // printf("%d\n", getpid());
    strcpy(prevdir, "\0");
    getcwd(mainname, sizeof(mainname));
    size = strlen(mainname);
    while (1)
    {
        signal(SIGCHLD, sig_handler);
        char commandline[201];
        prompt();
        times = 0;
        fgets(commandline, 201, stdin);
        commandline[strlen(commandline) - 1] = 0;
        add_to_history(commandline, getlogin());
        for (int i = 0; i < strlen(commandline); i++)
        {
            while (commandline[i] == ' ')
                i++;
            if (commandline[i] == '&')
            {
                printf("Invalid Syntax\n");
                return 0;
            }
            else
                break;
        }
        char *rand2 = NULL;
        char *singlecommand = strtok_r(commandline, ";", &rand2);
        while (singlecommand != NULL)
        {
            int count = 1;
            for (int i = 0; i < strlen(singlecommand); i++)
            {
                if (singlecommand[i] == '&')
                    count++;
            }
            char *rand3 = NULL;
            char *cmd = strtok_r(singlecommand, "&", &rand3);
            for (int i = 0; i < count - 1; i++)
            {
                int tot = 0;
                char *args[101];
                char *nl = NULL;
                char *temp = strtok_r(cmd, " \t", &nl);
                while (temp != NULL)
                {
                    args[tot++] = temp;
                    temp = strtok_r(NULL, " \t", &nl);
                }
                args[tot] = NULL;
                strcpy(bgcommand[numbg], args[0]);
                numbg++;
                num++;
                int pid = fork();
                bgpid[numbg] = pid;
                if (!pid)
                {
                    printf("[%d] %d\n", num, getpid());
                    if (execvp(args[0], args) == -1)
                    {
                        printf("No such command!\n");
                        return 0;
                    }
                }
                times = 0;
                cmd = strtok_r(NULL, "&", &rand3);
            }
            char *rand = NULL;
            if (cmd != NULL)
            {
                int pid = getpid();
                char *command = strtok_r(cmd, " \t", &rand);
                if (command == NULL)
                    goto end;
                if (strcmp(command, "cd") == 0)
                    cd(rand, command);
                else if (strcmp(command, "echo") == 0)
                    echo(rand, command);
                else if (strcmp(command, "pwd") == 0)
                    pwd(rand, command);
                else if (strcmp(command, "ls") == 0)
                    ls_flags(rand, command);
                else if (strcmp(command, "history") == 0)
                    print_history(getlogin());
                else if (strcmp(command, "discover") == 0)
                    discover(rand, command);
                else if (strcmp(command, "exit") == 0)
                    return 0;
                else if (strcmp(command, "pinfo") == 0)
                {
                    command = strtok_r(NULL, " \t", &rand);
                    if (command != NULL)
                        pid = atoi(command);
                    pinfo(pid);
                }
                else
                {
                    char *args[100];
                    int tot = 0;
                    int status = 0;
                    while (command != NULL)
                    {
                        args[tot++] = command;
                        command = strtok_r(NULL, " \t", &rand);
                    }
                    args[tot] = NULL;
                    time_t start;
                    time_t end;
                    int p = fork();
                    if (p == 0)
                    {
                        if (execvp(args[0], args) == -1)
                        {
                            printf("No such command!\n");
                            return 0;
                        }
                    }
                    else
                    {
                        start = time(NULL);
                        waitpid(p, &status, WCONTINUED | WUNTRACED);
                        end = time(NULL);
                    }
                    times += ((end - start));
                }
            }
        end:
            singlecommand = strtok_r(NULL, ";", &rand2);
        }
    }
    return 0;
}