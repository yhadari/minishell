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
    char **tmp;

    tmp = buf;

    while (*buf)
    {
        *buf = quotes(*buf);
        printf("declare -x %s\n", *buf);
        buf++;
    }
    free(tmp);
}

char    **export(char **envp, char **argv)
{
    char **buf;
    int size;
    int i;
    int ispwd;

    i = 0;
    size = 0;
    ispwd = 0;
    check_getsize(envp, &ispwd, &size);
    if (argv[1])
    {
        while (argv[++i])
        {
            if (!valid_arg(argv[i]))
                printf("export: `%s': not a valid identifier\n", argv[i]);
            else
            {
                if (!var_exist(envp, argv[i]))
                {
                    envp = add_var(envp, argv[i], size);
                    size++;
                }
                else
                    envp = replace_var(envp, argv[i]);
            }
        }
    }
    i = 0;
    if (ispwd == 0)
        buf = malloc(sizeof(char*) * (size + 2));
    if (ispwd == 1)
        buf = malloc(sizeof(char*) * (size + 1));
    while (envp[i++])
        buf[i - 1] = envp[i - 1];
    if (ispwd == 0)
    {
        buf = add_var(buf, "OLDPWD", size);
        sort(buf, (size + 1));
    }
    else
        sort(buf, size);
    if (!argv[1])
        printfbuf(buf);
    // else
    // {
    //     while (*buf)
    //     {
    //         printf("%s\n", *buf);
    //         buf++;
    //     }
    //     return (buf);
    // }
    return (envp);
}

// int main(int argc, char **argv, char **envp)
// {
//     export(envp, argv);
//     return (0);
// }