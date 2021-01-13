#include "../include/cub3D.h"

void	draw_ver_line(int x, int drawStart, int drawEnd, int color)
{
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(&game.img, x, drawStart, color);
		drawStart++;
	}
}

void	draw_ceil_floor(int width, int height)
{
	int		x;
	int		y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			if (y < height / 2)
				my_mlx_pixel_put(&game.img, x, y, param.floor_color);
			else
				my_mlx_pixel_put(&game.img, x, y, param.ceiling_color);
			y++;
		}
		x++;
	}
}