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

static void			direction_we(char c, t_param *g_param)
{
	if (c == 'W')
	{
		g_param->dir_y = -1;
		plane_x = -0.66;
		plane_y = 0;
	}
	if (c == 'E')
	{
		g_param->dir_y = 1;
		plane_x = 0.66;
		plane_y = 0;
	}
}

static void			direction_ns(char c, t_param *g_param)
{
	if (c == 'N')
	{
		g_param->dir_x = -1;
		plane_x = 0;
		plane_y = 0.66;
	}
	if (c == 'S')
	{
		g_param->dir_x = 1;
		plane_x = 0;
		plane_y = -0.66;
	}
}

void				direction(char c, t_param *g_param)
{
	g_param->dir_x = 0;
	g_param->dir_y = 0;
	direction_we(c, g_param);
	direction_ns(c, g_param);
}
