/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastertext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 20:27:40 by jandre            #+#    #+#             */
/*   Updated: 2021/01/13 20:27:43 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

static void raycasting_init(int x)
{
	camera_x = 2 * x / (double)param.res_x - 1;
	ray_dir_x = dirX + planeX * camera_x;
	ray_dir_y = dirY + plane_y * camera_x;
	map_x = (int)(posX);
	map_y = (int)(posY);
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	hit = 0;
}

static void raycasting_init2(int x)
{
	if(ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (posX - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - posX) * delta_dist_x;
	}
	if(ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (posY - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - posY) * delta_dist_y;
	}
}

static void	raycasting_dda()
{
	while (hit == 0)
	{	
		if(side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (param.map[map_x][map_y] == '1')
			hit = 1;
	}
}

static int		get_tex_color(t_img *tex, int x, int y)
{
	char				*dst;
	unsigned int		color;

	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	color = (*(unsigned int*)dst);
	return (color);
}

void	sprite_value(t_sprite *sprite)
{
	int x;
	int	y;
	int i;

	x = 0;
	i = 0;
	while (x < param.map_h)
	{
		y = 0;
		while (param.map[x][y])
		{
			if (param.map[x][y] == '2')
			{
				sprite[i].x = y;
				sprite[i].y = x;
				sprite[i].text = textures[4];
				i++;
			}
			y++;
		}
		x++;
	}
}

void sortsprite(int *spriteOrder, double *spriteDistance, int numsprite)
{
	int		i;
	int		j;
	double	temp;
	double	temp2[numsprite];


	i = 0;
	while (i < numsprite)
	{
		printf("%f\n", spriteDistance[i]);
		temp2[i] = spriteDistance[i];
		i++;
	}
	i = 0;
	j = 0;
	while (i < numsprite)
	{
		temp = temp2[i];
		j = 0;
		while (j < numsprite)
		{
			if (temp < temp2[j])
			{
				temp = temp2[j];
				spriteOrder[i] = j;
			}
			j++;
		}
		temp2[spriteOrder[i]] = 0;
		i++;
	}
}

void	raycasting()
{
	int			color;
	int			x;
	int			texNum;
	double		z_buffer[param.res_x];
	int			spriteOrder[param.num_sprite];
	double		spriteDistance[param.num_sprite];
	t_sprite	sprite[param.num_sprite];

	x = 0;
	sprite_value(sprite);
	while (x < param.res_x)
	{
		raycasting_init(x);
		raycasting_init2(x);
		raycasting_dda();
		if (side == 0)
			perp_wall_dist = (map_x - posX + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - posY + (1 - step_y) / 2) / ray_dir_y;
		line_height = (int)(param.res_y / perp_wall_dist);
		draw_start = -line_height / 2 + param.res_y / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + param.res_y / 2;
		if(draw_end >= param.res_y)
			draw_end = param.res_y - 1;
		if (side == 0)
		{
			if (ray_dir_x < 0)
				texNum = 1;
			else
				texNum = 0;
		}
		else
		{
			if (ray_dir_y < 0)
				texNum = 3;
			else
				texNum = 2;
		}
		double wallX;
		if(side == 0)
			wallX = posY + perp_wall_dist * ray_dir_y;
		else
			wallX = posX + perp_wall_dist * ray_dir_x;
		wallX -= floor((wallX));
		int texX = (int)(wallX * (double)(textures[texNum].width));
		if(side == 0 && ray_dir_x > 0)
			texX = textures[texNum].width - texX - 1;
		if(side == 1 && ray_dir_y < 0)
			texX = textures[texNum].width - texX - 1;
		double step = 1.0 * textures[texNum].height / line_height;
		double texPos = (draw_start - param.res_y / 2 + line_height / 2) * step;
		for(int y = draw_start; y < draw_end; y++)
		{
			int texY = (int)texPos & (textures[texNum].height - 1);
			texPos += step;
			color = get_tex_color(&textures[texNum], texX, texY);
			if(side == 1)
				color = (color >> 1) & 8355711;
			my_mlx_pixel_put(&game.img, x, y, color);
		}
		z_buffer[x] = perp_wall_dist;
		x++;
	}
	for(int i = 0; i < param.num_sprite; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((posX - sprite[i].x) * (posX - sprite[i].x) + (posY - sprite[i].y) * (posY - sprite[i].y)); //sqrt not taken, unneeded
	}
	if (param.num_sprite > 0)
		sortsprite(spriteOrder, spriteDistance, param.num_sprite);
	for(int i = 0; i < param.num_sprite; i++)
	{
		printf("sprite order n %d : %d\n", i, spriteOrder[i]);
		//translate sprite position to relative to camera
		double spriteX = sprite[spriteOrder[i]].x - posX;
		double spriteY = sprite[spriteOrder[i]].y - posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (planeX * dirY - dirX * plane_y); //required for correct matrix multiplication

		double transformX = invDet * (dirY * spriteX - dirX * spriteY);
		double transformY = invDet * (-plane_y * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((param.res_x / 2) * (1 + transformX / transformY));

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(param.res_y / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + param.res_y / 2 + vMoveScreen;
		if(drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + param.res_y / 2 + vMoveScreen;
		if(drawEndY >= param.res_y)
			drawEndY = param.res_y - 1;
		int spriteWidth = abs((int)(param.res_y / (transformY))) / uDiv;
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= param.res_x)
			drawEndX = param.res_x - 1;
		printf("start : %d\nend : %d\n", drawStartX, drawEndX);
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
						printf("ok\n");
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * textures[4].width / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < param.res_x && transformY < z_buffer[stripe])
			{
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y-vMoveScreen) * 256 - param.res_y * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * textures[4].height) / spriteHeight) / 256;
					color = get_tex_color(&textures[4], texX, texY);
					printf("ok\n");
					if(color != 0)
						my_mlx_pixel_put(&game.img, x, y, color);
				 //paint pixel if it isn't black, black is the invisible color
				}
			}
		}
	}
}