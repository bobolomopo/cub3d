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
	camera_x = 2 * x / (double)param.res_x - 1;
	ray_dir_x = dirX + plane_x * camera_x;
	ray_dir_y = dirY + plane_y * camera_x;
	map_x = (int)(posX);
	map_y = (int)(posY);
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	hit = 0;
}

static void raycasting_init2(int x)
{
	if(ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (posX - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - posX) * delta_dist_x;
	}
	if(ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (posY - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - posY) * delta_dist_y;
	}
}

static void	raycasting_dda()
{
	while (hit == 0)
	{	
		if(side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (param.map[map_x][map_y] == '1')
			hit = 1;
	}
}

static void		raycasting_texturing()
{
	if (side == 0)
			perp_wall_dist = (map_x - posX + (1 - step_x) / 2) / ray_dir_x;
	else
		perp_wall_dist = (map_y - posY + (1 - step_y) / 2) / ray_dir_y;
	line_height = (int)(param.res_y / perp_wall_dist);
	draw_start = -line_height / 2 + param.res_y / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + param.res_y / 2;
	if(draw_end >= param.res_y)
		draw_end = param.res_y - 1;
	if (side == 0)
	{
		if (ray_dir_x < 0)
			tex_num = 1;
		else
			tex_num = 0;
	}
	else
	{
		if (ray_dir_y < 0)
			tex_num = 3;
		else
			tex_num = 2;
	}
}

static void		raycasting_drawing(int x)
{
	int color;
	double wallX;
	if(side == 0)
		wallX = posY + perp_wall_dist * ray_dir_y;
	else
		wallX = posX + perp_wall_dist * ray_dir_x;
	wallX -= floor((wallX));
	int texX = (int)(wallX * (double)(textures[tex_num].width));
	if(side == 0 && ray_dir_x > 0)
		texX = textures[tex_num].width - texX - 1;
	if(side == 1 && ray_dir_y < 0)
		texX = textures[tex_num].width - texX - 1;
	double step = 1.0 * textures[tex_num].height / line_height;
	double texPos = (draw_start - param.res_y / 2 + line_height / 2) * step;
	for(int y = draw_start; y < draw_end; y++)
	{
		int texY = (int)texPos & (textures[tex_num].height - 1);
		texPos += step;
		color = get_tex_color(&textures[tex_num], texX, texY);
		if(side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&game.img, x, y, color);
	}
}

void raycasting_sprite_init(t_sprite *sprite, int *spriteOrder, int i)
{
	sprite_x = sprite[spriteOrder[i]].x - posX;
	sprite_y = sprite[spriteOrder[i]].y - posY;
	inv_det = 1.0 / (plane_x * dirY - dirX * plane_y);
	transform_x = inv_det * (dirY * sprite_x - dirX * sprite_y);
	transform_y = inv_det * (plane_x * sprite_y -plane_y * sprite_x);
	sprite_screen_x = (int)((param.res_x / 2) * (1 + (transform_x / transform_y)));
	sprite_height = abs((int)((param.res_y / (transform_y))));
	draw_start_y = -sprite_height / 2 + param.res_y / 2;
	if(draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite_height / 2 + param.res_y / 2;
	if(draw_end_y >= param.res_y)
		draw_end_y = param.res_y - 1;
	sprite_width = abs((int)(param.res_y / (transform_y)));
	draw_start_x = -sprite_width / 2 + sprite_screen_x;
	if(draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite_width / 2 + sprite_screen_x;
	if(draw_end_x >= param.res_x)
		draw_end_x = param.res_x - 1;
}

void		raycasting_sprite_draw(double *z_buffer)
{
	int color;

	for(int stripe = draw_start_x; stripe < draw_end_x; stripe++)
	{
		int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * textures[4].width / sprite_width) / 256;
		if (transform_y > 0 && stripe > 0 && stripe < param.res_x && transform_y < z_buffer[stripe])
		{
			for(int y = draw_start_y; y < draw_end_y; y++)
			{
				int d = y * 256 - param.res_y * 128 + sprite_height * 128;
				int tex_y = ((d * textures[4].height) / sprite_height) / 256;
				color = get_tex_color(&textures[4], tex_x, tex_y);
				if (color != 0)
					my_mlx_pixel_put(&game.img, stripe, y, color);
			}
		}
	}
}

void	raycasting()
{
	int			x;
	int			tex_num;
	double		z_buffer[param.res_x];
	int			spriteOrder[param.num_sprite];
	double		spriteDistance[param.num_sprite];
	t_sprite	sprite[param.num_sprite];

	x = 0;
	sprite_value(sprite);
	while (x < param.res_x)
	{
		raycasting_init(x);
		raycasting_init2(x);
		raycasting_dda();
		raycasting_texturing();
		raycasting_drawing(x);
		z_buffer[x] = perp_wall_dist;
		x++;
	}
	for(int i = 0; i < param.num_sprite; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = sqrt(((posX - sprite[i].x) * (posX - sprite[i].x) + (posY - sprite[i].y) * (posY - sprite[i].y)));
	}
	if (param.num_sprite > 0)
		sortsprite(spriteOrder, spriteDistance, param.num_sprite);
	for(int i = 0; i < param.num_sprite; i++)
	{
		raycasting_sprite_init(sprite, spriteOrder, i);
		raycasting_sprite_draw(z_buffer);
	}
}