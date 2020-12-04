/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_param_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:03:12 by jandre            #+#    #+#             */
/*   Updated: 2020/10/16 18:07:59 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int		fill_param_char(char *line, t_param *param)
{
	int		i;
	char	c;
	char	c2;

	i = 0;
	c = line[i];
	c2 = line[i + 1];
	i += 2;
	while (line[i] == ' ')
		i++;
	if (line[i] != ' ')
	{
		if (c == 'N' && !param->text_north)
			param->text_north = fill_char(line + i);
		if (c == 'S' && c2 == 'O' && !param->text_south)
			param->text_south = fill_char(line + i);
		if (c == 'W' && !param->text_west)
			param->text_west = fill_char(line + i);
		if (c == 'E' && !param->text_east)
			param->text_east = fill_char(line + i);
		if (c == 'S' && c2 == ' ' && !param->text_sprite)
			param->text_sprite = fill_char(line + i);
		return (1);
	}
	return (-1);
}
