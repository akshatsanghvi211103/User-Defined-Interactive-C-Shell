#include "lib.h"
#include "pinfo.h"
void pinfo(int pid)
{
    char b[1001];
    char buf[1001];
    char buf2[1001];
    char buf3[1001];
    char buf4[1001];
    printf("pid: %d\n", pid);
    sprintf(b, "/proc/%d", pid);
    if (chdir(b) == -1)
    {
        printf("Process non-existant!\n");
        return;
    }
    chdir(directory);
    sprintf(buf2, "/proc/%d/exe", pid);
    sprintf(buf3, "/proc/%d/status", pid);
    sprintf(buf4, "/proc/%d/stat", pid);
    FILE *fp = fopen(buf3, "r");
    FILE *fp2 = fopen(buf4, "r");
    char read[1001];
    char status[1001];
    char readstat[1001];
    int vmem;
    while (fscanf(fp, "%s", read) != EOF)
    {
        if (!strcmp(read, "State:"))
        {
            fscanf(fp, "%s", status);
        }
        if (!strcmp(read, "VmSize:"))
        {
            fscanf(fp, "%d", &vmem);
            break;
        }
    }
    char plus1[1001];
    char plus2[1001];
    for (int i = 1; i <= 8; i++)
    {
        fscanf(fp2, "%s", readstat);
        if (i == 5)
            strcpy(plus1, readstat);
        if (i == 8)
        {
            strcpy(plus2, readstat);
            break;
        }
    }
    char plus[2];
    strcpy(plus, "");
    // printf("%s %s\n", plus1, plus2);
    if (!strcmp(plus1, plus2))
        strcat(plus, "+");
    printf("process Status: %s%s\n", status, plus);
    printf("memory: %d kb {Virtual Memory}\n", vmem);
    if (readlink(buf2, buf, sizeof(buf)) == -1)
        printf("No executable path\n");
    else
        printf("executable path: %s\n", buf);
}