#include "lib.h"
#include "discover.h"

void print_directories(char *target, int check)
{
    if (check == 1)
    {
        char dup[301];
        strcpy(dup, "~");
        strcat(dup, &target[strlen(mainname)]);
        printf("%s\n", dup);
    }
    else
        printf("%s\n", target);
    DIR *dhead = opendir(target);
    struct dirent *d = readdir(dhead);
    while (d != NULL)
    {
        if (d->d_name[0] == '.')
            goto ends;
        char temptarget[201];
        strcpy(temptarget, target);
        strcat(temptarget, "/");
        strcat(temptarget, d->d_name);
        char abspath[1001];
        strcpy(abspath, "");
        if (temptarget[0] == '.' && temptarget[1] != '.')
        {
            strcpy(abspath, directory);
            strcat(abspath, &temptarget[1]);
        }
        else if (temptarget[0] == '.' && temptarget[1] == '.')
        {
            chdir("..");
            char buf[101];
            getcwd(buf, sizeof(buf));
            chdir(directory);
            strcpy(abspath, buf);
            strcat(abspath, &temptarget[2]);
        }
        else
            strcat(abspath, temptarget);
        DIR *dir = opendir(abspath);
        if (dir != NULL)
        {
            closedir(dir);
            print_directories(temptarget, check);
        }
    ends:
        d = readdir(dhead);
    }
}
void print_files(char *target, int check)
{
    DIR *dhead = opendir(target);
    struct dirent *d = readdir(dhead);
    while (d != NULL)
    {
        if (d->d_name[0] == '.')
            goto ends;
        char temptarget[2001];
        strcpy(temptarget, target);
        strcat(temptarget, "/");
        strcat(temptarget, d->d_name);
        char abspath[1001];
        strcpy(abspath, "");
        if (temptarget[0] == '.' && temptarget[1] != '.')
        {
            strcpy(abspath, directory);
            strcat(abspath, &temptarget[1]);
        }
        else if (temptarget[0] == '.' && temptarget[1] == '.')
        {
            chdir("..");
            char buf[101];
            getcwd(buf, sizeof(buf));
            chdir(directory);
            strcpy(abspath, buf);
            strcat(abspath, &temptarget[2]);
        }
        else
            strcat(abspath, temptarget);
        DIR *dir = opendir(abspath);
        if (dir != NULL)
        {
            closedir(dir);
            print_files(temptarget, check);
        }
        else
        {
            if (check == 1)
            {
                char dup[301];
                strcpy(dup, "~");
                strcat(dup, &temptarget[strlen(mainname)]);
                printf("%s\n", dup);
            }
            else
                printf("%s\n", temptarget);
        }
    ends:
        d = readdir(dhead);
    }
}
void find_directories(char *target, char *name, int check)
{
    if (!strcmp(&target[strlen(target) - strlen(name)], name))
    {
        if (check == 1)
        {
            char dup[3001];
            strcpy(dup, "~");
            strcat(dup, &target[strlen(mainname)]);
            printf("%s\n", dup);
        }
        else
            printf("%s\n", target);
    }
    DIR *dhead = opendir(target);
    struct dirent *d = readdir(dhead);
    while (d != NULL)
    {
        if (d->d_name[0] == '.')
            goto ends;
        char temptarget[201];
        strcpy(temptarget, target);
        strcat(temptarget, "/");
        strcat(temptarget, d->d_name);
        char abspath[1001];
        strcpy(abspath, "");
        if (temptarget[0] == '.' && temptarget[1] != '.')
        {
            strcpy(abspath, directory);
            strcat(abspath, &temptarget[1]);
        }
        else if (temptarget[0] == '.' && temptarget[1] == '.')
        {
            chdir("..");
            char buf[1001];
            getcwd(buf, sizeof(buf));
            chdir(directory);
            strcpy(abspath, buf);
            strcat(abspath, &temptarget[2]);
        }
        else
            strcat(abspath, temptarget);
        DIR *dir = opendir(abspath);
        if (dir != NULL)
        {
            closedir(dir);
            find_directories(temptarget, name, check);
        }
    ends:
        d = readdir(dhead);
    }
}
void find_files(char *target, char *name, int check)
{
    DIR *dhead = opendir(target);
    struct dirent *d = readdir(dhead);
    while (d != NULL)
    {
        if (d->d_name[0] == '.')
            goto ends;
        char temptarget[201];
        strcpy(temptarget, target);
        strcat(temptarget, "/");
        strcat(temptarget, d->d_name);
        char abspath[1001];
        strcpy(abspath, "");
        if (temptarget[0] == '.' && temptarget[1] != '.')
        {
            strcpy(abspath, directory);
            strcat(abspath, &temptarget[1]);
        }
        else if (temptarget[0] == '.' && temptarget[1] == '.')
        {
            chdir("..");
            char buf[101];
            getcwd(buf, sizeof(buf));
            chdir(directory);
            strcpy(abspath, buf);
            strcat(abspath, &temptarget[2]);
        }
        else
            strcat(abspath, temptarget);
        DIR *dir = opendir(abspath);
        if (dir != NULL)
        {
            closedir(dir);
            find_files(temptarget, name, check);
        }
        else
        {
            if (!strcmp(d->d_name, name))
            {
                if (check == 1)
                {
                    char dup[301];
                    strcpy(dup, "~");
                    strcat(dup, &temptarget[strlen(mainname)]);
                    printf("%s\n", dup);
                }
                else
                    printf("%s\n", temptarget);
            }
        }
    ends:
        d = readdir(dhead);
    }
}
void print_discover(char *name, char *target, int d, int f, int check)
{
    if (name[0] == 0)
    {
        if (d == 1)
            print_directories(target, check);
        if (f == 1)
            print_files(target, check);
    }
    else
    {
        if (d == 1)
            find_directories(target, name, check);
        if (f == 1)
            find_files(target, name, check);
    }
}
void discover(char *rand, char *command)
{
    int tot = 0, d = 0, f = 0, namepresent = 0, dirpresent = 0;
    char commands[10][1001];
    char target[1001];
    char name[1001];
    name[0] = 0;
    target[0] = 0;
    command = strtok_r(NULL, " \t", &rand);
    int chk = 0;
    while (command != NULL)
    {
        strcpy(commands[tot], command);
        tot++;
        command = strtok_r(NULL, " \t", &rand);
    }
    int check = 0;
    for (int i = 0; i < tot; i++)
    {
        if (!strcmp(commands[i], "-d"))
            d = 1;
        else if (!strcmp(commands[i], "-f"))
            f = 1;
        else if (!strcmp(commands[i], "-fd") || !strcmp(commands[i], "-df"))
        {
            f = 1;
            d = 1;
        }
        else if (commands[i][0] == '"')
        {
            strcpy(name, &commands[i][1]);
            name[strlen(name) - 1] = 0;
            namepresent = 1;
        }
        else if (commands[i][0] == '~')
        {
            char abspath[2001];
            strcpy(abspath, mainname);
            strcat(abspath, &commands[i][1]);
            strcpy(target, abspath);
            chk = 1;
        }
        else
        {
            strcpy(target, commands[i]);
            dirpresent = 1;
        }
    }
    if (d == 0 && f == 0)
    {
        d = 1;
        f = 1;
    }
    if (target[0] == 0)
        strcpy(target, ".");
    print_discover(name, target, d, f, chk);
}