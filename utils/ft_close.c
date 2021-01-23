/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:03:03 by jandre            #+#    #+#             */
/*   Updated: 2021/01/16 16:03:05 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int				parsing_error(char *ptr, int ret)
{
	if (ret == -1)
		write(1, "Error\nallocation de mémoire\n", 28);
	if (ret == -2)
		write(1, "Error\ncaractere non autorise\n", 29);
	if (ret == -3)
		write(1, "Error\nmanque des parametres\n", 28);
	if (ret == -4)
		write(1, "Error\nfichier de texture non valide\n", 37);
	if (ret == -5)
		write(1, "Error\nparametre RGB non valide\n", 32);
	if (ret == -6)
		write(1, "Error\nparametre resolution non valide\n", 38);
	if (ret == -7)
		write(1, "Error\nMAP non valide\n", 21);
	if (ret == -8)
		write(1, "Error\ndoublon de parametre\n", 27);
	if (ret == -9)
		write(1, "Error\nmap trop longue\n", 22);
	free(ptr);
	return (ft_close());
}

int				msg_error(int ret)
{
	if (ret == 1)
		write(1, "Error\nmauvais nombre d'arguments\n", 33);
	if (ret == 2)
		write(1, "Error\nfichier .cub non valide\n", 30);
	return (ft_close());
}

static void		destroy_images(void)
{
	if (g_param.textures[0].img)
		mlx_destroy_image(g_param.dis.mlx, g_param.textures[0].img);
	if (g_param.textures[1].img)
		mlx_destroy_image(g_param.dis.mlx, g_param.textures[1].img);
	if (g_param.textures[2].img)
		mlx_destroy_image(g_param.dis.mlx, g_param.textures[2].img);
	if (g_param.textures[3].img)
		mlx_destroy_image(g_param.dis.mlx, g_param.textures[3].img);
	if (g_param.textures[4].img)
		mlx_destroy_image(g_param.dis.mlx, g_param.textures[4].img);
	if (g_param.game.img)
		mlx_destroy_image(g_param.dis.mlx, g_param.game.img);
	if (g_param.dis.win)
		mlx_destroy_window(g_param.dis.mlx, g_param.dis.win);
}

int				ft_close(void)
{
	int		i;

	i = MAXMAPSIZE;
	if (g_param.fd)
		close(g_param.fd);
	if (g_param.text_north)
		free(g_param.text_north);
	if (g_param.text_west)
		free(g_param.text_west);
	if (g_param.text_east)
		free(g_param.text_east);
	if (g_param.text_sprite)
		free(g_param.text_sprite);
	if (g_param.text_south)
		free(g_param.text_south);
	while (i-- > 0)
	{
		if (g_param.map[i])
			free(g_param.map[i]);
	}
	destroy_images();
	exit(0);
}
