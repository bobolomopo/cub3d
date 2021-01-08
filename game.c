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
		mlx_put_image_to_window(dis->mlx, dis->win, map.img, 0, 0);
        mlx_put_image_to_window(dis->mlx, dis->win, perso.img.img, perso.x, perso.y);
    }
    if (keycode == 123 && perso.x > 0)
    {
        mlx_clear_window(dis->mlx, dis->win);
        perso.x -= 5;
		mlx_put_image_to_window(dis->mlx, dis->win, map.img, 0, 0);
        mlx_put_image_to_window(dis->mlx, dis->win, perso.img.img, perso.x, perso.y);
    }
    if (keycode == 126 && perso.y > 0)
    {
        mlx_clear_window(dis->mlx, dis->win);
        perso.y -= 5;
		mlx_put_image_to_window(dis->mlx, dis->win, map.img, 0, 0);
        mlx_put_image_to_window(dis->mlx, dis->win, perso.img.img, perso.x, perso.y);
    }
    if (keycode == 125 && perso.y < 1000)
    {
        mlx_clear_window(dis->mlx, dis->win);
        perso.y += 5;
		mlx_put_image_to_window(dis->mlx, dis->win, map.img, 0, 0);
        mlx_put_image_to_window(dis->mlx, dis->win, perso.img.img, perso.x, perso.y);
    }
    if (keycode == 53)
        ft_close();
    return (0);
}

void	ft_define_map(t_param *param)
{
	int     i;
	int     j;

	i = 0;
	while (param->map[i])
	{
		j = 0;
		while (param->map[i][j])
			j++;
		if (j > param->map_w)
			param->map_w = j;
		i++;
	}
	param->map_h = i;
	}

int		initialize(t_param *param)
{
	fd = open("./test.cub", O_RDONLY);
	param->res_x = 0;
	param->res_y = 0;
	param->text_north = NULL;
	param->text_south = NULL;
	param->text_east = NULL;
	param->text_west = NULL;
	param->floor_color = -1;
	param->ceiling_color = -1;
	param->text_sprite = NULL;
	param->map = NULL;
	param->pos_x = 0;
	param->pos_y = 0;
	param->dir_x = 0;
	param->dir_y = 0;
	if (parsing(fd, param) < 0)
		return (-1);
	if (param->dir_x != 0)
		plan.x = 0;
	if (param->dir_y != 0)
		plan.x = 1;
	plan.y = 0.66;
	ft_define_map(param);
	return (1);
}

int		main(void)
{
    if (initialize(&param) < 0)
        return (-1);
    dis.mlx = mlx_init();
    dis.win = mlx_new_window(dis.mlx, param.res_x, param.res_y, "Cub3D");
	map.img = mlx_new_image(dis.mlx, param.res_x, param.res_y);
	map.addr = mlx_get_data_addr(map.img, &map.bits_per_pixel, &map.line_length,&map.endian);
	draw_map(&map);
	perso.img.img = mlx_new_image(dis.mlx, 20, 20);
	perso.img.addr = mlx_get_data_addr(perso.img.img, &perso.img.bits_per_pixel, &perso.img.line_length,&perso.img.endian);
	draw_player(&perso);
	mlx_put_image_to_window(dis.mlx, dis.win, map.img, 0, 0);
	perso.x = param.pos_x * GRIDSIZE + GRIDSIZE / 4;
	perso.y = param.pos_y * GRIDSIZE + GRIDSIZE / 4;
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