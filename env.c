#include <stdio.h>

extern char **environ;

/**
 * print_env - تطبع جميع متغيرات البيئة الحالية
 */
void print_env(void)
{
    int i = 0;

    while (environ[i])
    {
        printf("%s\n", environ[i]);
        i++;
    }
}
