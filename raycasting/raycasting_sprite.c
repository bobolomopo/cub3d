/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:06:31 by jandre            #+#    #+#             */
/*   Updated: 2021/01/19 16:06:33 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void			raycasting_sprite_init(t_sprite *sprite, int *sprite_order,
									int i)
{
	g_param.sprite_x = sprite[sprite_order[i]].x - g_param.pos_x;
	g_param.sprite_y = sprite[sprite_order[i]].y - g_param.pos_y;
	g_param.inv_det = 1.0 / (g_param.plane_x * g_param.dir_y -
		g_param.dir_x * g_param.plane_y);
	g_param.transform_x = g_param.inv_det * (g_param.dir_y * g_param.sprite_x
		- g_param.dir_x * g_param.sprite_y);
	g_param.transform_y = g_param.inv_det * (g_param.plane_x * g_param.sprite_y
		- g_param.plane_y * g_param.sprite_x);
	g_param.sprite_screen_x = (int)((g_param.res_x / 2) * (1 +
	(g_param.transform_x / g_param.transform_y)));
	g_param.sprite_height = abs((int)((g_param.res_y / (g_param.transform_y))));
	g_param.draw_start_y = -g_param.sprite_height / 2 + g_param.res_y / 2;
	if (g_param.draw_start_y < 0)
		g_param.draw_start_y = 0;
	g_param.draw_end_y = g_param.sprite_height / 2 + g_param.res_y / 2;
	if (g_param.draw_end_y >= g_param.res_y)
		g_param.draw_end_y = g_param.res_y - 1;
	g_param.sprite_width = abs((int)(g_param.res_y / (g_param.transform_y)));
	g_param.draw_start_x = -g_param.sprite_width / 2 +
	g_param.sprite_screen_x;
	if (g_param.draw_start_x < 0)
		g_param.draw_start_x = 0;
	g_param.draw_end_x = g_param.sprite_width / 2 + g_param.sprite_screen_x;
	if (g_param.draw_end_x >= g_param.res_x)
		g_param.draw_end_x = g_param.res_x - 1;
}

static void		raycasting_sprite_draw2(int stripe, double *z_buffer)
{
	int		tex_x;
	int		tex_y;
	int		d;
	int		y;
	int		color;

	tex_x = (int)(256 * (stripe - (-g_param.sprite_width / 2 +
			g_param.sprite_screen_x)) * g_param.textures[4].width /
			g_param.sprite_width) / 256;
	if (g_param.transform_y > 0 && stripe > 0 && stripe < g_param.res_x &&
		g_param.transform_y < z_buffer[stripe])
	{
		y = g_param.draw_start_y;
		while (y < g_param.draw_end_y)
		{
			d = y * 256 - g_param.res_y * 128 + g_param.sprite_height * 128;
			tex_y = ((d * g_param.textures[4].height) /
				g_param.sprite_height) / 256;
			color = get_tex_color(&g_param.textures[4], tex_x, tex_y);
			if (color != 0)
				my_mlx_pixel_put(&g_param.game, stripe, y, color);
			y++;
		}
	}
}

void			raycasting_sprite_draw(double *z_buffer)
{
	int		stripe;

	stripe = g_param.draw_start_x;
	while (stripe < g_param.draw_end_x)
	{
		raycasting_sprite_draw2(stripe, z_buffer);
		stripe++;
	}
}
