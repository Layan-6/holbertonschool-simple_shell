#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t n;

    while (1)
    {
        if (isatty(0))
            write(1, "($) ", 4);
        
        n = getline(&line, &len, stdin);
        if (n == -1)
        {
            if (isatty(0))
                write(1, "\n", 1);
            break;
        }
        
        if (n > 0 && line[n - 1] == '\n')
            line[n - 1] = '\0';
        
        if (strlen(line) == 0)
            continue;

        if (fork() == 0)
        {
            char *argv[] = {line, NULL};
            execve(line, argv, environ);
            fprintf(stderr, "./hsh: 1: %s: not found\n", line);
            exit(1);
        }
        else
        {
            wait(NULL);
        }
    }
    
    free(line);
    return (0);
}
