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

int		fill_param(char *line, t_param *param)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R')
		return (fill_param_res(line + i + 1, param));
	else if ((line[i] == 'N' && line[i + 1] == 'O') ||
			(line[i] == 'S' && line[i + 1] == ' ') ||
			(line[i] == 'S' && line[i + 1] == 'O') ||
			(line[i] == 'W' && line[i + 1] == 'E') ||
			(line[i] == 'E' && line[i + 1] == 'A'))
		return (fill_param_char(line + i, param));
	else if (line[i] == 'F' || line[i] == 'C')
		return (fill_param_rgb(line + i + 1, param, line[i]));
	return (-1);
}
