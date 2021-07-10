#include "builtins.h"

void	replace_oldpwd(char **envp, char *path, int i)
{
	int size;

	size = getsize(envp);
	while (i < size)
	{
		if (*envp[i] == 'O' && *(envp[i] + 1) == 'L'
			&& *(envp[i] + 2) == 'D' && *(envp[i] + 3) == 'P'
			&& *(envp[i] + 4) == 'W' && *(envp[i] + 5) == 'D')
			break ;
		else
			i++;
	}
	if (i < size)
	{
		free(envp[i]);
		envp[i] = ft_strjoin("OLDPWD=", path);
	}
}

void    new_pwd(char **envp, char *path, char *newpath)
{
	int i;
	int size;

	i = 0;
	size = getsize(envp);
	if (var_exist(envp, "PWD"))
	{
		while (*envp[i] != 'P' || *(envp[i] + 1) != 'W'
			|| *(envp[i] + 2) != 'D')
			i++;
		free(envp[i]);
		envp[i] = ft_strjoin("PWD=", newpath);
	}
	if (var_exist(envp, "OLDPWD"))
		replace_oldpwd(envp, path, i);
}

int	checkdir(char *argv)
{
	int		ret;

	if (argv)
	{
		ret = chdir(argv);
		if (ret != 0)
		{
			printf("minishell: cd: no such file or directory: %s\n", argv);
			return (1);
		}
	}
	return (0);
}

char	*cd_home(char **envp, char *path)
{
	int		i;
	char	*newpath;

	i = var_exist(envp, "HOME");
	if (i == 0)
	{
		printf("minishell: cd: HOME not set\n");
		return (NULL);
	}
    newpath = envp[i] + 5;
	new_pwd(envp, path, newpath);
	return (newpath);
}

char    **cd(char *argv, char **envp)
{
	char    *path;
	char    *newpath;

	path = malloc(100);
	getcwd(path, 1024);
	if (!argv)
	{
		newpath = cd_home(envp, path);
		checkdir(newpath);
	}
	else
	{
		if (!checkdir(argv))
		{
			newpath = malloc(100);
			getcwd(newpath, 1024);
			new_pwd(envp, path, newpath);
			free(newpath);
		}
	}
	free(path);
	return (envp);
}
