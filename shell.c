#include "shell.h"

/**
 * shell_loop - Main loop of the shell
 * @env: Environment variables
 */
void shell_loop(char **env)
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
        if (args[0] != NULL)
            execute(args, env);

        free(args);
    }
}
