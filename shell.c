#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char *command)
{
    pid_t pid;
    int status;
    char *argv[64];
    char *token;
    int i = 0;

    token = strtok(command, " \n");
    while (token != NULL)
    {
        argv[i++] = token;
        token = strtok(NULL, " \n");
    }
    argv[i] = NULL;

    if (argv[0] == NULL)
        return;

    if (strcmp(argv[0], "exit") == 0)
        exit(0);

    pid = fork();
    if (pid == 0)
    {
        execvp(argv[0], argv);
        perror("Error");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        wait(&status);
    }
    else
    {
        perror("fork");
    }
}
