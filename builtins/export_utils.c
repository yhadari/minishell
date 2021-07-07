#include "minishell.h"

void    sort(char **buf, int size)
{
	int		i;
	int		index;
	char	*swap;

	i = 0;
    index = 0;
	while (size--)
    {
        i = 0;
        while (i < size)
        {
            if (ft_strcmp(buf[i], buf[i + 1]) > 0)
            {
                swap = buf[i];
                buf[i] = buf[i + 1];
                buf[i + 1] = swap;
            }
            i++;
        }
    }
}

int     valid_arg(char *argv, char c)
{
    int i;

    i = 0;
    if ((argv[i] < 65 || argv[i] > 90) &&
        (argv[i] < 97 || argv[i] > 122) && argv[i] != '_')
        return (0);
    while (argv[++i])
    {
        if ((argv[i] < 65 || argv[i] > 90) &&
            (argv[i] < 97 || argv[i] > 122) &&
            argv[i] != '_' && (argv[i] < 48 || argv[i] > 57) &&
            argv[i] != 61 && c == 'e')
            return (0);
        if ((argv[i] < 65 || argv[i] > 90) &&
            (argv[i] < 97 || argv[i] > 122) &&
            argv[i] != '_' && (argv[i] < 48 || argv[i] > 57) &&
            c == 'u')
            return (0);
    }
    return (1);
}

int is_var(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] - s2[i] == 0 && s1[i] != '\0' && s2[i] != '\0')
    {
        if ((s1[i] == '=' && s2[i] == '=') || ft_strcmp(s1, s2) == 0)
            return (1);
		i++;
    }
    if ((s1[i] == '=' && s2[i] == '\0') ||
        (s1[i] == '\0' && s2[i] == '='))
        return (1);
	return (0);
}

int     var_exist(char **envp, char *argv)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (is_var(envp[i], argv))
            return (1);
        i++;
    }
    return (0);
}

char    **replace_var(char **envp, char *argv)
{
    int i;

    i = 0;
    if (var_value(argv))
    {
        while (!is_var(envp[i], argv))
            i++;
        free(envp[i]);
        envp[i] = argv;
    }
    else
        free(argv);
    return (envp);
}