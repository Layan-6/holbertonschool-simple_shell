#include "shell.h"

/**
 * execute_args - Executes command with arguments
 * @args: Command arguments
 * @env: Environment variables
 * Return: 1 to continue, 0 to exit
 */
int execute_args(char **args, char **env)
{
    pid_t pid;
    int status;
    char *command_path;

    /* Check for built-in commands */
    if (check_builtins(args, env) == 1)
        return (1);

    /* Find command path */
    command_path = find_command_path(args[0]);
    if (!command_path)
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
        return (1);
    }

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execve(command_path, args, env) == -1)
        {
            perror("./hsh");
            free(command_path);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        /* Fork failed */
        perror("./hsh");
        free(command_path);
    }
    else
    {
        /* Parent process */
        wait(&status);
        free(command_path);
    }

    return (1);
}
