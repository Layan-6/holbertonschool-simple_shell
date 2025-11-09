#include "shell.h"

/**
 * execute_command - Executes a single command
 * @command: Command to execute
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	struct stat st;

	/* Check if file exists and is executable */
	if (stat(command, &st) == -1)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", command);
		return;
	}

	/* Check if it's executable */
	if (access(command, X_OK) == -1)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", command);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		/* Child process */
		char *args[] = {command, NULL};
		
		if (execve(command, args, environ) == -1)
		{
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		wait(&status);
	}
}
