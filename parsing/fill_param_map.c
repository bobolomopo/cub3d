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

/*
**on verifie si la ligne n'est composee que de caracteres autorise dans la map
*/

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

/*
**on remplit la parametre map et on oublie pas de free les str qui ont ete
**allouee
*/

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

/*
**on verifie si le caractere est bien autorise et si la map est fermee en
**verifiant tout les caractere quie l'entoure, il ne peut etre entoure que
**par un mur ou alors par un autre espace vide, sinon la map n'est pas
**valide
*/

static int		valid_c(char **map, int *i, t_param *param)
{
	if (ft_isin(map[i[0]][i[1]], "NESW") > 0)
	{
		if (i[2] == 1)
			return (-1);
		param->pos_x = i[0];
		param->pos_y = i[1];
		direction(map[i[0]][i[1]], param);
		i[2] = 1;
	}
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

/*
**verification si la map est ouverte, en deux partie avec la fonction
**statique valic_c
*/

static int		verif_open(char **map, t_param *param)
{
	int		i[3];

	i[2] = 0;
	i[0] = 0;
	while (map[i[0]])
	{
		i[1] = 0;
		while (i[1] < ft_strlen(map[i[0]]))
		{
			if (ft_isin(map[i[0]][i[1]], " 012NESW") < 0)
				return (parsing_error(NULL, -7));
			if (ft_isin(map[i[0]][i[1]], "02NESW") > 0)
			{
				if (valid_c(map, i, param) < 0)
					return (parsing_error(NULL, -7));
			}
			i[1]++;
		}
		i[0]++;
	}
	return (fill_map(map, param));
}

/*
**fonction principale pour remplir la parametre de map, va remplir
**le param map, les directino et positions de depart du joueur
*/

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
