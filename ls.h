#if !defined(ls_h)
#define ls_h

int compare(const void *a, const void *b);
int compare2(const struct dirent **a, const struct dirent **b);
char *convert(int p);
void ls_file(char *rand, char *name, int a, int l);
void ls_directory(char *rand, char *name, int a, int l);
void ls_flags(char *rand, char *command);

#endif // ls_h
