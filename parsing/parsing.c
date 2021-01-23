/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:12:57 by jandre            #+#    #+#             */
/*   Updated: 2020/10/16 20:17:27 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int		ch_comp_param(char c)
{
	if (c == 'R' || c == 'N' || c == 'S' || c == 'W' ||
			c == 'E' || c == 'F' || c == 'C')
		return (1);
	else if (c == '1')
		return (0);
	return (-1);
}

static int		is_param_fill(t_param *g_param)
{
	if (g_param->res_x != 0 && g_param->res_y != 0
				&& g_param->text_north && g_param->text_south &&
				g_param->text_west &&
				g_param->text_east && g_param->text_sprite &&
				g_param->floor_color >= 0
				&& g_param->ceiling_color >= 0)
		return (1);
	else
		return (-1);
}

int				parsing(int fd, t_param *g_param)
{
	char	*line[1];
	int		ret;
	char	*ptr;

	ret = 1;
	if (is_param_fill(g_param))
	{
		while ((is_param_fill(g_param) < 0 && (ret = get_next_line(fd, line))))
		{
			ptr = *line;
			while (**line == ' ' || **line == '\n')
				*line += 1;
			if (**line && ch_comp_param(**line) == -1)
				return (parsing_error(ptr, -2));
			if (**line && ch_comp_param(**line) == 1)
			{
				if ((ret = fill_param(*line, g_param)) < 0)
					return (parsing_error(ptr, ret));
			}
			free(ptr);
		}
	}
	if (is_param_fill(g_param) < 0)
		return (parsing_error(NULL, -3));
	return (get_to_map(fd));
}

int		get_to_map(int fd)
{
	char	*line[1];
	char	*ptr;
	int		ret;
	int		i;

	while (((ret = get_next_line(fd, line)) >= 0) && ft_isin_str("102NESW", *line) < 0)
	{
		ptr = *line;
		i = 0;
		while (line[0][i])
		{
			if (line[0][i] != ' ')
				return (parsing_error(ptr, -7));
			i++;
		}
		free(ptr);
		if (ret == 0)
			break ;
	}
	return (copy_map(fd, line[0]));
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

int		copy_map(int fd, char *str)
{
	int		i;
	int		j;
	char	*map[MAXMAPSIZE];
	char	*line[1];
	char	*ptr;
	int		ret;

	g_param.is_start = 0;
	if (!str)
		return (parsing_error(NULL, -7));
	i = 1;
	if (!(map[0] = malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (parsing_error(str, -1));
	ft_strcpy(map[0], str);
	free(str);
	while ((ret = get_next_line(fd, line)) >= 0)
	{
		if (i == MAXMAPSIZE)
			return (free_map_buffer(i, map, 1));
		if (!line[0][0])
			return (free_map_buffer(i, map, 2));
		ptr = *line;
		j = 0;
		while (line[0][j])
		{
			if (ft_isin(line[0][j], " 012NESW") < 0)
				return (parsing_error(ptr, -7));
			if (ft_isin(line[0][j], "NESW") > 0)
			{
				if (g_param.is_start == 1)
					return (free_map_buffer(i, map, 2));
				g_param.is_start = 1;
				g_param.map_start_x = j;
				g_param.map_start_y = i;
				direction(line[0][j], &g_param);
				line[0][j] = '0';
			}
			j++;
		}
		if (!(map[i] = malloc(sizeof(char) * ft_strlen(line[0]) + 1)))
			return (parsing_error(line[0], -1));
		ft_strcpy(map[i], line[0]);
		free(ptr);
		i++;
		if (ret == 0)
			break ;
	}
	map[i] = NULL;
	g_param.map_h = i;
	if ((flood_fill(map, g_param.map_start_x, g_param.map_start_y)) < 0)
		return (free_map_buffer(g_param.map_h, map, 2));
	i = 0;
	g_param.num_sprite = 0;
	while (map[i] != NULL)
	{
		if (!(g_param.map[i] = malloc(sizeof(char) * ft_strlen(map[i]) + 1)))
			return (parsing_error(NULL, -1));
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'F')
				map[i][j] = '0';
			if (map[i][j] == 'S')
				map[i][j] = '2';
			j++;
		}
		ft_strcpy(g_param.map[i], map[i]);
		printf("%s\n", g_param.map[i]);
		free(map[i]);
		i++;
	}
	g_param.map[i] = NULL;
	return (1);
}

int		flood_fill(char **map, int start_x, int start_y)
{
	if (map[start_y][start_x] == '0')
		map[start_y][start_x] = 'F';
	if (map[start_y][start_x] == '2')
	{
		g_param.num_sprite += 1;
		map[start_y][start_x] = 'S';
	}
	if (start_x + 1 < ft_strlen(map[start_y]) &&
		map[start_y][start_x + 1] && (map[start_y][start_x + 1] == '0'
		|| map[start_y][start_x + 1] == '2'))
		flood_fill(map, start_x + 1, start_y);
	if (start_x + 1 >= ft_strlen(map[start_y])
	|| map[start_y][start_x + 1] == ' ')
		return (-1);
	if ((start_x - 1 >= 0) &&
		map[start_y][start_x - 1]
		&& (map[start_y][start_x - 1] == '0'
		|| map[start_y][start_x - 1] == '2'))
		flood_fill(map, start_x - 1, start_y);
	if (start_x - 1 < 0 || map[start_y][start_x - 1] == ' ')
		return (-1);
	if ((map[start_y + 1]) && start_x < ft_strlen(map[start_y + 1]) &&
		map[start_y + 1][start_x] && (map[start_y + 1][start_x] == '0'
			|| map[start_y + 1][start_x] == '2'))
		flood_fill(map, start_x, start_y + 1);
	if (!(map[start_y + 1]) || start_x >= ft_strlen(map[start_y + 1]) ||
		map[start_y + 1][start_x] == ' ')
		return (-1);
	if (map[start_y - 1] && start_x < ft_strlen(map[start_y - 1]) &&
		(map[start_y - 1][start_x] == '0'
		|| map[start_y - 1][start_x] == '2'))
		flood_fill(map, start_x, start_y - 1);
	if (!map[start_y - 1] || start_x >= ft_strlen(map[start_y - 1]) ||
		map[start_y - 1][start_x] == ' ')
		return (-1);
	return (1);
}