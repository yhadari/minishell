#include "minishell.h"

char    *quotes(char *buf)
{
    char *ptr;
    int i;
    int size;

    i = 0;
    size = ft_strlen(buf) + 3;
    ptr = malloc(sizeof(char) * size);
    while (buf[i] && buf[i] != '=')
    {
        ptr[i] = buf[i];
        i++;
    }
    if (buf[i] == '=')
    {
        ptr[i++] = '=';
        ptr[i++] = '"';
        while (buf[i - 1])
        {
            ptr[i] = buf[i - 1];
            i++;
        }
        ptr[i++] = '"';
    }
    ptr[i] = '\0';
    return (ptr);
}

void    printfbuf(char **buf)
{
    char **tmp;

    tmp = buf;
    while (*buf)
    {
        *buf = quotes(*buf);
        printf("declare -x %s\n", *buf);
        free(*buf);
        buf++;
    }
    free(tmp);
}

void    show_export(char **envp, int size)
{
    char    **buf;
    int     i;

    i = -1;
    buf = malloc(sizeof(char*) * (size + 1));
    while (envp[++i])
        buf[i] = envp[i];
    buf[i] = NULL;
    sort(buf, size);
    printfbuf(buf);
}

char    **export(char **envp, char **argv)
{
    int size;
    int i;

    i = 0;
    size = getsize(envp);
    if (argv[1])
    {
        while (argv[++i])
        {
            if (!valid_arg(argv[i], 'e'))
                printf("export: `%s': not a valid identifier\n", argv[i]);
            else
            {
                if (!var_exist(envp, argv[i]))
                    envp = add_var(envp, ft_strdup(argv[i]), size++);
                else
                    envp = replace_var(envp, ft_strdup(argv[i]));
            }
        }
    }
    else
        show_export(envp, size);
    return (envp);
}
