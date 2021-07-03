#include "minishell.h"

char    *quotes(char *buf)
{
    char *ptr;
    int i;
    int size;

    i = 0;
    size = ft_strlen(buf) + 3;
    ptr = malloc(sizeof(char) * size);
    while (buf[i - 1] != '=')
    {
        ptr[i] = buf[i];
        i++;
    }
    ptr[i++] = '"';
    while (buf[i - 1])
    {
        ptr[i] = buf[i - 1];
        i++;
    }
    ptr[i++] = '"';
    ptr[i] = '\0';
    return (ptr);
}

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
                swap = ft_strdup(buf[i]);
                buf[i] = buf[i + 1];
                buf[i + 1] = swap;
            }
            i++;
        }
    }
}

int     check_getsize(char **envp, int *ispwd, int *size)
{
    while (envp[*size])
    {
        if (*envp[*size] == 'O' && *(envp[*size] + 1) == 'L'&&
            *(envp[*size] + 2) == 'D' && *(envp[*size] + 3) == 'P' &&
            *(envp[*size] + 4) == 'W' && *(envp[*size] + 5) == 'D')
            *ispwd = 1;
        (*size)++;
    }
    return (*size);
}

void    printfbuf(char **buf)
{
    while (*buf)
    {
        *buf = ft_strdup(quotes(*buf));
        printf("declare -x %s\n", *buf);
        free(*buf);
        buf++;
    }
}

void    export(char **envp, char **argv)
{
    char **buf;
    int size;
    int i;
    int ispwd;

    size = 0;
    i = 0;
    ispwd = 0;
    printf("%s\n", *argv);
    check_getsize(envp, &ispwd, &size);
    if (ispwd == 0)
        buf = malloc(sizeof(char*) * (size + 2));
    if (ispwd == 1)
        buf = malloc(sizeof(char*) * (size + 1));
    while (envp[i++])
        buf[i - 1] = envp[i - 1];
    if (ispwd == 0)
    {
        buf = addoldpwd(buf, "OLDPWD", size);
        sort(buf, (size + 1));
    }
    else
        sort(buf, size);
    printfbuf(buf);
}
