#ifndef LIBFT_H
#define LIBFT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char    **ft_split(char const *s, char c);
char    *ft_substr(char const *s, unsigned int start, size_t len);
int     ft_strcmp(const char *s1, const char *s2);
char    *ft_strjoin(char const *s1, char const *s2);
size_t  ft_strlen(const char *s);
size_t  ft_strlcpy(char *dst, const char *src, size_t size);
char    *ft_strdup(const char *s1);

#endif
