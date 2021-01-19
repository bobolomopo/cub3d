/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:01:32 by jandre            #+#    #+#             */
/*   Updated: 2020/10/16 20:17:06 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	check_full(char *line, t_param *g_param)
{
	int i;

	i = 0;
	if (line[i] == 'R' && g_param->res_x == 0 && g_param->res_y == 0)
		return (fill_param_res(line + i + 1, g_param));
	if ((line[i] == 'N' && !g_param->text_north) ||
			(line[i] == 'S' && line[i + 1] == 'O' && !g_param->text_south) ||
			(line[i] == 'S' && line[i + 1] == ' ' && !g_param->text_sprite) ||
			(line[i] == 'W' && !g_param->text_west) ||
			(line[i] == 'E' && !g_param->text_east))
		return (fill_param_char(line + i, g_param));
	if ((line[i] == 'F' && g_param->floor_color < 0) ||
			(line[i] == 'C' && g_param->ceiling_color < 0))
		return (fill_param_rgb(line + i + 1, g_param, line[i]));
	return (-8);
}

int			fill_param(char *line, t_param *g_param)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R')
		return (check_full(line, g_param));
	else if ((line[i] == 'N' && line[i + 1] == 'O') ||
			(line[i] == 'S' && line[i + 1] == ' ') ||
			(line[i] == 'S' && line[i + 1] == 'O') ||
			(line[i] == 'W' && line[i + 1] == 'E') ||
			(line[i] == 'E' && line[i + 1] == 'A') ||
			line[i] == 'F' || line[i] == 'C')
		return (check_full(line + i, g_param));
	return (-2);
}
