#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stddef.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

void shell_loop(int interactive);
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_env(char **args);
int _putchar(char c);
void _puts(char *str);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *_getenv(const char *name);

#endif
