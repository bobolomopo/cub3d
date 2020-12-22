/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_param_res.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 14:49:21 by jandre            #+#    #+#             */
/*   Updated: 2020/10/16 19:55:50 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	check_res(int *x, int *y)
{
	if (x < 0 || y < 0)
		return (-1);
	if (*x > 1980)
		*x = 1980;
	if (*y > 1080)
		*y = 1080;
	return (1);
}

int			fill_param_res(char *line, t_param *param)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	if (param->res_y != 0 || param->res_x != 0)
		return (-1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '2' && line[i] != '3'
				&& line[i] != '4' && line[i] != '5' && line[i] != '6' &&
				line[i] != '7' && line[i] != '8' && line[i] != '9' &&
				line[i] != '0' && line[i] != '\n')
		{
			return (-1);
		}
		if (ft_isdigit((int)line[i]) > 0 && line[i - 1] == ' ')
			count++;
		i++;
	}
	i = 0;
	if (count != 2)
		return (-1);
	param->res_x = ft_atoi(line);
	while (line[i] == ' ')
		i++;
	while (ft_isdigit((int)line[i]) > 0)
		i++;
	param->res_y = ft_atoi(line + i);
	return (check_res(&param->res_x, &param->res_y));
}
