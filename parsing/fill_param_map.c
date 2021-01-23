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

static int		verif(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isin(line[i], "012NESW ") < 0 && line[i] != '\0')
			return (-1);
		i++;
	}
	return (1);
}

static int		fill_map(char **map, t_param *g_param)
{
	int		y;

	y = 0;
	while (map[y] != NULL)
		y++;
	if (!(g_param->map = malloc(sizeof(char *) * y + 1)))
		return (-1);
	y = 0;
	while (map[y])
	{
		if (!(g_param->map[y] = malloc(sizeof(char) * ft_strlen(map[y]) + 1)))
			return (-1);
		ft_strcpy(g_param->map[y], map[y]);
		y++;
		if (y > g_param->map_h)
			g_param->map_h = y;
	}
	g_param->map_w = y;
	while (y-- > 0)
		free(map[y]);
	return (1);
}

static int		valid_c(char **map, int *i, t_param *g_param)
{
	if (ft_isin(map[i[0]][i[1]], "NESW") > 0)
	{
		if (i[2] == 1)
			return (-1);
		g_param->pos_x = i[0] + 0.5;
		g_param->pos_y = i[1] + 0.5;
		direction(map[i[0]][i[1]], g_param);
		i[2] = 1;
		map[i[0]][i[1]] = '0';
	}
	if (map[i[0]][i[1]] == '2')
		g_param->num_sprite += 1;
	if (!(map[i[0]][(i[1]) + 1]) ||
		(ft_isin(map[i[0]][(i[1]) + 1], "012NESW") < 0))
		return (-1);
	if (!(map[i[0]][(i[1]) - 1]) ||
		(ft_isin(map[i[0]][(i[1]) - 1], "012NESW") < 0))
		return (-1);
	if (!(map[(i[0]) + 1][i[1]]) ||
		(ft_isin(map[(i[0]) + 1][i[1]], "012NESW") < 0))
		return (-1);
	if (!(map[(i[0]) - 1][i[1]]) ||
		(ft_isin(map[(i[0]) - 1][i[1]], "012NESW") < 0))
		return (-1);
	return (1);
}

static int		verif_open(char **map, t_param *g_param)
{
	int		i[3];

	i[2] = 0;
	i[0] = 0;
	while (map[i[0]])
	{
		i[1] = 0;
		while (i[1] < ft_strlen(map[i[0]]))
		{
			if (!(map[i[0]][i[1]]) ||
				ft_isin(map[i[0]][i[1]], " 012NESW") < 0)
				return (parsing_error(NULL, -7));
			if ((map[i[0]][i[1]]) &&
				ft_isin(map[i[0]][i[1]], "02NESW") > 0)
			{
				if (valid_c(map, i, g_param) < 0)
					return (parsing_error(NULL, -7));
			}
			i[1]++;
		}
		i[0]++;
	}
	return (fill_map(map, g_param));
}

int				fill_param_map(int fd, t_param *g_param)
{
	char	*line[1];
	int		ret;
	char	*map[100];
	int		i;

	i = 0;
	while ((ret = get_next_line(fd, line)) >= 0)
	{
		if (i >= 99)
			return (parsing_error(*line, -9));
		if (verif(*line) < 0)
			return (parsing_error(*line, -7));
		if (*line && **line != '\n' && ft_isin('1', *line) > 0)
		{
			if (!(map[i] = ft_strnew(ft_strlen(*line) + 1)))
				return (-1);
			ft_strcpy(map[i++], *line);
		}
		free(*line);
		if (ret == 0)
			break ;
	}
	map[i] = NULL;
	return (verif_open(map, g_param));
}
