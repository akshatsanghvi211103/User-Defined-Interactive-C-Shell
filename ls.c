#include "lib.h"
#include "ls.h"
extern void reset();
int compare(const void *a, const void *b)
{
    const char **str_a = (const char **)a;
    const char **str_b = (const char **)b;
    return strcmp(*str_a, *str_b);
}
int compare2(const struct dirent **a, const struct dirent **b)
{
    int indexa = 0, indexb = 0;
    const struct dirent *str_a = *((const struct dirent **)a);
    const struct dirent *str_b = *((const struct dirent **)b);
    if (str_a->d_name[0] == '.')
        indexa = 1;
    if (str_b->d_name[0] == '.')
        indexb = 1;
    return strcmp(&(str_a->d_name[indexa]), &(str_b->d_name[indexb]));
}
char *convert(int p)
{
    int perm[10];
    if (p / 10000 == 3)
        printf("-");
    else
        printf("d");
    for (int i = 9; i > 0; i--)
    {
        perm[i] = p % 2;
        p /= 2;
    }
    if (perm[1])
        printf("r");
    else
        printf("-");
    if (perm[2])
        printf("w");
    else
        printf("-");
    if (perm[3])
        printf("x");
    else
        printf("-");
    if (perm[4])
        printf("r");
    else
        printf("-");
    if (perm[5])
        printf("w");
    else
        printf("-");
    if (perm[6])
        printf("x");
    else
        printf("-");
    if (perm[7])
        printf("r");
    else
        printf("-");
    if (perm[8])
        printf("w");
    else
        printf("-");
    if (perm[9])
        printf("x ");
    else
        printf("- ");
}
void ls_file(char *rand, char *name, int a, int l)
{
    struct stat stats;
    lstat(name, &stats);
    if (l == 1)
    {
        char link[1001];
        int linked = readlink(name, link, 1001);
        char *times = ctime(&stats.st_mtime);
        char display[101];
        strcpy(display, times);
        int seconds = time(NULL);
        display[strlen(times) - 9] = 0;
        int size = stats.st_size;
        int p = stats.st_rdev;
        if (S_ISBLK(stats.st_mode) || S_ISCHR(stats.st_mode))
            size = p;
        convert(stats.st_mode);
        printf("%ld ", stats.st_nlink);
        if (linked != -1)
        {
            if (stats.st_mode & S_IXUSR)
            {
                printf("%s %s %d %s \033[0;32m%s -> %s\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, name, link);
                reset();
            }
            else
                printf("%s %s %d %s %s -> %s\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, name, link);
        }
        else
        {
            if (stats.st_mode & S_IXUSR)
            {
                printf("%s %s %d %s \033[0;32m%s\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, name);
                reset();
            }
            else
                printf("%s %s %d %s %s\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, name);
        }
    }
    else
    {
        if (stats.st_mode & S_IXUSR)
        {
            printf("\033[0;32m%s\n", name);
            reset();
        }
        else
            printf("%s\n", name);
    }
}
void ls_directory(char *rand, char *name, int a, int l)
{
    struct dirent *d;
    DIR *dhead = opendir(name);
    d = readdir(dhead);
    struct stat stats;
    if (a == 0 && l == 0)
    {
        while (d != NULL)
        {
            if (d->d_name[0] != '.')
            {
                struct stat stats;
                lstat(d->d_name, &stats);
                DIR *dhead2 = opendir(d->d_name);
                if (dhead2 != NULL)
                {
                    printf("\033[0;31m%s\n", d->d_name);
                    reset();
                }
                else if (stats.st_mode & S_IXUSR)
                {
                    printf("\033[0;32m%s\n", d->d_name);
                    reset();
                }
                else
                    printf("%s\n", d->d_name);
            }
            d = readdir(dhead);
        }
    }
    else if (a == 1 && l == 0)
    {
        while (d != NULL)
        {
            struct stat stats;
            lstat(d->d_name, &stats);
            DIR *dhead2 = opendir(d->d_name);
            if (dhead2 != NULL)
            {
                printf("\033[0;31m%s\n", d->d_name);
                reset();
            }
            else if (stats.st_mode & S_IXUSR)
            {
                printf("\033[0;32m%s\n", d->d_name);
                reset();
            }
            else
                printf("%s\n", d->d_name);
            d = readdir(dhead);
        }
    }
    else if (a == 0 && l == 1)
    {
        int blocks = 0;
        struct dirent **q = &d;
        char list[1000][101];
        // int countlist = 0;
        int x = stat(d->d_name, &stats);
        int n = scandir(".", &q, 0, compare2);
        for (int i = 0; i < n; i++)
        {
            if (q[i]->d_name[0] == '.')
                continue;
            char link[1001];
            lstat(q[i]->d_name, &stats);
            int linked = readlink(q[i]->d_name, link, 1001);
            char *times = ctime(&stats.st_mtime);
            char display[101];
            strcpy(display, times);
            int seconds = time(NULL);
            display[strlen(times) - 9] = 0;
            int size = stats.st_size;
            int p = stats.st_rdev;
            if (S_ISBLK(stats.st_mode) || S_ISCHR(stats.st_mode))
                size = p;
            convert(stats.st_mode);
            printf("%ld ", stats.st_nlink);
            if (linked != -1)
            {
                DIR *dhead2 = opendir(q[i]->d_name);
                struct stat stats;
                lstat(q[i]->d_name, &stats);
                if (dhead2 != NULL)
                {
                    printf("%s %s %d %s \033[0;31m%s\033[0m -> %s\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, q[i]->d_name, link);
                }
                else if (stats.st_mode & S_IXUSR)
                {
                    printf("%s %s %d %s \033[0;32m%s\033[0m -> %s\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, q[i]->d_name, link);
                }
                else
                    printf("%s %s %d %s %s -> %s\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, q[i]->d_name, link);
            }
            else
            {
                DIR *dhead2 = opendir(q[i]->d_name);
                if (dhead2 != NULL)
                {
                    printf("%s %s %d %s \033[0;31m%s\033[0m\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, q[i]->d_name);
                    reset();
                }
                else if (stats.st_mode & S_IXUSR)
                {
                    printf("%s %s %d %s \033[0;32m%s\033[0m\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, q[i]->d_name);
                    reset();
                }
                else
                    printf("%s %s %d %s %s\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, q[i]->d_name);
            }
        }
    }
    else
    {
        struct dirent **q = &d;
        char list[1000][101];
        // int countlist = 0;
        int x = stat(d->d_name, &stats);
        int n = scandir(".", &q, 0, compare2);
        for (int i = 0; i < n; i++)
        {
            char link[1001];
            lstat(q[i]->d_name, &stats);
            int linked = readlink(q[i]->d_name, link, 1001);
            char *times = ctime(&stats.st_mtime);
            char display[101];
            strcpy(display, times);
            int seconds = time(NULL);
            display[strlen(times) - 9] = 0;
            int size = stats.st_size;
            int p = stats.st_rdev;
            if (S_ISBLK(stats.st_mode) || S_ISCHR(stats.st_mode))
                size = p;
            convert(stats.st_mode);
            printf("%ld ", stats.st_nlink);
            if (linked != -1)
            {
                DIR *dhead2 = opendir(q[i]->d_name);
                struct stat stats;
                lstat(q[i]->d_name, &stats);
                if (dhead2 != NULL)
                {
                    printf("%s %s %d %s \033[0;31m%s\033[0m -> %s\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, q[i]->d_name, link);
                }
                else if (stats.st_mode & S_IXUSR)
                {
                    printf("%s %s %d %s \033[0;32m%s\033[0m -> %s\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, q[i]->d_name, link);
                }
                else
                    printf("%s %s %d %s %s -> %s\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, q[i]->d_name, link);
            }
            else
            {
                DIR *dhead2 = opendir(q[i]->d_name);
                if (dhead2 != NULL)
                {
                    printf("%s %s %d %s \033[0;31m%s\033[0m\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, q[i]->d_name);
                    reset();
                }
                else if (stats.st_mode & S_IXUSR)
                {
                    printf("%s %s %d %s \033[0;32m%s\033[0m\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, q[i]->d_name);
                    reset();
                }
                else
                    printf("%s %s %d %s %s\n", getpwuid(stats.st_uid)->pw_name, getgrgid(stats.st_gid)->gr_name, size, display + 4, q[i]->d_name);
            }
        }
    }
}
void ls_flags(char *rand, char *command)
{
    int tot = 0, a = 0, l = 0, numdir = 0, numfiles = 0;
    char commands[10][1001];
    char directories[100][1001];
    char file[100][1001];
    command = strtok_r(NULL, " \t", &rand);
    while (command != NULL)
    {
        strcpy(commands[tot], command);
        tot++;
        command = strtok_r(NULL, " \t", &rand);
    }
    int check = 0;
    for (int i = 0; i < tot; i++)
    {
        if (!strcmp(commands[i], "-l"))
            l = 1;
        else if (!strcmp(commands[i], "-a"))
            a = 1;
        else if (!strcmp(commands[i], "-la") || !strcmp(commands[i], "-al"))
        {
            l = 1;
            a = 1;
        }
        else
        {
            DIR *directory = opendir(commands[i]);
            if (directory != NULL)
            {
                check = 1;
                closedir(directory);
                strcpy(directories[numdir++], commands[i]);
                // printf("directory\n");
            }
            else if (errno == ENOTDIR)
            {
                // printf("file\n");
                check = 1;
                strcpy(file[numfiles++], commands[i]);
            }
            else
            {
                check = 1;
                printf("ls: cannot access '%s': No such file or directory\n", commands[i]);
            }
        }
    }
    if (check == 0)
    {
        strcpy(directories[0], ".");
        numdir++;
    }
    // qsort(file, numfiles, sizeof(char *), compare);
    // qsort(directories, numdir, sizeof(char *), compare);
    // printf("%d\n", numdir);
    // printf("%d\n", numfiles);
    for (int i = 0; i < numfiles; i++)
    {
        ls_file(rand, file[i], a, l);
        printf("\n");
    }
    for (int i = 0; i < numdir; i++)
    {
        if (l == 1)
        {
            int sum = 0;
            char modifieddir[201];
            strcpy(modifieddir, "./");
            strcat(modifieddir, directories[i]);
            DIR *dhead = opendir(modifieddir);
            struct dirent *d = readdir(dhead);
            struct dirent **q = &d;
            int n = scandir(modifieddir, &q, 0, compare2);
            for (int j = 0; j < n; j++)
            {
                if (a == 0 && q[j]->d_name[0] == '.')
                    continue;
                struct stat stats;
                lstat(q[j]->d_name, &stats);
                sum += stats.st_blocks;
            }
            printf("total %d\n", sum / 2);
        }
        ls_directory(rand, directories[i], a, l);
        printf("\n");
    }
}