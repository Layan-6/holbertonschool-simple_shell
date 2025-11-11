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
	int interactive = isatty(STDIN_FILENO);

	(void)argc;
	(void)argv;
	(void)env;

	shell_loop(interactive);
	return (0);
}

/**
 * shell_loop - Main shell loop
 * @interactive: Mode flag
 *
 * Return: void
 */
void shell_loop(int interactive)
{
	char *line;
	char **args;
	int status = 1;

	do {
		if (interactive)
			write(STDOUT_FILENO, "($) ", 4);

		line = read_line();
		if (line == NULL)
			break;

		args = split_line(line);
		if (args == NULL)
		{
			free(line);
			continue;
		}

		status = execute(args);

		free(line);
		free(args);
	} while (status);
}

/**
 * read_line - Reads input line
 *
 * Return: Line read or NULL
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t chars_read;

	chars_read = getline(&line, &bufsize, stdin);
	if (chars_read == -1)
	{
		free(line);
		return (NULL);
	}

	if (chars_read > 0 && line[chars_read - 1] == '\n')
		line[chars_read - 1] = '\0';

	return (line);
}

/**
 * split_line - Splits line into tokens
 * @line: Input line
 *
 * Return: Array of tokens
 */
char **split_line(char *line)
{
	int bufsize = TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		_puts("Allocation error\n");
		return (NULL);
	}

	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = _strdup(token);
		if (!tokens[position])
		{
			_puts("Allocation error\n");
			free(tokens);
			return (NULL);
		}
		position++;

		if (position >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				_puts("Allocation error\n");
				return (NULL);
			}
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * execute - Executes command
 * @args: Command arguments
 *
 * Return: 1 to continue, 0 to exit
 */
int execute(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
		return (1);

	if (_strcmp(args[0], "exit") == 0)
		return (shell_exit(args));
	if (_strcmp(args[0], "env") == 0)
		return (shell_env(args));
	if (_strcmp(args[0], "cd") == 0)
		return (shell_cd(args));
	if (_strcmp(args[0], "help") == 0)
		return (shell_help(args));

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("Error");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Error");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}
