/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:54:08 by jandre            #+#    #+#             */
/*   Updated: 2021/01/12 18:54:11 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3D.h"
#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

char world_map[mapWidth][mapHeight]=
{
  {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','2','2','2','2','2','0','0','0','0','3','0','3','0','3','0','0','0','1'},
  {'1','0','0','0','0','0','2','0','0','0','2','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','2','0','0','0','2','0','0','0','0','3','0','0','0','3','0','0','0','1'},
  {'1','0','0','0','0','0','2','0','0','0','2','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','2','2','0','2','2','0','0','0','0','3','0','3','0','3','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','4','4','4','4','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','4','0','4','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','4','0','0','0','0','5','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','4','0','4','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','4','0','4','4','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','4','4','4','4','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
  {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}
};

void	draw_ver_line(int x, int drawStart, int drawEnd, int color)
{
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(&game.img, x, drawStart, color);
		drawStart++;
	}
}

void	raycasting()
{
	double	pos_x;
	double	dir_x;
	double	pos_y;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double  side_dist_x;
	double  side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		x;
	int		hit;
	int		step_x;
	int		step_y;
	int 	side;
	int		line_height;
	int		draw_end;
	int		draw_start;
	
	pos_x = param.pos_x;
	pos_y = param.pos_y;
	dir_x = param.dir_x;
	dir_y = param.dir_y;
	plane_y = 0.66;
	x = 0;
	while (x < param.res_x)
	{
		camera_x = 2 * x / (double)param.res_x - 1;
		ray_dir_x = dir_x + plane_x * camera_x;
		ray_dir_y = dir_y + plane_y * camera_x;
		map_x = (int)pos_x;
		map_y = (int)pos_y;
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		hit = 0;
		if(ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
		}
		if(ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
		}
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
			if ((ft_isin(param.map[map_x][map_y], "0NESW")) < 0) 
				hit = 1;
		}
		if(side == 0)
			perp_wall_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y;
		line_height = (int)(param.res_y / perp_wall_dist);
		draw_start = -line_height / 2 + param.res_y / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + param.res_y / 2;
		if (draw_end >= param.res_y)
			draw_end = param.res_y - 1;
		int color;
		switch(param.map[map_x][map_y])
		{
		case '1':  color = 16711680;    break; //red
		case '2':  color = 65280;  break; //green
		case '3':  color = 255;   break; //blue
		case '4':  color = 16777215;  break; //white
		default: color = 16776960; break; //yellow
		}
		if (side == 1)
			color /= 2;
		draw_ver_line(x, draw_start, draw_end, color);
		x++;
	}
}