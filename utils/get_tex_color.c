/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tex_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:44:07 by jandre            #+#    #+#             */
/*   Updated: 2021/01/16 16:44:08 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		get_tex_color(t_img *tex, int x, int y)
{
	char				*dst;
	unsigned int		color;

	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	color = (*(unsigned int*)dst);
	return (color);
}
