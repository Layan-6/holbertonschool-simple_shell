#include "shell.h"

/**
 * execute_args - Executes command with arguments
 * @args: Array of arguments
 * @env: Environment variables
 *
 * Return: 1 to continue, 0 to exit
 */
int execute_args(char **args, char **env)
{
    pid_t pid;
    int status;
    struct stat st;

    /* Check for built-in commands */
    if (check_builtins(args, env) == 0)
        return (1);

    /* Check if command exists */
    if (stat(args[0], &st) == -1)
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
        return (1);
    }

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execve(args[0], args, env) == -1)
        {
            perror("./hsh");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        /* Fork failed */
        perror("./hsh");
    }
    else
    {
        /* Parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return (1);
}
