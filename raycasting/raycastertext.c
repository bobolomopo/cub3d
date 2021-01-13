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
		if (param.map[map_x][map_y] != '0')
			hit = 1;
	}
}

void raycasting()
{
	int		color;
	int		x;

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
		switch(param.map[map_x][map_y])
		{
			case '1':  color = 16711680;    break; //red
			case '2':  color = 65280;  break; //green
			case '3':  color = 255;   break; //blue
			case '4':  color = 16777215;  break; //white
			default: color = 16776960; break; //yellow
		}
		if(side == 1) {color = color / 2;}
		draw_ver_line(x, draw_start, draw_end, color);
	}
}