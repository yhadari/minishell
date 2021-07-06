#include "minishell.h"

int echo(char **argv)
{
    int i;
    int is_n;

    i = 1;
    is_n = 0;
    while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
    {
        i++;
        is_n++;
    }
    while (argv[i])
    {
        write(1, argv[i], ft_strlen(argv[i]));
        if (argv[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (is_n == 0)
        printf("\n");
    return (0);
}
