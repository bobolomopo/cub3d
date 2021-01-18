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

int main(int argc, char **argv)
{
	if (argc != 1)
	{
		if (argc > 2 || ft_strcmp(argv[1], "--save") != 0)
			return (0);
	}
	printf("%s", argv[1]);
	dis.mlx = mlx_init();
	if (initialize(&param) < 0)
        return (-1);
	posX = param.pos_x;
	posY = param.pos_y;
	dirX = param.dir_x;
	dirY = param.dir_y;
	int i = 0;
	dis.win = mlx_new_window(dis.mlx, param.res_x, param.res_y, "Cub3D");
	game.img.img = mlx_new_image(dis.mlx, param.res_x, param.res_y);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);
	draw_ceil_floor(param.res_x, param.res_y);
	raycasting();
	mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
	if (argv[1] && ft_strcmp(argv[1], "--save") == 0)
		create_image();
	mlx_hook(dis.win, 2, 1L<<0, manage_key, &dis);
    mlx_loop(dis.mlx);
	return (0);
}
