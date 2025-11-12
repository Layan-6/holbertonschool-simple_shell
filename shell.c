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
	printf("#cisfun$ ");
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

	/* Remove newline character */
	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * execute_command - Executes a command using execve
 * @command: The command to execute
 *
 * Return: 1 on success, 0 on failure
 */
int execute_command(char *command)
{
	pid_t pid;
	int status;
	char *args[2];

	args[0] = command;
	args[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (0);
	}

	if (pid == 0)
	{
		/* Child process */
		if (execve(command, args, environ) == -1)
		{
			printf("./shell: No such file or directory\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		wait(&status);
	}

	return (1);
}
