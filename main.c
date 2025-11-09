#include "shell.h"

/**
 * main - Entry point for simple shell
 * Return: Always 0
 */
int main(void)
{
	char *command;

	while (1)
	{
		display_prompt();
		command = read_input();
		
		if (command == NULL)
			break;

		if (strlen(command) > 0)
			execute_command(command);

		free(command);
	}

	return (0);
}
