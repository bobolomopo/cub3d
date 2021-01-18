#include "../include/cub3D.h"

void	*ft_memset(void *b, int c, unsigned int len)
{
	char	*a;
	size_t	i;

	a = (char *)b;
	i = 0;
	while (i < len)
	{
		a[i] = (char)c;
		i++;
	}
	return (b);
}

void	ft_bzero(void *s, unsigned int n)
{
	ft_memset(s, 0, n);
}