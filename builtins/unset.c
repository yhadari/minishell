#include "builtins.h"

int in_envp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0')
    {
        if (ft_strcmp(s1, s2) == 0)
            return (1);
		i++;
    }
    if (s1[i] == '=' && s2[i] == '\0')
        return (1);
    return (0);
}

int is_in_envp(char **envp, char *argv)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (in_envp(envp[i], argv))
            return (1);
        i++;
    }
    return (0);
}

char    **remove_var(char **envp, char *argv)
{
    int     size;
    int     i;
    char    **buf;

    i = 0;
    size = getsize(envp);
    buf = malloc(sizeof(char*) * size);
    while (!in_envp(envp[i], argv))
    {
        buf[i] = envp[i];
        i++;
    }
    free(envp[i]);
    while (envp[++i])
        buf[i - 1] = envp[i];
    buf[i - 1] = NULL;
    free(envp);
    return (buf);
}

char    **unset(char **envp, char **argv)
{
    int i;

    i = 0;
    if (argv[1])
    {
        while (argv[++i])
        {
            if (!valid_arg(argv[i], 'u'))
                    printf("unset: `%s': not a valid identifier\n", argv[i]);
            else
            {
                if (is_in_envp(envp, argv[i]))
                    envp = remove_var(envp, argv[i]);
            }
        }
    }
    return (envp);
}
