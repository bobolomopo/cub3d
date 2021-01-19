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

#include "../include/cub3d.h"

int		fill_param_char(char *line, t_param *g_param)
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
		if (c == 'N' && !g_param->text_north)
			g_param->text_north = fill_char(line + i);
		if (c == 'S' && c2 == 'O' && !g_param->text_south)
			g_param->text_south = fill_char(line + i);
		if (c == 'W' && !g_param->text_west)
			g_param->text_west = fill_char(line + i);
		if (c == 'E' && !g_param->text_east)
			g_param->text_east = fill_char(line + i);
		if (c == 'S' && c2 == ' ' && !g_param->text_sprite)
			g_param->text_sprite = fill_char(line + i);
		return (1);
	}
	return (-4);
}
