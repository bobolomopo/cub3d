/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_managing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:46:49 by jandre            #+#    #+#             */
/*   Updated: 2021/01/16 16:46:50 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void		sprite_value(t_sprite *sprite)
{
	int x;
	int	y;
	int i;

	x = 0;
	i = 0;
	while (x < g_param.map_h)
	{
		y = 0;
		while (g_param.map[x][y])
		{
			if (g_param.map[x][y] == '2')
			{
				sprite[i].x = x + 0.5;
				sprite[i].y = y + 0.5;
				sprite[i].text = textures[4];
				i++;
			}
			y++;
		}
		x++;
	}
}

void		sortsprite(int *sprite_order, double *sprite_distance,
						int numsprite)
{
	int		i;
	int		j;
	double	temp;
	double	temp2[numsprite];

	i = -1;
	while (++i < numsprite)
		temp2[i] = sprite_distance[i];
	i = -1;
	while (++i < numsprite)
	{
		temp = temp2[i];
		j = -1;
		while (++j < numsprite)
		{
			if (temp < temp2[j])
			{
				temp = temp2[j];
				sprite_order[i] = j;
			}
		}
		temp2[sprite_order[i]] = 0;
	}
}
