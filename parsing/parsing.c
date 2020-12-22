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

static int		parsing_error(char *ptr)
{
	free(ptr);
	write(1, "Fichier .cub incorrect\n", 23);
	exit(0);
	return (-1);
}

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
			param->text_east && param->text_sprite && param->floor_color != 0
			&& param->ceiling_color != 0)
		return (1);
	else
		return (-1);
}

int				parsing(int fd, t_param *param)
{
	char	*line[1];
	int		ret;
	int		test;
	char	*ptr;

	ret = 1;
	if (is_param_filled(param))
	{	
		while ((ret = get_next_line(fd, line)))
		{
			ptr = *line;
			while (**line == ' ' || **line == '\n')
				*line += 1;
			if (**line && ch_comp_param(**line) == -1)
				return (parsing_error(ptr));
			if (**line && ch_comp_param(**line) == 1)
			{
				if (fill_param(*line, param) < 0)
					return (parsing_error(ptr));
			}
			free(ptr);
		}
	}
	if (is_param_filled(param) < 0)
		return (parsing_error(NULL));
	return (1);
}
