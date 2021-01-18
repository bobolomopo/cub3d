#include "../include/cub3D.h"

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

static unsigned char	*create_image_header()
{
	unsigned char *image_header;

	if (!(image_header = ft_calloc(41, sizeof(*image_header))))
		parsing_error(NULL, 5);
	image_header[0] = (unsigned char)(40);
	image_header[4] = (unsigned char)(param.res_x);
	image_header[5] = (unsigned char)(param.res_x >> 8);
	image_header[6] = (unsigned char)(param.res_x >> 16);
	image_header[7] = (unsigned char)(param.res_x >> 24);
	image_header[8] = (unsigned char)(param.res_y);
	image_header[9] = (unsigned char)(param.res_y >> 8);
	image_header[10] = (unsigned char)(param.res_y >> 16);
	image_header[11] = (unsigned char)(param.res_y >> 24);
	image_header[12] = (unsigned char)(1);
	image_header[14] = (unsigned char)(game.img.bits_per_pixel);
	return (image_header);
}

static void			calc_bmp_data(t_bmp *bmp)
{
	bmp->bytes_width = param.res_x * game.img.bits_per_pixel;
	bmp->pad_size = (4 - (bmp->bytes_width) % 4) % 4;
	bmp->bmp_size = 14 + 40 + ((bmp->bytes_width + bmp->pad_size) * param.res_y);
	bmp->fileheader = create_file_header(bmp->bmp_size);
	bmp->imageheader = create_image_header();
	write(bmp->fd, bmp->fileheader, 14);
	write(bmp->fd, bmp->imageheader, 40);
	free(bmp->fileheader);
	free(bmp->imageheader);
}

void			create_image()
{
	t_bmp bmp;

	if ((bmp.fd = open("firstpic.bmp", O_CREAT | O_RDWR,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		parsing_error(NULL, 5);
	calc_bmp_data(&bmp);
	bmp.i = (param.res_y);
	while (--bmp.i > 0)
	{
		bmp.j = -1;
		while (++bmp.j < (param.res_x))
		{
			bmp.r = game.img.addr[bmp.i * game.img.line_length + bmp.j * game.img.bits_per_pixel / 8];
			bmp.g = game.img.addr[bmp.i * game.img.line_length + bmp.j * game.img.bits_per_pixel / 8 + 1];
			bmp.b = game.img.addr[bmp.i * game.img.line_length + bmp.j * game.img.bits_per_pixel / 8 + 2];
			write(bmp.fd, &bmp.r, 1);
			write(bmp.fd, &bmp.g, 1);
			write(bmp.fd, &bmp.b, 1);
			write(bmp.fd, "\0", 1);
		}
	}
	close(bmp.fd);
	ft_close();
}