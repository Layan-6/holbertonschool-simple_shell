#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* Function prototypes */
void display_prompt(void);
char *read_input(void);
char *trim_whitespace(char *str);
char **parse_input(char *input, int *arg_count);
int execute_command(char *input);

#endif
