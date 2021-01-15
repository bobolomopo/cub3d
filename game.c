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

/*void	ft_define_map(t_param *param)
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
}*/

int main()
{
	dis.mlx = mlx_init();
	if (initialize(&param) < 0)
        return (-1);
	posX = param.pos_x;
	posY = param.pos_y;
	if (posX == 1)
		posX += 0.5;
	if (posY == 1)
		posY += 0.5;
	dirX = param.dir_x;
	dirY = param.dir_y;
	int i = 0;
	dis.win = mlx_new_window(dis.mlx, param.res_x, param.res_y, "Cub3D");
	game.img.img = mlx_new_image(dis.mlx, param.res_x, param.res_y);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);
	draw_ceil_floor(param.res_x, param.res_y);
	raycasting();
	mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
	//mlx_put_image_to_window(dis.mlx, dis.win, textures[0].img, 0, 0);
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