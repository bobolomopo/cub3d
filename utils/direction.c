/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:47:28 by jandre            #+#    #+#             */
/*   Updated: 2021/01/08 14:47:32 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	direction(char c, t_param *param)
{
	param->dir_x = 0;
	param->dir_y = 0;
	if (c == 'N')
	{
		param->dir_x = -1;
		planeX = 0;
		planeY = 0.66;
	}
	if (c == 'S')
	{
		param->dir_x = 1;
		planeX = 0;
		planeY = -0.66;
	}
	if (c == 'W')
	{
		param->dir_y = -1;
		planeX = -0.66;
		planeY = 0;
	}
	if (c == 'E')
	{
		param->dir_y = 1;
		planeX = 0.66;
		planeY = 0;
	}
}