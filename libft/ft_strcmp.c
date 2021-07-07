#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*d2;

	d1 = (unsigned char*)s1;
	d2 = (unsigned char*)s2;
	i = 0;
	while (d1[i] - d2[i] == 0 && d1[i] != 0 && d2[i] != 0)
		i++;
	return (d1[i] - d2[i]);
}
