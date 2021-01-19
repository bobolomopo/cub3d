/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:59:45 by jandre            #+#    #+#             */
/*   Updated: 2021/01/19 16:59:46 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
