#include "shell.h"

/**
 * print_env - Prints the environment variables
 * @env: Array of environment variable strings
 */
void print_env(char **env)
{
    int i = 0;

    while (env[i])
    {
        write(STDOUT_FILENO, env[i], _strlen(env[i]));
        write(STDOUT_FILENO, "\n", 1);
        i++;
    }
}
