#include "builtins.h"

char    **add_var(char **envp, char *var, int size)
{
	int     i;
	char    **new_envp;

	i = 0;
	new_envp = malloc(sizeof(char*) * (size + 2));
	while (i < size)
	{
		new_envp[i] = envp[i];
		i++;
	}
	free(envp);
	new_envp[i++] = var;
	new_envp[i] = NULL;
	return (new_envp);
}

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