/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:26:12 by jandre            #+#    #+#             */
/*   Updated: 2021/01/16 16:26:14 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void			lateral_mouvement(int keycode)
{
	if (keycode == 2)
	{
		if ((g_param.map[(int)(g_param.pos_x + g_param.dir_y * MOVESPEED)]
			[(int)(g_param.pos_y)]) == '0')
			g_param.pos_x += g_param.dir_y * MOVESPEED;
		if ((g_param.map[(int)(g_param.pos_x)][(int)(g_param.pos_y -
			g_param.dir_x * MOVESPEED)]) == '0')
			g_param.pos_y -= g_param.dir_x * MOVESPEED;
	}
	if (keycode == 0)
	{
		if ((g_param.map[(int)(g_param.pos_x - g_param.dir_y * MOVESPEED)]
			[(int)(g_param.pos_y)]) == '0')
			g_param.pos_x -= g_param.dir_y * MOVESPEED;
		if ((g_param.map[(int)(g_param.pos_x)][(int)(g_param.pos_y +
			g_param.dir_x * MOVESPEED)]) == '0')
			g_param.pos_y += g_param.dir_x * MOVESPEED;
	}
}

static void			linear_movement(int keycode)
{
	if (keycode == 13)
	{
		if ((g_param.map[(int)(g_param.pos_x + g_param.dir_x * MOVESPEED)]
			[(int)(g_param.pos_y)]) == '0')
			g_param.pos_x += g_param.dir_x * MOVESPEED;
		if ((g_param.map[(int)(g_param.pos_x)][(int)(g_param.pos_y +
			g_param.dir_y * MOVESPEED)]) == '0')
			g_param.pos_y += g_param.dir_y * MOVESPEED;
	}
	if (keycode == 1)
	{
		if ((g_param.map[(int)(g_param.pos_x - g_param.dir_x * MOVESPEED)]
			[(int)(g_param.pos_y)]) == '0')
			g_param.pos_x -= g_param.dir_x * MOVESPEED;
		if ((g_param.map[(int)(g_param.pos_x)][(int)(g_param.pos_y -
			g_param.dir_y * MOVESPEED)]) == '0')
			g_param.pos_y -= g_param.dir_y * MOVESPEED;
	}
}

static void			rotation2(int keycode, double old_dir_x, double old_plane_x)
{
	if (keycode == 123)
	{
		old_dir_x = g_param.dir_x;
		g_param.dir_x = g_param.dir_x * cos(ROTSPEED) -
			g_param.dir_y * sin(ROTSPEED);
		g_param.dir_y = old_dir_x * sin(ROTSPEED) +
			g_param.dir_y * cos(ROTSPEED);
		old_plane_x = g_param.plane_x;
		g_param.plane_x = g_param.plane_x * cos(ROTSPEED) -
			g_param.plane_y * sin(ROTSPEED);
		g_param.plane_y = old_plane_x * sin(ROTSPEED) +
			g_param.plane_y * cos(ROTSPEED);
	}
}

static void			rotation(int keycode)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == 124)
	{
		old_dir_x = g_param.dir_x;
		g_param.dir_x = g_param.dir_x * cos(-ROTSPEED) -
			g_param.dir_y * sin(-ROTSPEED);
		g_param.dir_y = old_dir_x * sin(-ROTSPEED) +
			g_param.dir_y * cos(-ROTSPEED);
		old_plane_x = g_param.plane_x;
		g_param.plane_x = g_param.plane_x * cos(-ROTSPEED) -
			g_param.plane_y * sin(-ROTSPEED);
		g_param.plane_y = old_plane_x * sin(-ROTSPEED) +
			g_param.plane_y * cos(-ROTSPEED);
	}
	rotation2(keycode, old_dir_x, old_plane_x);
}

int					manage_key(int keycode)
{
	if (keycode == 13 || keycode == 1)
		linear_movement(keycode);
	if (keycode == 2 || keycode == 0)
		lateral_mouvement(keycode);
	if (keycode == 124 || keycode == 123)
		rotation(keycode);
	if (keycode == 53)
		ft_close();
	draw_ceil_floor(g_param.res_x, g_param.res_y);
	raycasting();
	mlx_put_image_to_window(g_param.dis.mlx, g_param.dis.win,
		g_param.game.img, 0, 0);
	return (1);
}
