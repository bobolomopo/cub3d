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

int             fill_param_map(int fd)
{
    char    *line[1];
    int     ret;
    char    *map[100];
    int     i;
    int     j;

    i = 0;
    while ((ret = get_next_line(fd, line)))
    {
        if (!(map[i] = ft_strnew(ft_strlen(*line) + 1)))
            return (-1);
        j = 0;
        if (verif(*line) < 0)
        {
            free(*line);
            return (-1);
        }
        ft_strcpy(map[i], *line);
        free(*line);
        i++;
    }
    i = 0;
    while (map[i])
        printf("%s\n", map[i++]);
    return (0);
}
