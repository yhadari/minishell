#include "execute.h"

void    ft_free(char **ptr)
{
    int i;

    i = -1;
    while (ptr[++i])
        free(ptr[i]);
    free(ptr);
}

char    *get_path(char **envp)
{
    int i;

    i = var_exist(envp, "PATH");
    return (envp[i] + 5);
}

int     ft_stat(char **argv, char **path, int i)
{
    int     ret;
    struct  stat buf;
    char    *cmd;
    char    *path_cmd;

    cmd = ft_strjoin("/", *argv);
    path_cmd = ft_strjoin(path[i], cmd);
    ret = stat(path_cmd, &buf);
    free(cmd);
    free(path_cmd);
    return (ret);
}

void    execute(char **argv, char **envp, int i)
{
    char    **path;
    char    *env_path;
    t_stat  stat;

    i = -1;
    stat.ret = -1;
    env_path = get_path(envp);
    path = ft_split(env_path, ':');
    while (stat.ret != 0 && path[++i])
        stat.ret = ft_stat(argv, path, i);
    if (stat.ret == 0)
    {
        stat.cmd = ft_strjoin("/", *argv);
        stat.path_cmd = ft_strjoin(path[i], stat.cmd);
        i = fork();
        if(i == 0)
            execve(stat.path_cmd, argv, envp);
        else
            wait(NULL);
        free(stat.cmd);
        free(stat.path_cmd);
    }
    else
        printf("minishell: %s: command not found\n", *argv);
    ft_free(path);
}
