#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/**
 * main - Simple shell for task 0.1
 * Return: Always 0
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t pid;
    int status;
    struct stat st;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "($) ", 4);

        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        /* Remove newline */
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        /* Skip empty lines */
        if (strlen(line) == 0)
            continue;

        /* Check if command exists */
        if (stat(line, &st) == -1 || access(line, X_OK) == -1)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", line);
            continue;
        }

        pid = fork();
        if (pid == 0)
        {
            /* Child process */
            char *args[] = {line, NULL};
            execve(line, args, environ);
            perror("./hsh");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            /* Parent process */
            wait(&status);
        }
        else
        {
            perror("fork");
        }
    }

    free(line);
    return (0);
}
