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

static int     verif(char *line)
{
    int     i;

    i = 0;
    while (line[i++])
    {
        if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != '2'
                &&line[i] != '\0')
            return (-1);
    }
    return (1);
}

static int      verif_open(char **map)
{
    int     i;
    int     j;
    int     start;

    start = 0;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ' && map[i][j] != '2')
                return (-1);
            if (map[i][j] == '0' || map[i][j] == '2')
            {
                if (map[i][j] == '2')
                {
                    if (start == 1)
                        return (-1);
                    start = 1;
                }
                if (!(map[i][j + 1]) || (map[i][j + 1] != '0' && map[i][j + 1] != '1' && map[i][j + 1] != '2'))
                    return (-1);
                if (!(map[i][j - 1]) || (map[i][j - 1] != '0' && map[i][j - 1] != '1' && map[i][j - 1] != '2'))
                    return (-1);
                if (!(map[i + 1][j]) || (map[i + 1][j] != '0' && map[i + 1][j] != '1' && map[i + 1][j] != '2'))
                    return (-1);
                if (!(map[i - 1][j]) || (map[i - 1][j] != '0' && map[i - 1][j] != '1' && map[i - 1][j] != '2'))
                    return (-1);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int             fill_param_map(int fd)
{
    char    *line[1];
    int     ret;
    char    *map[100];
    int     i;

    i = 0;
    while ((ret = get_next_line(fd, line)) >= 0)
    {
        if (!(map[i] = ft_strnew(ft_strlen(*line) + 1)))
            return (-1);
        if (verif(*line) < 0)
        {
            free(*line);
            return (-1);
        }
        if (*line)
            ft_strcpy(map[i], *line);
        free(*line);
        i++;
        if (ret == 0)
            break ;
    }
    i = 0;
    return (verif_open(map));
}
