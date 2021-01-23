/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastertext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 20:27:40 by jandre            #+#    #+#             */
/*   Updated: 2021/01/13 20:27:43 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void		raycasting_init(int x)
{
	g_param.camera_x = 2 * x / (double)g_param.res_x - 1;
	g_param.ray_dir_x = g_param.dir_x + g_param.plane_x * g_param.camera_x;
	g_param.ray_dir_y = g_param.dir_y + g_param.plane_y * g_param.camera_x;
	g_param.map_x = (int)(g_param.pos_x);
	g_param.map_y = (int)(g_param.pos_y);
	g_param.delta_dist_x = fabs(1 / g_param.ray_dir_x);
	g_param.delta_dist_y = fabs(1 / g_param.ray_dir_y);
	g_param.hit = 0;
}

static void		raycasting_init2(int x)
{
	if (g_param.ray_dir_x < 0)
	{
		g_param.step_x = -1;
		g_param.side_dist_x = (g_param.pos_x - g_param.map_x) *
								g_param.delta_dist_x;
	}
	else
	{
		g_param.step_x = 1;
		g_param.side_dist_x = (g_param.map_x + 1.0 - g_param.pos_x) *
								g_param.delta_dist_x;
	}
	if (g_param.ray_dir_y < 0)
	{
		g_param.step_y = -1;
		g_param.side_dist_y = (g_param.pos_y - g_param.map_y) *
								g_param.delta_dist_y;
	}
	else
	{
		g_param.step_y = 1;
		g_param.side_dist_y = (g_param.map_y + 1.0 - g_param.pos_y) *
								g_param.delta_dist_y;
	}
}

static void		raycasting_dda(void)
{
	while (g_param.hit == 0)
	{
		if (g_param.side_dist_x < g_param.side_dist_y)
		{
			g_param.side_dist_x += g_param.delta_dist_x;
			g_param.map_x += g_param.step_x;
			g_param.side = 0;
		}
		else
		{
			g_param.side_dist_y += g_param.delta_dist_y;
			g_param.map_y += g_param.step_y;
			g_param.side = 1;
		}
		printf("%c\n", g_param.map[g_param.map_x][g_param.map_y]);
		if (g_param.map[g_param.map_x][g_param.map_y] == '1')
			g_param.hit = 1;
	}
}

static void		raycasting2(double *z_buffer)
{
	int			i;
	int			sprite_order[g_param.num_sprite];
	double		sprite_distance[g_param.num_sprite];
	t_sprite	sprite[g_param.num_sprite];

	i = -1;
	sprite_value(sprite);
	while (++i < g_param.num_sprite)
	{
		sprite_order[i] = i;
		sprite_distance[i] = sqrt(((g_param.pos_x - sprite[i].x) *
			(g_param.pos_x - sprite[i].x) + (g_param.pos_y - sprite[i].y) *
			(g_param.pos_y - sprite[i].y)));
	}
	if (g_param.num_sprite > 0)
		sortsprite(sprite_order, sprite_distance, g_param.num_sprite);
	i = -1;
	while (++i < g_param.num_sprite)
	{
		raycasting_sprite_init(sprite, sprite_order, i);
		raycasting_sprite_draw(z_buffer);
	}
}

void			raycasting(void)
{
	int			x;
	int			i;
	double		z_buffer[g_param.res_x];

	x = 0;
	while (x < g_param.res_x)
	{
		raycasting_init(x);
		raycasting_init2(x);
		raycasting_dda();
		raycasting_texturing();
		raycasting_drawing(x);
		z_buffer[x] = g_param.perp_wall_dist;
		x++;
	}
	raycasting2(z_buffer);
}
