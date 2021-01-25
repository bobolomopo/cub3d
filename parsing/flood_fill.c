/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:49:23 by jandre            #+#    #+#             */
/*   Updated: 2021/01/25 13:49:25 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int		flood_fill3(char **map, int start_x, int start_y)
{
	if ((map[start_y + 1]) && start_x < ft_strlen(map[start_y + 1]) &&
		map[start_y + 1][start_x] && (map[start_y + 1][start_x] == '0'
		|| map[start_y + 1][start_x] == '2'))
	{
		if (flood_fill(map, start_x, start_y + 1) < 0)
			return (-1);
	}
	if (map[start_y - 1] && start_x < ft_strlen(map[start_y - 1]) &&
		(map[start_y - 1][start_x] == '0'
		|| map[start_y - 1][start_x] == '2'))
	{
		if (flood_fill(map, start_x, start_y - 1) < 0)
			return (-1);
	}
	return (1);
}

static int		flood_fill2(char **map, int start_x, int start_y)
{
	if (start_x + 1 < ft_strlen(map[start_y]) &&
		map[start_y][start_x + 1] && (map[start_y][start_x + 1] == '0'
		|| map[start_y][start_x + 1] == '2'))
	{
		if (flood_fill(map, start_x + 1, start_y) < 0)
			return (-1);
	}
	if ((start_x - 1 >= 0) &&
		map[start_y][start_x - 1]
		&& (map[start_y][start_x - 1] == '0'
		|| map[start_y][start_x - 1] == '2'))
	{
		if (flood_fill(map, start_x - 1, start_y) < 0)
			return (-1);
	}
	return (flood_fill3(map, start_x, start_y));
}

int				flood_fill(char **map, int start_x, int start_y)
{
	if (map[start_y][start_x] == '0')
		map[start_y][start_x] = 'F';
	if (map[start_y][start_x] == '2')
		map[start_y][start_x] = 'S';
	if (!map[start_y - 1] || start_x >= ft_strlen(map[start_y - 1]) ||
		!map[start_y - 1][start_x] || map[start_y - 1][start_x] == ' ')
		return (-1);
	if (!(map[start_y + 1]) || start_x >= ft_strlen(map[start_y + 1]) ||
		map[start_y + 1][start_x] == ' ' || !map[start_y + 1][start_x])
		return (-1);
	if (start_x - 1 < 0 || map[start_y][start_x - 1] == ' '
		|| !map[start_y][start_x - 1])
		return (-1);
	if (start_x + 1 >= ft_strlen(map[start_y])
		|| map[start_y][start_x + 1] == ' '
		|| !map[start_y][start_x + 1])
		return (-1);
	return (flood_fill2(map, start_x, start_y));
}
