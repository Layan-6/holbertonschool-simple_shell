
#ifndef SHELL_H
#define SHELL_H

extern char **environ;

void print_env(void);
char *find_command_path(char *command);

#endif
