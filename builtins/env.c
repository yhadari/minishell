#include "minishell.h"

int     var_value(char *envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (envp[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

void    env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (var_value(envp[i]))
            printf("%s\n", envp[i]);
        i++;
    }
}