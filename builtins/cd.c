#include "minishell.h"

char    **addoldpwd(char **envp, char *oldpath, int size)
{
    int     i;
    char    **new;

    i = 0;
    new = malloc(sizeof(char*) * (size + 2));
    while (i < size)
    {
        new[i] = ft_strdup(envp[i]);
        i++;
    }
    new[i++] = ft_strdup(oldpath);
    new[i] = NULL;
    return (new);
}

int    getsize(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        i++;
    return (i);
}

int checkdir(char *argv)
{
    int ret;

    ret = chdir(argv);
    if (ret != 0)
    {
        printf("cd: no such file or directory: %s\n", argv);
        return (1);
    }
    return (0);
}

char    **new_pwd(char **envp, char *path, char *newpath)
{
    int i;
    int size;

    size = getsize(envp);
    i = 0;
    while (*envp[i] != 'P' || *(envp[i] + 1) != 'W' || *(envp[i] + 2) != 'D')
        i++;
    ft_strlcpy(envp[i], ft_strjoin("PWD=", newpath), ft_strlen(newpath)+5);
     while (i < size)
     {
        if (*envp[i] == 'O' && *(envp[i] + 1) == 'L' && *(envp[i] + 2) == 'D' &&
            *(envp[i] + 3) == 'P' && *(envp[i] + 4) == 'W' && *(envp[i] + 5) == 'D')
                break ;
        else
            i++;
     }
    if (i < size)
        ft_strlcpy(envp[i], ft_strjoin("OLDPWD=", path), ft_strlen(path)+8);
    else
        envp = addoldpwd(envp, ft_strjoin("OLDPWD=", path), size);
    free(path);
    free(newpath);
    return (envp);
}

char    **cd(char *argv, char **envp)
{
    char    *path;
    char    *newpath;

    path = malloc(100);
    getcwd(path, 1024);
    if (checkdir(argv))
        return (envp);
    newpath = malloc(100);
    getcwd(newpath, 1024);
    return (new_pwd(envp, path, newpath));
}
