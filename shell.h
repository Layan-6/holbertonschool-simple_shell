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
char *_getenv(const char *name);
char *find_command_in_path(char *command);
void print_environment(void);
int check_builtin(char **args, int *exit_shell);
int execute_command(char *input, int *exit_shell);

#endif
