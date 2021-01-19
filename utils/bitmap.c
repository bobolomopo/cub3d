/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:59:39 by jandre            #+#    #+#             */
/*   Updated: 2021/01/19 16:59:41 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static unsigned char	*create_file_header(int bmp_size)
{
	unsigned char *file_header;

	if (!(file_header = ft_calloc(15, sizeof(*file_header))))
		parsing_error(NULL, 5);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(bmp_size);
	file_header[3] = (unsigned char)(bmp_size >> 8);
	file_header[4] = (unsigned char)(bmp_size >> 16);
	file_header[5] = (unsigned char)(bmp_size >> 24);
	file_header[10] = (unsigned char)(14 + 40);
	return (file_header);
}

static unsigned char	*create_image_header(void)
{
	unsigned char *image_header;

	if (!(image_header = ft_calloc(41, sizeof(*image_header))))
		parsing_error(NULL, 5);
	image_header[0] = (unsigned char)(40);
	image_header[4] = (unsigned char)(g_param.res_x);
	image_header[5] = (unsigned char)(g_param.res_x >> 8);
	image_header[6] = (unsigned char)(g_param.res_x >> 16);
	image_header[7] = (unsigned char)(g_param.res_x >> 24);
	image_header[8] = (unsigned char)(g_param.res_y);
	image_header[9] = (unsigned char)(g_param.res_y >> 8);
	image_header[10] = (unsigned char)(g_param.res_y >> 16);
	image_header[11] = (unsigned char)(g_param.res_y >> 24);
	image_header[12] = (unsigned char)(1);
	image_header[14] = (unsigned char)(g_param.game.bits_per_pixel);
	return (image_header);
}

static void				calc_bmp_data(t_bmp *bmp)
{
	bmp->bytes_width = g_param.res_x * g_param.game.bits_per_pixel;
	bmp->pad_size = (4 - (bmp->bytes_width) % 4) % 4;
	bmp->bmp_size = 14 + 40 + ((bmp->bytes_width +
		bmp->pad_size) * g_param.res_y);
	bmp->fileheader = create_file_header(bmp->bmp_size);
	bmp->imageheader = create_image_header();
	write(bmp->fd, bmp->fileheader, 14);
	write(bmp->fd, bmp->imageheader, 40);
	free(bmp->fileheader);
	free(bmp->imageheader);
	bmp->i = g_param.res_y;
}

void					create_image(void)
{
	t_bmp bmp;

	if ((bmp.fd = open("firstpic.bmp", O_CREAT | O_RDWR,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		parsing_error(NULL, 5);
	calc_bmp_data(&bmp);
	while (--bmp.i > 0)
	{
		bmp.j = -1;
		while (++bmp.j < (g_param.res_x))
		{
			bmp.r = g_param.game.addr[bmp.i * g_param.game.line_length +
				bmp.j * g_param.game.bits_per_pixel / 8];
			bmp.g = g_param.game.addr[bmp.i * g_param.game.line_length +
				bmp.j * g_param.game.bits_per_pixel / 8 + 1];
			bmp.b = g_param.game.addr[bmp.i * g_param.game.line_length +
				bmp.j * g_param.game.bits_per_pixel / 8 + 2];
			write(bmp.fd, &bmp.r, 1);
			write(bmp.fd, &bmp.g, 1);
			write(bmp.fd, &bmp.b, 1);
			write(bmp.fd, "\0", 1);
		}
	}
	close(bmp.fd);
	ft_close();
}
