#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Function prototypes */
void shell_loop(char **env);
char *read_line(void);
char **parse_line(char *line);
int execute_args(char **args, char **env);
int check_builtins(char **args, char **env);

/* Built-in functions */
void exit_shell(char **args);
void print_env(char **env);

#endif /* SHELL_H */
