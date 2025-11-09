#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* Function prototypes - جميع الدوال يجب أن تكون معرفة هنا */
void shell_loop(char **env);
char *read_line(void);
char **parse_line(char *line);
int execute_args(char **args, char **env);
char *find_command_path(char *command);
void exit_shell(char **args);
void print_env(char **env);
int check_builtins(char **args, char **env);

#endif /* SHELL_H */
