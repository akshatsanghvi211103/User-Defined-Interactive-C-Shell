# OSN ASSIGNMENT 2: BUILDING A SHELL
## Roll No.: 2021101094
## Name: Akshat Sanghvi
## General Assumptions
> Run the command "make" and then "./a.out" to get the terminal interface.
Tabs, spaces and semicolons have been handled in all the required commands.
Assumed size of commands to not be greater than size = 100.
### shell.c
> Has the main function.
> Handles assigning and running foreground and background processes.
> Also handles the timing of the foreground processes.
### cd.c
> Outputs "OLDPWD not set" in case  the directory hasn't been changed till now (as in bash, but not in zsh).
### discover.c
> Handled the ~ case.
Assumed any order of arguments
Have used opendir functionality.
### echo.c
> Removed the extra space at the end of the output and handled spaces and tabs.
Did not handle escape sequences and quotes (printed as such).
### err.c
> Handled the "too many arguments" error in this file
### history.c
> History file is in the home directory. 
> Max 20 commands stored in history.txt.
> Commands with extra spaces is not considered same. i.e., "command" and "command " written consecutively are both stored (just like in bash).
### ls.c
> If the direcctory is also having executing permissions, it has the same color as the other directories (not coloured as executables).
> Used scandir for scanning the directories.
### pinfo.c
> All info is taken from /proc/pid directory.
> Error handling is done for non-existant processes and also for non-executable processes.
### prompt.c
> Handles colouring of the prompt and outputs the time taken by the processes (if time >= 1s).
### pwd.c
> Used getcwd function.
> Have handled the case of too many arguments for pwd, as in zsh it gives an error but in bash it doesn't.
### reset.c
> Just resets the color of the output to the default color of the terminal.
### signal.c
> Handles the signals recieved when the child process gets over.