#include "shell.h"

/**
 * read_line - Reads a line from stdin
 *
 * Return: Pointer to the line read
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

    /* Remove newline character */
    if (line[chars_read - 1] == '\n')
        line[chars_read - 1] = '\0';

    return (line);
}
