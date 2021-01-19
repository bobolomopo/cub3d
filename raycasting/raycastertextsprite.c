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

#include "../include/cub3D.h"

static void raycasting_init(int x)
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

static void raycasting_init2(int x)
{
	if(g_param.ray_dir_x < 0)
	{
		g_param.step_x = -1;
		g_param.side_dist_x = (g_param.pos_x - g_param.map_x) * g_param.delta_dist_x;
	}
	else
	{
		g_param.step_x = 1;
		g_param.side_dist_x = (g_param.map_x + 1.0 - g_param.pos_x) * g_param.delta_dist_x;
	}
	if(g_param.ray_dir_y < 0)
	{
		g_param.step_y = -1;
		g_param.side_dist_y = (g_param.pos_y - g_param.map_y) * g_param.delta_dist_y;
	}
	else
	{
		g_param.step_y = 1;
		g_param.side_dist_y = (g_param.map_y + 1.0 - g_param.pos_y) * g_param.delta_dist_y;
	}
}

static void	raycasting_dda()
{
	while (g_param.hit == 0)
	{	
		if(g_param.side_dist_x < g_param.side_dist_y)
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
		if (g_param.map[g_param.map_x][g_param.map_y] == '1')
			g_param.hit = 1;
	}
}

static void		raycasting_texturing()
{
	if (g_param.side == 0)
			g_param.perp_wall_dist = (g_param.map_x - g_param.pos_x + (1 - g_param.step_x) / 2) / g_param.ray_dir_x;
	else
		g_param.perp_wall_dist = (g_param.map_y - g_param.pos_y + (1 - g_param.step_y) / 2) / g_param.ray_dir_y;
	g_param.line_height = (int)(g_param.res_y / g_param.perp_wall_dist);
	g_param.draw_start = -g_param.line_height / 2 + g_param.res_y / 2;
	if (g_param.draw_start < 0)
		g_param.draw_start = 0;
	g_param.draw_end = g_param.line_height / 2 + g_param.res_y / 2;
	if(g_param.draw_end >= g_param.res_y)
		g_param.draw_end = g_param.res_y - 1;
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

static void		raycasting_drawing(int x)
{
	int color;
	double wallX;
	if (g_param.side == 0)
		wallX = g_param.pos_y + g_param.perp_wall_dist * g_param.ray_dir_y;
	else
		wallX = g_param.pos_x + g_param.perp_wall_dist * g_param.ray_dir_x;
	wallX -= floor((wallX));
	int texX = (int)(wallX * (double)(g_param.textures[g_param.tex_num].width));
	if (g_param.side == 0 && g_param.ray_dir_x > 0)
		texX = g_param.textures[g_param.tex_num].width - texX - 1;
	if (g_param.side == 1 && g_param.ray_dir_y < 0)
		texX = g_param.textures[g_param.tex_num].width - texX - 1;
	double step = 1.0 * g_param.textures[g_param.tex_num].height / g_param.line_height;
	double texPos = (g_param.draw_start - g_param.res_y / 2 + g_param.line_height / 2) * step;
	for(int y = g_param.draw_start; y < g_param.draw_end; y++)
	{
		int texY = (int)texPos & (g_param.textures[g_param.tex_num].height - 1);
		texPos += step;
		color = get_tex_color(&g_param.textures[g_param.tex_num], texX, texY);
		if (g_param.side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&g_param.game, x, y, color);
	}
}

void raycasting_sprite_init(t_sprite *sprite, int *spriteOrder, int i)
{
	g_param.sprite_x = sprite[spriteOrder[i]].x - g_param.pos_x;
	g_param.sprite_y = sprite[spriteOrder[i]].y - g_param.pos_y;
	g_param.inv_det = 1.0 / (g_param.plane_x * g_param.dir_y - g_param.dir_x * g_param.plane_y);
	g_param.transform_x = g_param.inv_det * (g_param.dir_y * g_param.sprite_x - g_param.dir_x * g_param.sprite_y);
	g_param.transform_y = g_param.inv_det * (g_param.plane_x * g_param.sprite_y -g_param.plane_y * g_param.sprite_x);
	g_param.sprite_screen_x = (int)((g_param.res_x / 2) * (1 + (g_param.transform_x / g_param.transform_y)));
	g_param.sprite_height = abs((int)((g_param.res_y / (g_param.transform_y))));
	g_param.draw_start_y = -g_param.sprite_height / 2 + g_param.res_y / 2;
	if (g_param.draw_start_y < 0)
		g_param.draw_start_y = 0;
	g_param.draw_end_y = g_param.sprite_height / 2 + g_param.res_y / 2;
	if (g_param.draw_end_y >= g_param.res_y)
		g_param.draw_end_y = g_param.res_y - 1;
	g_param.sprite_width = abs((int)(g_param.res_y / (g_param.transform_y)));
	g_param.draw_start_x = -g_param.sprite_width / 2 + g_param.sprite_screen_x;
	if (g_param.draw_start_x < 0)
		g_param.draw_start_x = 0;
	g_param.draw_end_x = g_param.sprite_width / 2 + g_param.sprite_screen_x;
	if (g_param.draw_end_x >= g_param.res_x)
		g_param.draw_end_x = g_param.res_x - 1;
}

void		raycasting_sprite_draw(double *z_buffer)
{
	int color;

	for(int stripe = g_param.draw_start_x; stripe < g_param.draw_end_x; stripe++)
	{
		int tex_x = (int)(256 * (stripe - (-g_param.sprite_width / 2 + g_param.sprite_screen_x)) * g_param.textures[4].width / g_param.sprite_width) / 256;
		if (g_param.transform_y > 0 && stripe > 0 && stripe < g_param.res_x && g_param.transform_y < z_buffer[stripe])
		{
			for(int y = g_param.draw_start_y; y < g_param.draw_end_y; y++)
			{
				int d = y * 256 - g_param.res_y * 128 + g_param.sprite_height * 128;
				int tex_y = ((d * g_param.textures[4].height) / g_param.sprite_height) / 256;
				color = get_tex_color(&g_param.textures[4], tex_x, tex_y);
				if (color != 0)
					my_mlx_pixel_put(&g_param.game, stripe, y, color);
			}
		}
	}
}

void	raycasting()
{
	int			x;
	double		z_buffer[g_param.res_x];
	int			spriteOrder[g_param.num_sprite];
	double		spriteDistance[g_param.num_sprite];
	t_sprite	sprite[g_param.num_sprite];

	x = 0;
	sprite_value(sprite);
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
	for(int i = 0; i < g_param.num_sprite; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = sqrt(((g_param.pos_x - sprite[i].x) * (g_param.pos_x - sprite[i].x) + (g_param.pos_y - sprite[i].y) * (g_param.pos_y - sprite[i].y)));
	}
	if (g_param.num_sprite > 0)
		sortsprite(spriteOrder, spriteDistance, g_param.num_sprite);
	for(int i = 0; i < g_param.num_sprite; i++)
	{
		raycasting_sprite_init(sprite, spriteOrder, i);
		raycasting_sprite_draw(z_buffer);
	}
}