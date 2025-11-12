cat > shell.c << 'EOF'
#include "shell.h"

/**
 * main - Entry point for simple shell
 * @argc: Argument count
 * @argv: Argument vector
 * @env: Environment variables
 *
 * Return: 0 on success
 */
int main(int argc, char **argv, char **env)
{
(void)argc;
(void)argv;
(void)env;

printf("Simple Shell Starting...\n");

return (0);
}
