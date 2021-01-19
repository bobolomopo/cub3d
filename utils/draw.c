/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:16:06 by jandre            #+#    #+#             */
/*   Updated: 2021/01/16 16:16:07 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_ceil_floor(int width, int height)
{
	int x;
	int y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height / 2)
		{
			my_mlx_pixel_put(&g_param.game, x, y, g_param.ceiling_color);
			y++;
		}
		while (y < height)
		{
			my_mlx_pixel_put(&g_param.game, x, y, g_param.floor_color);
			y++;
		}
		x++;
	}
}
