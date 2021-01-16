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

#include "../include/cub3D.h"

static void			lateral_mouvement(int keycode)
{
	if (keycode == 2)
	{
		if ((param.map[(int)(posX + dirY * MOVESPEED)][(int)(posY)]) == '0')
			posX += dirY * MOVESPEED;
		if ((param.map[(int)(posX)][(int)(posY - dirX * MOVESPEED)]) == '0')
			posY -= dirX * MOVESPEED;
	}
	if (keycode == 0)
	{
		if ((param.map[(int)(posX - dirY * MOVESPEED)][(int)(posY)]) == '0')
			posX -= dirY * MOVESPEED;
		if ((param.map[(int)(posX)][(int)(posY + dirX * MOVESPEED)]) == '0')
			posY += dirX * MOVESPEED;
	}
}

static void			linear_movement(int keycode)
{
	if (keycode == 13)
	{
		if ((param.map[(int)(posX + dirX * MOVESPEED)][(int)(posY)]) == '0')
			posX += dirX * MOVESPEED;
		if ((param.map[(int)(posX)][(int)(posY + dirY * MOVESPEED)]) == '0')
			posY += dirY * MOVESPEED;
	}
	if (keycode == 1)
	{
		if ((param.map[(int)(posX - dirX * MOVESPEED)][(int)(posY)]) == '0')
			posX -= dirX * MOVESPEED;
		if ((param.map[(int)(posX)][(int)(posY - dirY * MOVESPEED)]) == '0')
			posY -= dirY * MOVESPEED;
	}
}

static void			rotation(int keycode)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == 124)
	{
		old_dir_x = dirX;
		dirX = dirX * cos(-ROTSPEED) - dirY * sin(-ROTSPEED);
		dirY = old_dir_x * sin(-ROTSPEED) + dirY * cos(-ROTSPEED);
		old_plane_x = plane_x;
		plane_x = plane_x * cos(-ROTSPEED) - plane_y * sin(-ROTSPEED);
		plane_y = old_plane_x * sin(-ROTSPEED) + plane_y * cos(-ROTSPEED);
	}
	if (keycode == 123)
	{
		old_dir_x = dirX;
		dirX = dirX * cos(ROTSPEED) - dirY * sin(ROTSPEED);
		dirY = old_dir_x * sin(ROTSPEED) + dirY * cos(ROTSPEED);
		old_plane_x = plane_x;
		plane_x = plane_x * cos(ROTSPEED) - plane_y * sin(ROTSPEED);
		plane_y = old_plane_x * sin(ROTSPEED) + plane_y * cos(ROTSPEED);
	}
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
	draw_ceil_floor(param.res_x, param.res_y);
	raycasting();
	mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
	return (1);
}
