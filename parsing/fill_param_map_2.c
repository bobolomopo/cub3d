/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_param_map_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:36:59 by jandre            #+#    #+#             */
/*   Updated: 2021/01/25 15:37:00 by jandre           ###   ########.fr       */
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
