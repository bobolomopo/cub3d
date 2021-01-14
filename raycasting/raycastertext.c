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
	ray_dir_x = dirX + planeX * camera_x;
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

static int		get_tex_color(t_img *tex, int x, int y)
{
	char	*dst;
	int		color;

	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	color = (*(unsigned int*)dst);
	return (color);
}

void raycasting()
{
	int		color;
	int		x;
	int		texNum;

	x = 0;
	while (x++ < param.res_x)
	{
		raycasting_init(x);
		raycasting_init2(x);
		raycasting_dda();
		if (side == 0)
			perp_wall_dist = (map_x - posX + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - posY + (1 - step_y) / 2) / ray_dir_y;
		line_height = (int)(param.res_y / perp_wall_dist);
		draw_start = -line_height / 2 + param.res_y / 2;
		if(draw_start < 0)draw_start = 0;
			draw_end = line_height / 2 + param.res_y / 2;
		if(draw_end >= param.res_y)
			draw_end = param.res_y - 1;
		else if (side == 0)
		{
			if (ray_dir_x < 0)
				texNum = 1;
			else
				texNum = 0;
		}
		else
		{
			if (ray_dir_y < 0)
				texNum = 3;
			else
				texNum = 2;
		}
		double wallX;
		if(side == 0)
			wallX = posY + perp_wall_dist * ray_dir_y;
		else
			wallX = posX + perp_wall_dist * ray_dir_x;
		wallX -= floor((wallX));
		int texX = (int)(wallX * (double)(textures[texNum].width));
		if(side == 0 && ray_dir_x > 0)
			texX = textures[texNum].width - texX - 1;
		if(side == 1 && ray_dir_y < 0)
			texX = textures[texNum].width - texX - 1;
		double step = 1.0 * textures[texNum].height / line_height;
		double texPos = (draw_start - param.res_y / 2 + line_height / 2) * step;
		for(int y = draw_start; y < draw_end; y++)
		{
			int texY = (int)texPos & (textures[texNum].height - 1);
			texPos += step;
			color = get_tex_color(&textures[texNum], texX, texY);
			if(side == 1)
				color = (color >> 1) & 8355711;
			my_mlx_pixel_put(&game.img, x, y, color);
		}
	}
}