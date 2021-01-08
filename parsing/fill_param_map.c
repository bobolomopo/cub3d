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

#include "../include/cub3D.h"

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

static int		fill_map(char **map, t_param *param)
{
	int		y;

	y = 0;
	while (map[y] != NULL)
		y++;
	if (!(param->map = malloc(sizeof(char *) * y + 1)))
		return (-1);
	y = 0;
	while (map[y])
	{
		if (!(param->map[y] = malloc(sizeof(char) * ft_strlen(map[y]) + 1)))
			return (-1);
		ft_strcpy(param->map[y], map[y]);
		y++;
	}
	param->map[y] = NULL;
	while (y-- > 0)
		free(map[y]);
	return (1);
}

static int		valid_c(char **map, int i, int j, int start)
{
	if (ft_isin(map[i][j], "NESW") > 0)
	{
		if (start == 1)
			return (-1);
		start = 1;
	}
	if (!(map[i][j + 1]) || (ft_isin(map[i][j + 1], "012NESW") < 0))
		return (-1);
	if (!(map[i][j - 1]) || (ft_isin(map[i][j - 1], "012NESW") < 0))
		return (-1);
	if (!(map[i + 1][j]) || (ft_isin(map[i + 1][j], "012NESW") < 0))
		return (-1);
	if (!(map[i - 1][j]) || (ft_isin(map[i - 1][j], "012NESW") < 0))
		return (-1);
	return (1);
}

static int		verif_open(char **map, t_param *param)
{
	int		i;
	int		j;
	int		start;

	start = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (j < ft_strlen(map[i]))
		{
			if (ft_isin(map[i][j], " 012NESW") < 0)
				return (parsing_error(NULL, -7));
			if (ft_isin(map[i][j], "02NESW") > 0)
			{
				if (valid_c(map, i, j, start) < 0)
					return (parsing_error(NULL, -7));
			}
			j++;
		}
		i++;
	}
	return (fill_map(map, param));
}

int				fill_param_map(int fd, t_param *param)
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
	return (verif_open(map, param));
}
