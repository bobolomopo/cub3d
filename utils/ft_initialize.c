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

#include "../include/cub3D.h"

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
	textures[2].addr = mlx_get_data_addr(textures[2].img,
								&textures[2].bits_per_pixel,
								&textures[2].line_length,
								&textures[2].endian);
	if (!(textures[3].img = mlx_xpm_file_to_image(dis.mlx,
								param.text_west,
								&textures[3].width,
								&textures[3].height)))
		return (text_error(4));
	textures[3].addr = mlx_get_data_addr(textures[3].img,
								&textures[3].bits_per_pixel,
								&textures[3].line_length,
								&textures[3].endian);
	if (!(textures[4].img = mlx_xpm_file_to_image(dis.mlx,
								param.text_sprite,
								&textures[4].width,
								&textures[4].height)))
		return (text_error(5));
	textures[4].addr = mlx_get_data_addr(textures[4].img,
								&textures[4].bits_per_pixel,
								&textures[4].line_length,
								&textures[4].endian);
	return (1);
}

static int			test_structure(void)
{
	if (!((textures[0].img) = mlx_xpm_file_to_image(dis.mlx,
								param.text_south,
								&(textures[0].width),
								&(textures[0].height))))
		return (text_error(1));
	textures[0].addr = mlx_get_data_addr(textures[0].img,
								&textures[0].bits_per_pixel,
								&textures[0].line_length,
								&textures[0].endian);
	if (!(textures[1].img = mlx_xpm_file_to_image(dis.mlx,
								param.text_north,
								&textures[1].width,
								&textures[1].height)))
		return (text_error(2));
	textures[1].addr = mlx_get_data_addr(textures[1].img,
								&textures[1].bits_per_pixel,
								&textures[1].line_length,
								&textures[1].endian);
	if (!(textures[2].img = mlx_xpm_file_to_image(dis.mlx,
								param.text_east,
								&textures[2].width,
								&textures[2].height)))
		return (text_error(3));
	return (test_structure2());
}

static void			all_to_zero(void)
{
	param.res_x = 0;
	param.res_y = 0;
	param.text_north = NULL;
	param.text_south = NULL;
	param.text_east = NULL;
	param.text_west = NULL;
	param.floor_color = -1;
	param.ceiling_color = -1;
	param.text_sprite = NULL;
	param.map = NULL;
	param.num_sprite = 0;
	param.pos_x = 0;
	param.pos_y = 0;
	param.dir_x = 0;
	param.dir_y = 0;
}

int					initialize(t_param *param)
{
	fd = open("./test.cub", O_RDONLY);
	all_to_zero();
	if (parsing(fd, param) < 0)
		return (-1);
	if (test_structure() < 0)
		return (-1);
	return (1);
}
