#include "shell.h"

/**
 * shell_loop - Main shell loop
 * @env: Environment variables
 */
void shell_loop(char **env)
{
    char *line;
    char **args;
    int status = 1;

    while (status)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "($) ", 4);

        line = read_line();
        if (line == NULL)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        args = parse_line(line);
        if (args[0] != NULL)
            status = execute_args(args, env);

        free(line);
        free(args);
    }
}
