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
		write(1, "Error\nfichier de texture non valide\n", 38);
	if (ret == -5)
		write(1, "Error\nparametre RGB non valide\n", 31);
	if (ret == -6)
		write(1, "Error\nparametre resolution non valide\n", 38);
	if (ret == -7)
		write(1, "Error\nMAP non valide\n", 21);
	if (ret == -8)
		write(1, "Error\ndoublon de parametre\n", 27);
	if (ret == -9)
		write(1, "Error\nmap trop longue\n", 22);
	free(ptr);
	return (-1);
}

void			ft_close(void)
{
	mlx_destroy_window(g_param.dis.mlx, g_param.dis.win);
	free(g_param.dis.mlx);
	if (g_param.fd)
		close(g_param.fd);
	exit(0);
}
