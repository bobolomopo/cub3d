#include "../include/cub3D.h"

void	color_square(t_img *img, int x, int y, int color)
{
	int		i;
	int		j;
	int		x2;

	x2 = x;
	i = 0;
	while (i < GRIDSIZE)
	{
		j = 0;
		x = x2;
		while (j < GRIDSIZE)
		{
			my_mlx_pixel_put(img, y, x, color);
			j++;
			x++;
		}
		y++;
		i++;
	}
}

void	draw_map(t_img *map)
{
	int		i;
	int		j;

	while (param.map[i])
	{
		j = 0;
		while (param.map[i][j])
		{
			if (param.map[i][j] == '1')
				color_square(map, i * GRIDSIZE, j * GRIDSIZE, 16777215);
			j++;
		}
		i++;
	}
}

void    draw_player(t_perso *perso)
{
    int		i;
	int		j;

	i = 0;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			my_mlx_pixel_put(&perso->img, i, j, 16711680);
			j++;
		}
		i++;
    }
}