#include "shell.h"

/**
 * check_builtins - Checks for built-in commands
 * @args: Command arguments
 * @env: Environment variables
 * Return: 1 if builtin handled, 0 otherwise
 */
int check_builtins(char **args, char **env)
{
    (void)env; 

    if (strcmp(args[0], "exit") == 0)
    {
        exit_shell(args);
        return (1);
    }
    else if (strcmp(args[0], "env") == 0)
    {
        print_env(env);
        return (1);
    }

    return (0);
}

/**
 * exit_shell - Exits the shell
 * @args: Command arguments
 */
void exit_shell(char **args)
{
    (void)args; /* إذا لم تستخدم args */
    exit(EXIT_SUCCESS);
}

/**
 * print_env - Prints environment variables
 * @env: Environment variables
 */
void print_env(char **env)
{
    int i = 0;

    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }
}
