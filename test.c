/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:36:04 by jandre            #+#    #+#             */
/*   Updated: 2020/11/30 14:55:06 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

void            my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             closing(int keycode, t_display *dis)
{
	if (keycode == 0xff53 && pos.x < 790)
	{
		mlx_clear_window(dis->mlx, dis->win);
		pos.x += 5;
		mlx_put_image_to_window(dis->mlx, dis->win, perso.img, pos.x, pos.y);
	}
			
	if (keycode == 0xff1b)
		mlx_destroy_window(dis->mlx, dis->win);
}

int main()
{
	t_display	dis;
	int		x;
	int		y;


	dis.mlx = mlx_init();
	dis.win = mlx_new_window(dis.mlx, 800, 640, "Cub3D");
	perso.img = mlx_new_image(dis.mlx, 10, 10);
	perso.addr = mlx_get_data_addr(perso.img, &perso.bits_per_pixel, &perso.line_length, &perso.endian);
	pos.x = 0;
	while (pos.x++ <= 10)
	{
		pos.y = 0;
		while (pos.y++ <= 10)
			my_mlx_pixel_put(&perso, pos.x, pos.y, 0X00FF0000);
	}
	pos.x = 0;
	pos.y = 0;
	mlx_put_image_to_window(dis.mlx, dis.win, perso.img, pos.x, pos.y);
	mlx_hook(dis.win, 2, 1L<<0, closing, &dis);
	mlx_loop(dis.mlx);
	return (0);
}
