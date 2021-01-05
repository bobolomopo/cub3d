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

static int	check_full(char *line, t_param *param)
{
	int i;

	i = 0;
	if (line[i] == 'R' && param->res_x == 0 && param->res_y == 0)
		return (fill_param_res(line + i + 1, param));
	if ((line[i] == 'N' && !param->text_north) ||
			(line[i] == 'S' && line[i + 1] == 'O' && !param->text_south) ||
			(line[i] == 'S' && line[i + 1] == ' ' && !param->text_sprite) ||
			(line[i] == 'W' && !param->text_west) ||
			(line[i] == 'E' && !param->text_east))
		return (fill_param_char(line + i, param));
	if ((line[i] == 'F' && param->floor_color < 0) ||
			(line[i] == 'C' && param->ceiling_color < 0))
		return (fill_param_rgb(line + i + 1, param, line[i]));
	return (-8);
}

int			fill_param(char *line, t_param *param)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R')
		return (check_full(line, param));
	else if ((line[i] == 'N' && line[i + 1] == 'O') ||
			(line[i] == 'S' && line[i + 1] == ' ') ||
			(line[i] == 'S' && line[i + 1] == 'O') ||
			(line[i] == 'W' && line[i + 1] == 'E') ||
			(line[i] == 'E' && line[i + 1] == 'A') ||
			line[i] == 'F' || line[i] == 'C')
		return (check_full(line + i, param));
	return (-2);
}
