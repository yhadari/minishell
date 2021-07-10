#ifndef EXECUTE_H
#define EXECUTE_H

#include <sys/wait.h>
#include <sys/stat.h>
#include "../libft/libft.h"
#include "../builtins/builtins.h"

typedef struct  s_stat
{
    char        *cmd;
    char        *path_cmd;
    int         ret;
}               t_stat;

void    execute(char **argv, char **envp, int i);
void    ft_free(char **ptr);

#endif