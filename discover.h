#if !defined(discover_h)
#define discover_h

void print_directories(char *target, int check);
void print_files(char *target, int check);
void find_directories(char *target, char *name, int check);
void find_files(char *target, char *name, int check);
void print_discover(char *name, char *target, int d, int f, int check);
void discover(char *rand, char *command);

#endif // discover_h
