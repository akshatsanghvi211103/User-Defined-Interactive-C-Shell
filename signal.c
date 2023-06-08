#include "lib.h"
#include "signal.h"

void sig_handler(int signum)
{
    for (int i = 0; i < 1000; i++)
    {
        if (bgpid[i] == -1)
            continue;
        int status;
        if (waitpid(bgpid[i], &status, WNOHANG) != 0)
        {
            if (WIFEXITED(status))
            {
                printf("\n%s with pid %d exited normally\n", bgcommand[i], bgpid[i]);
                bgpid[i] = -1;
            }
            else
            {
                printf("\n%s with pid %d exited abnormally\n", bgcommand[i], bgpid[i]);
                bgpid[i] = -1;
            }
            num--;
        }
    }
}