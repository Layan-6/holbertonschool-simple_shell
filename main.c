#include "shell.h"

/**
 * main - Entry point
 * @argc: Argument count
 * @argv: Argument vector
 * @env: Environment variables
 * Return: 0 on success
 */
int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;

    shell_loop(env);
    return (0);
}
