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

static void			direction_we(char c, t_param *param)
{
	if (c == 'W')
	{
		param->dir_y = -1;
		plane_x = -0.66;
		plane_y = 0;
	}
	if (c == 'E')
	{
		param->dir_y = 1;
		plane_x = 0.66;
		plane_y = 0;
	}
}

static void			direction_ns(char c, t_param *param)
{
	if (c == 'N')
	{
		param->dir_x = -1;
		plane_x = 0;
		plane_y = 0.66;
	}
	if (c == 'S')
	{
		param->dir_x = 1;
		plane_x = 0;
		plane_y = -0.66;
	}
}

void				direction(char c, t_param *param)
{
	param->dir_x = 0;
	param->dir_y = 0;
	direction_we(c, param);
	direction_ns(c, param);
}
