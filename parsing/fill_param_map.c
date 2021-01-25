/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_param_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:36:25 by jandre            #+#    #+#             */
/*   Updated: 2020/12/22 17:36:31 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		get_to_map(int fd)
{
	char	*line[1];
	char	*ptr;
	int		ret;
	int		i;

	while (((ret = get_next_line(fd, line)) >= 0) &&
		ft_isin_str("102NESW", *line) < 0)
	{
		ptr = *line;
		i = 0;
		while (line[0][i])
		{
			if (line[0][i] != ' ')
				return (parsing_error(ptr, -7));
			i++;
		}
		if (ret == 0)
			break ;
		free(ptr);
	}
	return (copy_map(fd, line[0], ret));
}

int		free_map_buffer(int i, char **map, int ret)
{
	while (i >= 0)
	{
		free(map[i]);
		i--;
	}
	if (ret == 1)
		return (parsing_error(NULL, -9));
	return (parsing_error(NULL, -7));
}

int		fill_map(char **map)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i] != NULL)
	{
		if (!(g_param.map[i] = malloc(sizeof(char) * ft_strlen(map[i]) + 1)))
			return (parsing_error(NULL, -1));
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'F')
				map[i][j] = '0';
			if (map[i][j] == 'S' || map[i][j] == '2')
			{
				g_param.num_sprite += 1;
				map[i][j] = '2';
			}
			j++;
		}
		ft_strcpy(g_param.map[i], map[i]);
		free(map[i]);
	}
	g_param.map[i] = NULL;
	return (1);
}

int		define_start(char *str, int i)
{
	int		j;

	j = 0;
	while (str[j])
	{
		if (ft_isin(str[j], " 012NESW") < 0)
			return (-1);
		if (ft_isin(str[j], "NESW") > 0)
		{
			if (g_param.is_start == 1)
				return (-1);
			g_param.is_start = 1;
			g_param.map_start_x = j;
			g_param.map_start_y = i;
			direction(str[j], &g_param);
			str[j] = '0';
		}
		j++;
	}
	return (1);
}

int		copy_first_line(char *str, char **map, int ret)
{
	g_param.is_start = 0;
	if (!str)
		return (parsing_error(NULL, -7));
	if (!(map[0] = malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (parsing_error(str, -1));
	ft_strcpy(map[0], str);
	free(str);
	if (ret <= 0)
		return (parsing_error(NULL, -7));
	return (1);
}

int		copy_map2(int fd, char **map, int ret)
{
	char	*line[1];
	int		i;
	char	*ptr;

	i = 1;
	while ((ret = get_next_line(fd, line)) >= 0)
	{
		if (i == MAXMAPSIZE)
			return (free_map_buffer(i, map, 1));
		if (!line[0][0])
			return (free_map_buffer(i, map, 2));
		ptr = *line;
		if (define_start(line[0], i) < 0)
			return (free_map_buffer(i, map, 2));
		if (!(map[i] = malloc(sizeof(char) * ft_strlen(line[0]) + 1)))
			return (parsing_error(line[0], -1));
		ft_strcpy(map[i], line[0]);
		free(ptr);
		i++;
		if (ret == 0)
			break ;
	}
	return (i);
}

int		copy_map(int fd, char *str, int ret)
{
	int		i;
	char	*map[MAXMAPSIZE];
	char	*line[1];
	char	*ptr;

	copy_first_line(str, map, ret);
	i = 1;
	i = copy_map2(fd, map, ret);
	map[i] = NULL;
	g_param.map_h = i;
	g_param.num_sprite = 0;
	if (g_param.is_start == 0)
		return (free_map_buffer(i, map, 2));
	if ((flood_fill(map, g_param.map_start_x, g_param.map_start_y)) < 0)
		return (free_map_buffer(g_param.map_h, map, 2));
	return (fill_map(map));
}