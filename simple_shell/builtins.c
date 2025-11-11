#include "shell.h"

/**
 * shell_exit - Exit builtin
 * @args: Arguments
 *
 * Return: 0 to exit
 */
int shell_exit(char **args)
{
	(void)args;
	return (0);
}

/**
 * shell_env - Print environment
 * @args: Arguments
 *
 * Return: 1 to continue
 */
int shell_env(char **args)
{
	extern char **environ;
	char **env = environ;

	(void)args;

	while (*env)
	{
		_puts(*env);
		_putchar('\n');
		env++;
	}
	return (1);
}

/**
 * shell_cd - Change directory
 * @args: Arguments
 *
 * Return: 1 to continue
 */
int shell_cd(char **args)
{
	char *dir = args[1];
	char cwd[BUFSIZE];

	if (dir == NULL)
	{
		dir = _getenv("HOME");
		if (dir == NULL)
		{
			_puts("cd: HOME not set\n");
			return (1);
		}
	}

	if (chdir(dir) != 0)
	{
		perror("cd");
		return (1);
	}

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		setenv("PWD", cwd, 1);
	else
		perror("getcwd");

	return (1);
}

/**
 * shell_help - Help builtin
 * @args: Arguments
 *
 * Return: 1 to continue
 */
int shell_help(char **args)
{
	(void)args;

	_puts("Simple Shell Help\n");
	_puts("Builtins: cd, exit, env, help\n");
	return (1);
}
