#include "shell.h"

/**
 * display_prompt - Displays shell prompt
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "($) ", 4);
}

/**
 * read_input - Reads user input
 * Return: Input string or NULL on EOF
 */
char *read_input(void)
{
	char *input = NULL;
	size_t size = 0;
	ssize_t chars_read;

	chars_read = getline(&input, &size, stdin);

	if (chars_read == -1)
	{
		free(input);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		return (NULL);
	}

	/* Remove newline character */
	if (input[chars_read - 1] == '\n')
		input[chars_read - 1] = '\0';

	return (input);
}
