/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:07:31 by jandre            #+#    #+#             */
/*   Updated: 2020/10/16 14:57:52 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*fill_char(char *line)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	len = i;
	if (!(result = malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = line[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
