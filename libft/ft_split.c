#include "libft.h"

static	int		numstr(const char *src, char sp)
{
	int i;
	int nb;
	int len;

	i = 0;
	nb = 0;
	len = ft_strlen(src) - 1;
	if (len == -1)
		return (0);
	if (src[i] == sp && src[len] == sp)
		nb--;
	if (src[i] != sp && src[len] != sp)
		nb++;
	while (src[i] != '\0')
	{
		if (src[i] == sp && src[i + 1] != sp)
			nb++;
		i++;
	}
	return (nb);
}

static	int		lenght(const char *src, char sp)
{
	int i;
	int lenght;

	i = 0;
	lenght = 0;
	while (src[i] == sp)
		i++;
	while (src[i] != sp && src[i] != '\0')
	{
		i++;
		lenght++;
	}
	return (lenght);
}

static	char	**freearr(char **s, int i)
{
	while (i > 0)
	{
		free(s[i - 1]);
		i--;
	}
	free(s);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	arr = malloc((numstr(s, c) + 1) * sizeof(char*));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < numstr(s, c))
	{
		while (s[i] == c)
			i++;
		arr[j] = ft_substr(s, i, lenght((s + i), c));
		if (!arr[j])
			return (freearr(arr, j));
		j++;
		i = i + lenght((s + i), c);
	}
	arr[j] = NULL;
	return (arr);
}
