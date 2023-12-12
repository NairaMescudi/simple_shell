#include "shell.h"

void printenv(void)
{
        int i = 0;

        while (environ[i] != NULL)
        {
                printf("%s\n", environ[i]);
                ++i;
        }
}
