#include "../include/cub3D.h"

/*
**selon les tuto, permet d'afficher plus rapidement les pixeles et de les
**gerer plus facilement
*/

void            my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
