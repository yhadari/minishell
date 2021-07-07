#ifndef MINISHELL_H
#define MINISHELL_H

#include <errno.h>
#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"

void    pwd();
char    **cd(char *argv, char **envp);
int     echo(char **argv);
void    env(char **envp);
char    **export(char **envp, char **argv);
char    **unset(char **envp, char **argv);
char    **add_var(char **envp, char *oldpath, int size);
int     var_value(char *envp);
int     is_var(char *s1, char *s2);
int     var_exist(char **envp, char *argv);
char    **replace_var(char **envp, char *argv);
void    sort(char **buf, int size);
int     valid_arg(char *argv, char c);
int     getsize(char **envp);
int     is_in_envp(char **envp, char *argv);

#endif
