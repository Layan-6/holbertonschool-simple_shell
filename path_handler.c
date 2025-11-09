#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/**
 * find_command_path - Searches for command in PATH
 * @command: The command to search for
 *
 * Return: Full path if found, NULL otherwise
 */
char *find_command_path(char *command)
{
    char *path = getenv("PATH");
    char *token, *full_path;
    size_t len;

    if (!path)
        return (NULL);

    token = strtok(path, ":");
    while (token)
    {
        len = strlen(token) + strlen(command) + 2;
        full_path = malloc(len);
        if (!full_path)
            return (NULL);

        snprintf(full_path, len, "%s/%s", token, command);
        if (access(full_path, X_OK) == 0)
            return (full_path);

        free(full_path);
        token = strtok(NULL, ":");
    }
    return (NULL);
}
