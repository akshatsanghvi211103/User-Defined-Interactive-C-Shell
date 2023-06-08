#include "lib.h"
#include "prompt.h"
extern void reset();
void prompt()
{
    gethostname(hostname, 2001);
    getcwd(directory, sizeof(directory));
    int chk = strncmp(directory, mainname, size);
    if (chk == 0 && times >= 1)
        printf("\033[1;36m<%s@%s:\033[1;33m~%stook %ds> ", getlogin(), hostname, &directory[size], times);
    else if (chk == 0 && times < 1)
        printf("\033[1;36m<%s@%s:\033[1;33m~%s> ", getlogin(), hostname, &directory[size]);
    else if (chk != 0 && times >= 1)
        printf("\033[1;36m<%s@%s:\033[1;33m%stook %ds> ", getlogin(), hostname, directory, times);
    else if (chk != 0 && times < 1)
        printf("\033[1;36m<%s@%s:\033[1;33m%s> ", getlogin(), hostname, directory);
    reset();
}