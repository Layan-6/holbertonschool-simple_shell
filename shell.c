#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * shell_loop - Main loop of the shell
 * @av: Argument vector (used for shell name)
 * @env: Environment variables
 */
void shell_loop(char **av, char **env)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char **args;

    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);
        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            free(line);
            exit(0);
        }

        args = tokenize(line);
        if (args && args[0])
        {
            if (_strcmp(args[0], "env") == 0)
                print_env(env);
            else
                execute(args, av, env);
        }

        free(args);
    }
}
