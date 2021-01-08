/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:12:57 by jandre            #+#    #+#             */
/*   Updated: 2020/10/16 20:17:27 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int		ch_comp_param(char c)
{
	if (c == 'R' || c == 'N' || c == 'S' || c == 'W' ||
			c == 'E' || c == 'F' || c == 'C')
		return (1);
	else if (c == '1')
		return (0);
	return (-1);
}

static int		is_param_filled(t_param *param)
{
	if (param->res_x != 0 && param->res_y != 0
			&& param->text_north && param->text_south && param->text_west &&
			param->text_east && param->text_sprite && param->floor_color >= 0
			&& param->ceiling_color >= 0)
		return (1);
	else
		return (-1);
}

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

int				parsing(int fd, t_param *param)
{
	char	*line[1];
	int		ret;
	char	*ptr;

	ret = 1;
	if (is_param_filled(param))
	{
		while ((is_param_filled(param) < 0 && (ret = get_next_line(fd, line))))
		{
			ptr = *line;
			while (**line == ' ' || **line == '\n')
				*line += 1;
			if (**line && ch_comp_param(**line) == -1)
				return (parsing_error(ptr, -2));
			if (**line && ch_comp_param(**line) == 1)
			{
				if ((ret = fill_param(*line, param)) < 0)
					return (parsing_error(ptr, ret));
			}
			free(ptr);
		}
	}
	if (is_param_filled(param) < 0)
		return (parsing_error(NULL, -3));
	return (fill_param_map(fd, param));
}