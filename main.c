#include "shell.h"

int main(void)
{
    char command[1024];

    while (1)
    {
        printf("$ ");
        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        execute_command(command);
    }

    return 0;
}
