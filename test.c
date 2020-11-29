/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:36:04 by jandre            #+#    #+#             */
/*   Updated: 2020/11/29 17:12:18 by jandre           ###   ########.fr       */
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
    mlx_destroy_window(dis->mlx, dis->win);
}

int main()
{
	t_display	dis;
	t_img		img;
	int		x;
	int		y;


	dis.mlx = mlx_init();
	dis.win = mlx_new_window(dis.mlx, 800, 640, "Cub3D");
	img.img = mlx_new_image(dis.mlx, 800, 640);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.line_length, &img.endian);
	x = 100;
	while (x++ <= 200)
	{
		y = 100;
		while (y++ <= 200)
			my_mlx_pixel_put(&img, x, y, 0X00FF0000);
	}
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(dis.mlx, dis.win, img.img, 0, 0);
	mlx_hook(dis.win, 2, 1L<<0, closing, &dis);
	mlx_loop(dis.mlx);
	return (0);
}
