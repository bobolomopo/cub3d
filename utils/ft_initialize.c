/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:19:49 by jandre            #+#    #+#             */
/*   Updated: 2021/01/16 16:19:51 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int			text_error(int a)
{
	if (a == 1)
		write(1, "error : mauvaise texture sud\n", 29);
	if (a == 2)
		write(1, "error : mauvaise texture nord\n", 30);
	if (a == 3)
		write(1, "error : mauvaise texture est\n", 29);
	if (a == 4)
		write(1, "error : mauvaise texture ouest\n", 31);
	if (a == 5)
		write(1, "error : mauvaise texture sprite\n", 32);
	return (-1);
}

static int			test_structure2(void)
{
	g_param.textures[2].addr = mlx_get_data_addr(g_param.textures[2].img,
								&g_param.textures[2].bits_per_pixel,
								&g_param.textures[2].line_length,
								&g_param.textures[2].endian);
	if (!(g_param.textures[3].img = mlx_xpm_file_to_image(g_param.dis.mlx,
								g_param.text_west,
								&g_param.textures[3].width,
								&g_param.textures[3].height)))
		return (text_error(4));
	g_param.textures[3].addr = mlx_get_data_addr(g_param.textures[3].img,
								&g_param.textures[3].bits_per_pixel,
								&g_param.textures[3].line_length,
								&g_param.textures[3].endian);
	if (!(g_param.textures[4].img = mlx_xpm_file_to_image(g_param.dis.mlx,
								g_param.text_sprite,
								&g_param.textures[4].width,
								&g_param.textures[4].height)))
		return (text_error(5));
	g_param.textures[4].addr = mlx_get_data_addr(g_param.textures[4].img,
								&g_param.textures[4].bits_per_pixel,
								&g_param.textures[4].line_length,
								&g_param.textures[4].endian);
	return (1);
}

static int			test_structure(void)
{
	if (!((g_param.textures[0].img) = mlx_xpm_file_to_image(g_param.dis.mlx,
								g_param.text_south,
								&(g_param.textures[0].width),
								&(g_param.textures[0].height))))
		return (text_error(1));
	g_param.textures[0].addr = mlx_get_data_addr(g_param.textures[0].img,
								&g_param.textures[0].bits_per_pixel,
								&g_param.textures[0].line_length,
								&g_param.textures[0].endian);
	if (!(g_param.textures[1].img = mlx_xpm_file_to_image(g_param.dis.mlx,
								g_param.text_north,
								&g_param.textures[1].width,
								&g_param.textures[1].height)))
		return (text_error(2));
	g_param.textures[1].addr = mlx_get_data_addr(g_param.textures[1].img,
								&g_param.textures[1].bits_per_pixel,
								&g_param.textures[1].line_length,
								&g_param.textures[1].endian);
	if (!(g_param.textures[2].img = mlx_xpm_file_to_image(g_param.dis.mlx,
								g_param.text_east,
								&g_param.textures[2].width,
								&g_param.textures[2].height)))
		return (text_error(3));
	return (test_structure2());
}

static void			all_to_zero(void)
{
	g_param.res_x = 0;
	g_param.res_y = 0;
	g_param.text_north = NULL;
	g_param.text_south = NULL;
	g_param.text_east = NULL;
	g_param.text_west = NULL;
	g_param.floor_color = -1;
	g_param.ceiling_color = -1;
	g_param.text_sprite = NULL;
	g_param.map = NULL;
	g_param.num_sprite = 0;
	g_param.pos_x = 0;
	g_param.pos_y = 0;
	g_param.dir_x = 0;
	g_param.dir_y = 0;
}

int					initialize(t_param *g_param)
{
	g_param->fd = open("./test.cub", O_RDONLY);
	all_to_zero();
	if (parsing(g_param->fd, g_param) < 0)
		return (-1);
	if (test_structure() < 0)
		return (-1);
	return (1);
}
