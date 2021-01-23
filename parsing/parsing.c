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
	return (fill_param_map(fd, g_param));
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
		while (*line[i])
		{
			if (*line[i] != ' ')
				return (parsing_error(ptr, -7));
			i++;
		}
		printf("%s\n", *line);
		free(ptr);
		if (ret == 0)
			break ;
	}
	return (1);
}

