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

#include "../include/cub3d.h"

static int	is_a_coma_before(char *line, int i)
{
	i--;
	while (i > 0 && ft_isdigit((int)line[i]) < 0)
	{
		if (line[i] == ',')
			return (1);
		i--;
	}
	return (-5);
}

static int	fill_rgb2(char *line, int *color, int i)
{
	if (ft_isdigit(line[i]) < 0)
		return (-5);
	color[1] = atoi(line + i);
	if (ft_nbrlen(color[1]) > 3 || color[1] > 255)
		return (-5);
	i += ft_nbrlen(color[1]);
	while (line[i] && (line[i] == ' ' || line[i] == ','))
		i++;
	if (ft_isdigit(line[i]) < 0)
		return (-5);
	color[2] = atoi(line + i);
	if (ft_nbrlen(color[2]) > 3 || color[2] > 255)
		return (-5);
	i += ft_nbrlen(color[2]);
	return (i);
}

static int	fill_rgb(char *line, int *color)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]) < 0)
		return (-5);
	color[0] = atoi(line);
	if (ft_nbrlen(color[0]) > 3 || color[0] > 255)
		return (-5);
	i += ft_nbrlen(color[0]);
	while (line[i] && (line[i] == ' ' || line[i] == ','))
		i++;
	return (fill_rgb2(line, color, i));
}

static int	transform_rgb(char *line, t_param *g_param, char c)
{
	int		color[3];
	int		i;

	if ((i = fill_rgb(line, color)) < 0)
		return (-5);
	while (line[i] && line[i] == ' ')
	{
		i++;
		if (line[i] != ' ')
			return (-5);
	}
	if (c == 'F')
		g_param->floor_color = (color[0] << 16) + (color[1] << 8) + color[2];
	if (c == 'C')
		g_param->ceiling_color = (color[0] << 16) + (color[1] << 8) + color[2];
	return (1);
}

int			fill_param_rgb(char *line, t_param *g_param, char c)
{
	int		i;
	int		count_coma;
	int		count_space;

	i = 0;
	count_coma = 0;
	count_space = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i])
	{
		if (ft_isdigit((int)line[i]) < 0 && line[i] != ',' && line[i] != '\n'
				&& line[i] != ' ')
			return (-5);
		if (line[i] == ',')
			count_coma++;
		i++;
	}
	if (count_coma != 2)
		return (-5);
	return (transform_rgb(line, g_param, c));
}
