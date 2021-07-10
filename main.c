#include "minishell.h"

char    **ft_copy_env(char **envp)
{
    char **env;
    int size;

    size = getsize(envp);
    if (is_in_envp(envp, "OLDPWD"))
        env = malloc(sizeof(char*) * (size + 1));
    else
        env = malloc(sizeof(char*) * (size + 2));
    size = -1;
    while (envp[++size])
        env[size] = ft_strdup(envp[size]);
    if (!is_in_envp(envp, "OLDPWD"))
        env[size++] = ft_strdup("OLDPWD");
    env[size] = NULL;
    return (env);
}

int is_equal(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i])
    {
        if (s1[i] >= 65 && s1[i] <= 90)
            s1[i] += 32;
        i++;
    }
    if (ft_strcmp(s1, s2) == 0)
        return (1);
    return (0);
}

int main(int argc, char **argv, char **envp)
{
    char    *buf;
    int     i;

    envp = ft_copy_env(envp);
    i = argc;
    while (1)
    {
        write(0, "minishell$ ", 11);
        get_next_line(&buf);
        if(buf[0] == '\0' || ft_strcmp(buf, "\n") == 0)
        {
            free(buf);
            continue;
        }
        argv = ft_split(buf, ' ');
        if (ft_strcmp(*argv, "exit") == 0)
            break;
        else if (ft_strcmp(*argv, "cd") == 0)
            envp = cd(argv[1], envp);
        else if (ft_strcmp(*argv, "export") == 0)
            envp = export(envp, argv);
        else if (ft_strcmp(*argv, "unset") == 0)
            envp = unset(envp, argv);
        else if (is_equal(*argv, "pwd"))
            pwd();
        else if (is_equal(*argv, "echo"))
            echo(argv);
        else if (is_equal(*argv, "env"))
            env(envp);
        else
            execute(argv, envp, i);
        free(buf);
        ft_free(argv);
    }
    free(buf);
    ft_free(envp);
    exit(EXIT_SUCCESS);
}
