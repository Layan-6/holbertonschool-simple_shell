#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_INPUT 1024

extern char **environ;

/* Function prototypes */
void display_prompt(void);
char *read_input(void);
void execute_command(char *command);

#endif /* SHELL_H */
