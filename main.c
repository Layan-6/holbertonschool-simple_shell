#include "shell.h"

/**
 * main - Entry point of the shell
 * @ac: Argument count (unused)
 * @av: Argument vector (used to name the shell)
 * @env: Environment variables
 *
 * Return: Always 0 on success
 */
int main(int ac, char **av, char **env)
{
    (void)ac;

    shell_loop(av, env);
    return (0);
}
