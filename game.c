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

#include "include/cub3d.h"

int		main(int argc, char **argv)
{
	if (argc != 1)
	{
		if (argc > 2 || ft_strcmp(argv[1], "--save") != 0)
			return (0);
	}
	g_param.dis.mlx = mlx_init();
	if (initialize(&g_param) < 0)
		return (-1);
	g_param.dis.win = mlx_new_window(g_param.dis.mlx, g_param.res_x,
			g_param.res_y, "Cub3D");
	g_param.game.img = mlx_new_image(g_param.dis.mlx, g_param.res_x,
			g_param.res_y);
	g_param.game.addr = mlx_get_data_addr(g_param.game.img,
			&g_param.game.bits_per_pixel, &g_param.game.line_length,
			&g_param.game.endian);
	draw_ceil_floor(g_param.res_x, g_param.res_y);
	raycasting();
	mlx_put_image_to_window(g_param.dis.mlx, g_param.dis.win,
			g_param.game.img, 0, 0);
	if (argv[1] && ft_strcmp(argv[1], "--save") == 0)
		create_image();
	mlx_hook(g_param.dis.win, 2, 1L << 0, manage_key, &g_param.dis);
	mlx_loop(g_param.dis.mlx);
	return (0);
}
