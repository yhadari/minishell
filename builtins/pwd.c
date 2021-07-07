#include "minishell.h"

void    pwd()
{
    char *path;

    path = malloc(100);
    getcwd(path, 1024);
    printf("%s\n", path);
    free(path);
}
