#define _GNU_SOURCE
#include "shell.h"

extern char **environ;

/**
 * read_line - read a line from stdin using getline
 * Return: pointer to the line (malloc'd) or NULL on EOF
 */
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t nread;

    nread = getline(&line, &bufsize, stdin);
    if (nread == -1)
    {
        free(line);
        return (NULL);
    }
    return (line);
}

/**
 * split_line - split a line into tokens (whitespace separators)
 * @line: input line (will be modified)
 * Return: NULL-terminated array of pointers (malloc'd). Caller must free.
 */
char **split_line(char *line)
{
    int bufsize = 64;
    int position = 0;
    char **tokens = NULL;
    char *token = NULL;

    tokens = malloc(bufsize * sizeof(char *));
    if (tokens == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n");
    while (token != NULL)
    {
        tokens[position] = strdup(token);
        if (tokens[position] == NULL)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        position++;

        if (position >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (tokens == NULL)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n");
    }
    tokens[position] = NULL;
    return (tokens);
}

/**
 * launch - fork and exec the command
 * @args: NULL-terminated argument vector (args[0] is command)
 * Return: 1 to continue shell loop, 0 or exit handled by builtin
 */
int launch(char **args)
{
    pid_t pid;
    int status;
    int i;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (1);
    }
    if (pid == 0)
    {
        /* Child process */
        execvp(args[0], args);
        /* If execvp returns, there was an error */
        perror(args[0]);
        /* free child's copies of args before exit (not strictly necessary) */
        for (i = 0; args[i] != NULL; i++)
            free(args[i]);
        free(args);
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Parent process */
        do {
            if (waitpid(pid, &status, WUNTRACED) == -1)
            {
                perror("waitpid");
                return (1);
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return (1);
}

/**
 * execute - check for builtins and launch external programs
 * @args: arguments array
 * Return: 1 to continue loop, 0 to stop
 */
int execute(char **args)
{
    int i;

    if (args == NULL)
        return (1);
    if (args[0] == NULL)
        return (1);

    /* builtin: exit */
    if (strcmp(args[0], "exit") == 0)
    {
        /* free args before exiting */
        for (i = 0; args[i] != NULL; i++)
            free(args[i]);
        free(args);
        exit(0);
    }

    /* builtin: env */
    if (strcmp(args[0], "env") == 0)
    {
        for (i = 0; environ[i] != NULL; i++)
            puts(environ[i]);
        return (1);
    }

    /* otherwise launch external command */
    return (launch(args));
}

/**
 * loop_shell - main loop: prompt, read, parse, execute
 */
void loop_shell(void)
{
    char *line;
    char **args;
    int i;

    while (1)
    {
        fflush(stdout);
        printf("$ ");
        line = read_line();
        if (line == NULL)
        {
            /* EOF (Ctrl-D) */
            printf("\n");
            break;
        }

        /* if only newline, continue */
        if (line[0] == '\n')
        {
            free(line);
            continue;
        }

        args = split_line(line);
        /* free the original line; tokens are strdup'd so safe to free */
        free(line);

        /* if no args, free tokens array and continue */
        if (args[0] == NULL)
        {
            free(args);
            continue;
        }

        execute(args);

        /* free tokens after execution (if execute didn't exit) */
        for (i = 0; args[i] != NULL; i++)
            free(args[i]);
        free(args);
    }
}
