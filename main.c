#include "builtins/minishell.h"

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

int main(int argc, char **argv, char **envp)
{
    char *buf;
    int i;

    envp = ft_copy_env(envp);
    i = argc;
    while (1)
    {
        write(0, "$ ", 2);
        get_next_line(&buf);
        if(buf[0] == '\0' || ft_strcmp(buf, "\n") == 0)
            continue;
        argv = ft_split(buf, ' ');
        if (ft_strcmp(*argv, "exit") == 0)
            break;
        if (ft_strcmp(*argv, "pwd") == 0)
            pwd();
        if (ft_strcmp(*argv, "cd") == 0)
            envp = cd(argv[1], envp);
        if (ft_strcmp(*argv, "echo") == 0)
            echo(argv);
        if (ft_strcmp(*argv, "env") == 0)
            env(envp);
        if (ft_strcmp(*argv, "export") == 0)
            envp = export(envp, argv);
        if (ft_strcmp(*argv, "unset") == 0)
            envp = unset(envp, argv);
        free(buf);
        i = -1;
        while (argv[++i])
            free(argv[i]);
        free(argv);
    }
    free(buf);
    i = -1;
    while (envp[++i])
        free(envp[i]);
    free(envp);
    exit(EXIT_SUCCESS);
}
