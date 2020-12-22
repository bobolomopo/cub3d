/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 15:35:14 by jandre            #+#    #+#             */
/*   Updated: 2020/10/16 20:04:58 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

int main()
{
	t_param param;
	int fd = open("./test.cub", O_RDONLY);
	param.res_x = 0;
	param.res_y = 0;
	param.text_north = NULL;
	param.text_south = NULL;
	param.text_east = NULL;
	param.text_west = NULL;
	param.floor_color = 0;
	param.ceiling_color = 0;
	param.text_sprite = NULL;
	param.map = "";
	

	parsing(fd, &param);
	printf("%d\n%d\n", param.res_x, param.res_y);
	printf("NORD   : |%s|\n", param.text_north);
	printf("SUD    : |%s|\n", param.text_south);
	printf("EAST   : |%s|\n", param.text_east);
	printf("WEST   : |%s|\n", param.text_west);
	printf("SPRITE : |%s|\n", param.text_sprite);
	printf("FLOOR  : |%d|\n", param.floor_color);
	printf("CEILIN : |%d|\n", param.ceiling_color);
	if (param.text_south)
		free(param.text_south);
	if (param.text_west)
		free(param.text_west);
	if (param.text_east)
		free(param.text_east);
	if (param.text_north)
		free(param.text_north);
	if (param.text_sprite)
		free(param.text_sprite);
	return (0);
}
