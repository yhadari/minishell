#ifndef MINISHELL_H
#define MINISHELL_H

#include <errno.h>
#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"

void    pwd();
char    **cd(char *argv, char **envp);
int     echo(char **argv);
void    env(char **envp);
void    export(char **envp, char **argv);
char    **addoldpwd(char **envp, char *oldpath, int size);

#endif
