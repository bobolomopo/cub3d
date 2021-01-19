/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:06:22 by jandre            #+#    #+#             */
/*   Updated: 2021/01/19 16:06:24 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	raycasting_texturing2(void)
{
	if (g_param.side == 0)
	{
		if (g_param.ray_dir_x < 0)
			g_param.tex_num = 1;
		else
			g_param.tex_num = 0;
	}
	else
	{
		if (g_param.ray_dir_y < 0)
			g_param.tex_num = 3;
		else
			g_param.tex_num = 2;
	}
}

static void	raycasting_drawing2(int x, int tex_x, int tex_y)
{
	int		y;
	int		color;

	y = g_param.draw_start;
	while (y < g_param.draw_end)
	{
		tex_y = (int)g_param.tex_pos &
			(g_param.textures[g_param.tex_num].height - 1);
		g_param.tex_pos += g_param.step;
		color = get_tex_color(&g_param.textures[g_param.tex_num], tex_x, tex_y);
		if (g_param.side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&g_param.game, x, y, color);
		y++;
	}
}

void		raycasting_texturing(void)
{
	if (g_param.side == 0)
	{
		g_param.perp_wall_dist = (g_param.map_x - g_param.pos_x +
		(1 - g_param.step_x) / 2) / g_param.ray_dir_x;
	}
	else
	{
		g_param.perp_wall_dist = (g_param.map_y - g_param.pos_y +
		(1 - g_param.step_y) / 2) / g_param.ray_dir_y;
	}
	g_param.line_height = (int)(g_param.res_y / g_param.perp_wall_dist);
	g_param.draw_start = -g_param.line_height / 2 + g_param.res_y / 2;
	if (g_param.draw_start < 0)
		g_param.draw_start = 0;
	g_param.draw_end = g_param.line_height / 2 + g_param.res_y / 2;
	if (g_param.draw_end >= g_param.res_y)
		g_param.draw_end = g_param.res_y - 1;
	raycasting_texturing2();
}

void		raycasting_drawing(int x)
{
	int		tex_y;
	int		tex_x;
	double	wall_x;

	if (g_param.side == 0)
		wall_x = g_param.pos_y + g_param.perp_wall_dist * g_param.ray_dir_y;
	else
		wall_x = g_param.pos_x + g_param.perp_wall_dist * g_param.ray_dir_x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)(g_param.textures[g_param.tex_num].width));
	if (g_param.side == 0 && g_param.ray_dir_x > 0)
		tex_x = g_param.textures[g_param.tex_num].width - tex_x - 1;
	if (g_param.side == 1 && g_param.ray_dir_y < 0)
		tex_x = g_param.textures[g_param.tex_num].width - tex_x - 1;
	g_param.step = 1.0 * g_param.textures[g_param.tex_num].height
		/ g_param.line_height;
	g_param.tex_pos = (g_param.draw_start - g_param.res_y / 2
		+ g_param.line_height / 2) * g_param.step;
	raycasting_drawing2(x, tex_x, tex_y);
}
