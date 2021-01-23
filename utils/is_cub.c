/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:52:09 by jandre            #+#    #+#             */
/*   Updated: 2021/01/19 20:52:10 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		is_cub(char *str)
{
	int		i;
	int		j;
	char	test[5];

	test[0] = 'b';
	test[1] = 'u';
	test[2] = 'c';
	test[3] = '.';
	test[4] = '\0';
	i = ft_strlen(str) - 1;
	j = 0;
	while (test[j])
	{
		if (test[j] != str[i])
			return (-1);
		i--;
		j++;
	}
	return (1);
}
