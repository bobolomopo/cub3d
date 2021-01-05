#include "../include/cub3D.h"

int		ft_isin(char c, const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (-1);
}
