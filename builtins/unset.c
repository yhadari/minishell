#include "minishell.h"

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

    size = 0;
    i = 0;
    while (envp[size])
        size++;
    buf = malloc(sizeof(char*) * size);
    while (!in_envp(envp[i], argv))
    {
        buf[i] = envp[i];
        i++;
    }
    while (envp[++i])
        buf[i - 1] = envp[i];
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
            if (!valid_arg(argv[i]))
                    printf("unset: `%s': not a valid identifier\n", argv[i]);
            else
            {
                if (!is_in_envp(envp, argv[i]))
                    return (envp);
                else
                    envp = remove_var(envp, argv[i]);
            }
        }
    }
    // while (*envp)
    // {
    //     printf("%s\n", *envp);
    //     envp++;
    // }
    return (envp);
}

// int main(int argc, char **argv, char **envp)
// {
//     char *argv1[] = {"a.out", argv[1], argv[2], argv[3], NULL};
//     char *argv2[] = {"a.out", argv[4], NULL};
//     envp = export(envp, argv1);
//     unset(envp, argv2);
//     return (0);
// }