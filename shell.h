#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Function prototypes */
void display_prompt(void);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args);
int check_builtins(char **args);

/* Built-in commands */
int shell_exit(char **args);
int shell_env(char **args);
int shell_cd(char **args);

#endif
