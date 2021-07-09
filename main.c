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

void    execute(char **argv, char **envp)
{
    int     i;
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
            continue;
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
            execute(argv, envp);
        free(buf);
        ft_free(argv);
    }
    free(buf);
    ft_free(envp);
    exit(EXIT_SUCCESS);
}
