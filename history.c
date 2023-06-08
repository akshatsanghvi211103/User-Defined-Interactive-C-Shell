#include "lib.h"
#include "history.h"

void add_to_history(char *command, char *username)
{
    char loc[1001];
    sprintf(loc, "/home/%s/history.txt", username);
    FILE *fp = fopen(loc, "r");
    if (fp == NULL)
    {
        FILE *fp2 = fopen(loc, "w");
        fprintf(fp2, "%s\n", command);
        fclose(fp2);
        return;
    }
    char history[20][1001];
    int count = 0;
    while (fgets(history[count], sizeof(history[count]), fp) != NULL)
    {
        history[count][strlen(history[count]) - 1] = 0;
        // printf("%s\n", history[count]);
        count++;
    }
    if (!strcmp(command, "") || !strcmp(command, history[count - 1]))
        return;
    if (count == 20)
    {
        for (int i = 1; i < 20; i++)
        {
            strcpy(history[i - 1], history[i]);
        }
        strcpy(history[count - 1], command);
    }
    else
        strcpy(history[count], command);
    fclose(fp);
    FILE *fp3 = fopen(loc, "w");
    fclose(fp3);
    FILE *fp2 = fopen(loc, "a");
    for (int i = 0; i < count + 1 && i < 20; i++)
    {
        // fputs(history[i], fp);
        fprintf(fp2, "%s\n", history[i]);
    }
    fclose(fp2);
}
void print_history(char *username)
{
    char loc[1001];
    sprintf(loc, "/home/%s/history.txt", username);
    FILE *fp = fopen(loc, "r");
    char s[1001];
    fseek(fp, 0, SEEK_END);
    int posn = ftell(fp);
    int count = 0;
    int check = 0;
    while (posn)
    {
        fseek(fp, --posn, SEEK_SET);
        if (fgetc(fp) == '\n')
        {
            if (count++ == 10)
            {
                check = 1;
                break;
            }
        }
    }
    if (check != 1)
        fseek(fp, -1, SEEK_CUR);
    while (fgets(s, sizeof(s), fp) != NULL)
        printf("%s", s);
    fclose(fp);
}