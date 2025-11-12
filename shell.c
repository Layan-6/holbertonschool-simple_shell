#include "shell.h"

/**
 * main - Entry point for simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *input;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			display_prompt();

		input = read_input();

		if (input == NULL)
		{
			if (interactive)
				printf("\n");
			break;
		}

		if (strlen(input) > 0)
		{
			execute_command(input);
		}

		free(input);
	}

	return (0);
}

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
	printf(":) ");
	fflush(stdout);
}

/**
 * read_input - Reads a line of input from user
 *
 * Return: Pointer to the input string
 */
char *read_input(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);

	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * trim_whitespace - Removes leading and trailing whitespace
 * @str: String to trim
 *
 * Return: Pointer to trimmed string
 */
char *trim_whitespace(char *str)
{
	char *end;

	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;

	if (*str == 0)
		return (str);

	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;

	*(end + 1) = '\0';

	return (str);
}

/**
 * parse_input - Splits input into command and arguments
 * @input: The input string
 * @arg_count: Pointer to store number of arguments
 *
 * Return: Array of arguments
 */
char **parse_input(char *input, int *arg_count)
{
	char **args = malloc(64 * sizeof(char *));
	char *token;
	int i = 0;

	if (!args)
		return (NULL);

	token = strtok(input, " ");
	while (token != NULL && i < 63)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	*arg_count = i;

	return (args);
}

/**
 * find_command_in_path - Finds command in PATH directories
 * @command: The command to find
 *
 * Return: Full path to command or NULL if not found
 */
char *find_command_in_path(char *command)
{
	char *path, *path_copy, *dir, *full_path;
	struct stat st;

	/* If command contains '/', check it directly */
	if (strchr(command, '/'))
	{
		if (stat(command, &st) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", dir, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * execute_command - Executes a command using execve
 * @input: The input string
 *
 * Return: 1 on success, 0 on failure
 */
int execute_command(char *input)
{
	pid_t pid;
	int status, arg_count;
	char **args;
	char *trimmed_input, *command_path;

	trimmed_input = trim_whitespace(input);

	if (strlen(trimmed_input) == 0)
		return (1);

	args = parse_input(trimmed_input, &arg_count);
	if (!args || !args[0])
	{
		if (args) free(args);
		return (0);
	}

	/* Find command in PATH */
	command_path = find_command_in_path(args[0]);
	if (!command_path)
	{
		printf("./shell: No such file or directory\n");
		free(args);
		return (0);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		free(command_path);
		free(args);
		return (0);
	}

	if (pid == 0)
	{
		if (execve(command_path, args, environ) == -1)
		{
			perror("./shell");
			free(command_path);
			free(args);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}

	free(command_path);
	free(args);
	return (1);
}
