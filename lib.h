#if !defined(lib_h)
#define lib_h

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
extern char mainname[2001];
extern char username[2001];
extern char hostname[2001];
extern char command[2001];
extern char directory[2001];
extern char prevdir[2001];
extern int count;
extern int size;
extern int numbg;
extern int num;
extern int times;
extern int bgpid[1000];
extern char bgcommand[1000][201];

#endif // lib_h