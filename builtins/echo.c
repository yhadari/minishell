#include "builtins.h"

int option(char *argv)
{
    int i;

    i = 0;
    if (ft_strcmp(argv, "-n") == 0)
        return (1);
    while (argv[i])
    {
        if (argv[i] == '-' && argv[i + 1] == 'n')
        {
            while (argv[++i])
                if (argv[i] != 'n')
                    return (0);
        }
        else
            return (0);
    }
    return (1);
}

int echo(char **argv)
{
    int i;
    int is_n;

    i = 1;
    is_n = 0;
    while (argv[i] && option(argv[i]))
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
