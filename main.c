#include "builtins/minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *buf;
    int i;

    i = argc;
    buf = malloc(1024);
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
        {
            pwd();
            continue;
        }
        if (ft_strcmp(*argv, "cd") == 0)
        {
            envp = cd(argv[1], envp);
            continue;
        }
        if (ft_strcmp(*argv, "echo") == 0)
        {
            echo(argv);
            continue;
        }
        if (ft_strcmp(*argv, "env") == 0)
        {
            env(envp);
            continue;
        }
        if (ft_strcmp(*argv, "export") == 0)
        {
            export(envp, argv);
            continue;
        }
        free(buf);
    }
    free(buf);
    exit(EXIT_SUCCESS);
}
