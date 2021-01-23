/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 12:53:30 by jandre            #+#    #+#             */
/*   Updated: 2021/01/08 12:53:34 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int		ft_isin_str(char *str, char *str2)
{
	int	i;
	int	j;

	i = 0;
	while (str2[i])
	{
		printf("ok\n");
		j = 0;
		while (str[j])
		{
			if (str2[i] == str[j])
				return (1);
			j++;
		}
		i++;
	}
	
	return (-1);
}

void	doublefree(char *str, char *str2)
{
	free(str);
	free(str2);
}
