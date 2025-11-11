#include "shell.h"

/**
 * get_path - Finds the full path of a command
 * @cmd: Command to find
 *
 * Return: Full path or NULL
 */
char *get_path(char *cmd)
{
    char *path = getenv("PATH");
    char *token, *full_path;
    struct stat st;

    if (!path)
        return (NULL);

    token = strtok(path, ":");
    while (token)
    {
        full_path = malloc(_strlen(token) + _strlen(cmd) + 2);
        if (!full_path)
            return (NULL);

        _strcpy(full_path, token);
        _strcat(full_path, "/");
        _strcat(full_path, cmd);

        if (stat(full_path, &st) == 0)
            return (full_path);

        free(full_path);
        token = strtok(NULL, ":");
    }
    return (NULL);
}
