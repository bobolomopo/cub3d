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

#include "../include/cub3d.h"

static int	check_res(int x, int y)
{
	mlx_get_screen_size(g_param.dis.mlx, &g_param.max_res_x,
		&g_param.max_res_y);
	if (x == 0 || y == 0)
		return (-6);
	if (x > g_param.max_res_x || x < 0)
		g_param.res_x = g_param.max_res_x;
	if (y > g_param.max_res_y || y < 0)
		g_param.res_y = g_param.max_res_y;
	return (1);
}

int			fill_param_res(char *line, t_param *g_param)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] != ' ' && ft_isdigit(line[i]) < 0)
			return (-6);
		if (ft_isdigit((int)line[i]) > 0 && line[i - 1] == ' ')
			count++;
		i++;
	}
	i = 0;
	if (count != 2)
		return (-6);
	g_param->res_x = ft_atoi(line);
	while (line[i] == ' ')
		i++;
	while (ft_isdigit((int)line[i]) > 0)
		i++;
	g_param->res_y = ft_atoi(line + i);
	return (check_res(g_param->res_x, g_param->res_y));
}
