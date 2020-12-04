/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_param_rgb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:16:47 by jandre            #+#    #+#             */
/*   Updated: 2020/10/16 20:17:44 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	is_a_coma_before(char *line, int i)
{
	i--;
	while (i > 0 && ft_isdigit((int)line[i]) < 0)
	{
		if (line[i] == ',')
			return (1);
		i--;
	}
	return (-1);
}

static int	transform_RGB(char *line, t_param *param, char c)
{
	int 	red;
	int		green;
	int		blue;
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	red = atoi(line);
	if (ft_nbrlen(red) > 3 || red > 255)
		return (-1);
	i +=  ft_nbrlen(red);
	while (line[i] && (line[i] == ' ' || line[i] == ','))
		i++;
	green = atoi(line + i);
	if (ft_nbrlen(green) > 3 || green > 255)
		return (-1);
	i +=  ft_nbrlen(green);
	while (line[i] && (line[i] == ' ' || line[i] == ','))
		i++;
	blue = atoi(line + i);
	if (ft_nbrlen(blue) > 3 || blue > 255)
		return (-1);
	i +=  ft_nbrlen(blue);
	while (line[i] && line[i] == ' ')
	{
		i++;
		if (line[i] != ' ')
			return (-1);
	}
	if (c == 'F')
		param->floor_color = (red << 16) + (green << 8) + blue;
	if (c == 'C')
		param->ceiling_color = (red << 16) + (green << 8) + blue;
	return (1);
}

int			fill_param_rgb(char *line, t_param *param, char c)
{
	int		i;
	int 	count_coma;
	int		count_space;

	i = 0;
	count_coma = 0;
	count_space = 0;
	if (param->ceiling_color != 0 || param->ceiling_color != 0)
		return (-1);
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i])
	{
		if (ft_isdigit((int)line[i]) < 0 && line[i] != ',' && line[i] != '\n'
				&& line[i] != ' ')
			return (-1);
		if (ft_isdigit((int)line[i]) > 0 && is_a_coma_before(line, i) > 0)
			count_coma++;
		i++;
	}
	if (count_coma != 2)
		return (-1);
	return (transform_RGB(line, param, c));
}
