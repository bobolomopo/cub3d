/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:10:59 by jandre            #+#    #+#             */
/*   Updated: 2020/12/03 16:11:35 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

int             manage_key(int keycode, t_display *dis)
{
    if (keycode == 124 && perso.x < 1000)
    {
        mlx_clear_window(dis->mlx, dis->win);
        perso.x += 5;
        mlx_put_image_to_window(dis->mlx, dis->win, perso.img.img, perso.x, perso.y);
    }
    if (keycode == 123 && perso.x > 0)
    {
        mlx_clear_window(dis->mlx, dis->win);
        perso.x -= 5;
        mlx_put_image_to_window(dis->mlx, dis->win, perso.img.img, perso.x, perso.y);
    }
    if (keycode == 126 && perso.y > 0)
    {
        mlx_clear_window(dis->mlx, dis->win);
        perso.y -= 5;
        mlx_put_image_to_window(dis->mlx, dis->win, perso.img.img, perso.x, perso.y);
    }
    if (keycode == 125 && perso.y < 1000)
    {
        mlx_clear_window(dis->mlx, dis->win);
        perso.y += 5;
        mlx_put_image_to_window(dis->mlx, dis->win, perso.img.img, perso.x, perso.y);
    }
    if (keycode == 53)
        mlx_destroy_window(dis->mlx, dis->win);
    return (0);
}

void            my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		main(void)
{
    dis.mlx = mlx_init();
    dis.win = mlx_new_window(dis.mlx, 1000, 1000, "Cub3D");
    perso.img.img = mlx_new_image(dis.mlx, 15, 15);
    perso.img.addr = mlx_get_data_addr(perso.img.img, &perso.img.bits_per_pixel,
                                        &perso.img.line_length,&perso.img.endian);
    perso.x = 0;
    while (perso.x++ < 10)
    {
        perso.y = 0;
        while (perso.y++ < 10)
            my_mlx_pixel_put(&perso.img, perso.x, perso.y, 16711680);
    }
    perso.x = 0;
    perso.y = 0;
    mlx_put_image_to_window(dis.mlx, dis.win, perso.img.img, perso.x, perso.y);
    mlx_hook(dis.win, 2, 1L<<0, manage_key, &dis);
    mlx_loop(dis.mlx);
    return (0);
}


/* 
void    *mlx_init();
void    *mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
int     mlx_clear_window(void *mlx_ptr, void *win_ptr);
int     mlx_destroy_window(void *mlx_ptr, void *win_ptr);

int     mlx_get_color_value(void *mlx_ptr, int color);
int     mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
int     mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color, char *string);

void    *mlx_new_image(void *mlx_ptr,int width,int height);
char    *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);
int     mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);
int     mlx_destroy_image(void *mlx_ptr, void *img_ptr);

int     mlx_mouse_hook (void *win_ptr, int (*f)(), void *param);
int     mlx_key_hook (void *win_ptr, int (*f)(), void *param);
int     mlx_loop_hook (void *mlx_ptr, int (*f)(), void *param);
int     mlx_loop (void *mlx_ptr);

void    *mlx_xpm_to_image(void *mlx_ptr, char **xpm_data, int *width, int *height);
void    *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);
void    *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);
int     mlx_mouse_hide();
int     mlx_mouse_show();
int     mlx_mouse_move(void *win_ptr, int x, int y);
int     mlx_mouse_get_pos(void *win_ptr, int *x, int *y);
int     mlx_do_key_autorepeatoff(void *mlx_ptr);
int     mlx_do_key_autorepeaton(void *mlx_ptr);
int		mlx_do_sync(void *mlx_ptr);
int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);
*/