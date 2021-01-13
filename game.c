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

int             manage_key(int keycode)
{
	double	move_speed;
	double	old_dir;
	double	rot_speed;

	move_speed = 0.1;
	rot_speed = 0.08;
    if (keycode == 124)
    {
		mlx_destroy_image(dis.mlx, game.img.img);
        mlx_clear_window(dis.mlx, dis.win);
		game.img.img = mlx_new_image(dis.mlx, param.res_x, param.res_y);
		game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);
		old_dir = param.dir_x;
		param.dir_x = param.dir_x * cos(-rot_speed) - param.dir_y * sin(-rot_speed);
		param.dir_y = old_dir * sin(-rot_speed) + param.dir_y * cos(-rot_speed);
		old_plane_x = plane_x;
		plane_x = (plane_x * cos(-rot_speed)) - (plane_y * sin(-rot_speed));
		plane_y = old_plane_x * sin(-rot_speed) + plane_y * cos(-rot_speed);
		raycasting();
		mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
    }
    if (keycode == 123)
    {
		mlx_destroy_image(dis.mlx, game.img.img);
        mlx_clear_window(dis.mlx, dis.win);
		game.img.img = mlx_new_image(dis.mlx, param.res_x, param.res_y);
		game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);
		old_dir = param.dir_x;
		param.dir_x = param.dir_x * cos(rot_speed) - param.dir_y * sin(rot_speed);
		param.dir_y = old_dir * sin(rot_speed) + param.dir_y * cos(rot_speed);
		old_plane_x = plane_x;
		plane_x = plane_x * cos(rot_speed) - plane_y * sin(rot_speed);
		plane_y = old_plane_x * sin(rot_speed) + plane_y * cos(rot_speed);
		raycasting();
		mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
    }
    if (keycode == 126)
    {
		mlx_destroy_image(dis.mlx, game.img.img);
        mlx_clear_window(dis.mlx, dis.win);
		game.img.img = mlx_new_image(dis.mlx, param.res_x, param.res_y);
		game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);
		if (param.map[(int)(param.pos_x + param.dir_x * move_speed)][(int)param.pos_y])
			param.pos_x += param.dir_x * move_speed;
		if (param.map[(int)param.pos_x][(int)(param.pos_y + param.dir_y * move_speed)])
			param.pos_y += param.dir_y * move_speed;
		raycasting();
		mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
    }
    if (keycode == 125)
    {
		mlx_destroy_image(dis.mlx, game.img.img);
        mlx_clear_window(dis.mlx, dis.win);
		game.img.img = mlx_new_image(dis.mlx, param.res_x, param.res_y);
		game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);
		if (param.map[(int)(param.pos_x - param.dir_x * move_speed)][(int)param.pos_y])
			param.pos_x -= param.dir_x * move_speed;
		if (param.map[(int)param.pos_x][(int)(param.pos_y - param.dir_y * move_speed)])
			param.pos_y -= param.dir_y * move_speed;
		raycasting();
		mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
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
	ft_define_map(param);
	return (1);
}

int		main(void)
{
    if (initialize(&param) < 0)
        return (-1);
	dis.mlx = mlx_init();
	dis.win = mlx_new_window(dis.mlx, param.res_x, param.res_y, "Cub3D");
	game.img.img = mlx_new_image(dis.mlx, param.res_x, param.res_y);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);
	raycasting();
	mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
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