/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 19:25:49 by jandre            #+#    #+#             */
/*   Updated: 2020/10/16 19:26:09 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		ft_nbrlen(int n)
{
	size_t	i;
	long	nbr;

	nbr = (long)n;
	i = 1;
	if (nbr < 0)
	{
		i++;
		nbr = nbr * -1;
	}
	while (nbr >= 10)
	{
		i++;
		nbr /= 10;
	}
	return (i);
}
