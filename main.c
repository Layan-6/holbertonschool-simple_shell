#include "shell.h"

/**
 * main - Entry point of the shell
 * @ac: Argument count
 * @av: Argument vector
 * @env: Environment variables
 *
 * Return: Always 0
 */
int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    shell_loop(env);
    return (0);
}
