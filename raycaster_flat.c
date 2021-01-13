#include "include/cub3D.h"


double posX, posY;  //x and y start position
double dirX = -1, dirY = 0; //initial direction vector; //the 2d raycaster version of camera plane

void	draw_ver_line(int x, int drawStart, int drawEnd, int color)
{
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(&game.img, x, drawStart, color);
		drawStart++;
	}
}

int		manage_key(int keycode)
{
//timing for input and FPS counter
	//speed modifiers
	double moveSpeed = 1.0; //the constant value is in squares/second
	double rotSpeed = 0.1; //the constant value is in radians/second
	//move forward if no wall in front of you
	if(keycode == 126)
	{
		mlx_destroy_image(dis.mlx, game.img.img);
        mlx_clear_window(dis.mlx, dis.win);
		game.img.img = mlx_new_image(dis.mlx, param.res_x, param.res_y);
		game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);
		if ((param.map[(int)(posX + dirX * moveSpeed)][(int)(posY)]) == '0')
			posX += dirX * moveSpeed;
		if ((param.map[(int)(posX)][(int)(posY + dirY * moveSpeed)]) == '0')
			posY += dirY * moveSpeed;
		raycasting();
		mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
	}
	//move backwards if no wall behind you
	if(keycode == 125)
	{
		mlx_destroy_image(dis.mlx, game.img.img);
        mlx_clear_window(dis.mlx, dis.win);
		game.img.img = mlx_new_image(dis.mlx, param.res_x, param.res_y);
		game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);
		if ((param.map[(int)(posX - dirX * moveSpeed)][(int)(posY)]) == '0')
			posX -= dirX * moveSpeed;
		if ((param.map[(int)(posX)][(int)(posY - dirY * moveSpeed)]) == '0')
			posY -= dirY * moveSpeed;
		raycasting();
		mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
	}
	//rotate to the right
	if(keycode == 124)
	{
		mlx_destroy_image(dis.mlx, game.img.img);
        mlx_clear_window(dis.mlx, dis.win);
		game.img.img = mlx_new_image(dis.mlx, param.res_x, param.res_y);
		game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		raycasting();
		mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
	}
	//rotate to the left
	if(keycode == 123)
	{
		mlx_destroy_image(dis.mlx, game.img.img);
        mlx_clear_window(dis.mlx, dis.win);
		game.img.img = mlx_new_image(dis.mlx, param.res_x, param.res_y);
		game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		raycasting();
		mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
	}
	if (keycode == 53)
        ft_close();
	return (1);
}

void raycasting()
{
	for(int x = 0; x < param.res_x; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)param.res_x - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)(posX);
		int mapY = (int)(posY);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(sideDistX < sideDistY)
			{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		//Check if ray has hit a wall
		if(param.map[mapX][mapY] != '0') hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(param.res_y / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + param.res_y / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + param.res_y / 2;
		if(drawEnd >= param.res_y)drawEnd = param.res_y - 1;

		//choose wall color
		int color;
		switch(param.map[mapX][mapY])
		{
			case '1':  color = 16711680;    break; //red
			case '2':  color = 65280;  break; //green
			case '3':  color = 255;   break; //blue
			case '4':  color = 16777215;  break; //white
			default: color = 16776960; break; //yellow
		}

		//give x and y sides different brightness
		if(side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		draw_ver_line(x, drawStart, drawEnd, color);
	}
}

void	ft_define_map(t_param *param)
{
	int     i;
	int     j;

	i = 0;
	while (param->map[i])
	{
		j = 0;
		while (param->map[i][j])
			j++;
		if (j > param->map_w)
			param->map_w = j;
		i++;
	}
	param->map_h = i;
}

int		initialize(t_param *param)
{
	fd = open("./test.cub", O_RDONLY);
	param->res_x = 0;
	param->res_y = 0;
	param->text_north = NULL;
	param->text_south = NULL;
	param->text_east = NULL;
	param->text_west = NULL;
	param->floor_color = -1;
	param->ceiling_color = -1;
	param->text_sprite = NULL;
	param->map = NULL;
	param->pos_x = 0;
	param->pos_y = 0;
	param->dir_x = 0;
	param->dir_y = 0;
	if (parsing(fd, param) < 0)
		return (-1);
	ft_define_map(param);
	return (1);
}

int main()
{
	if (initialize(&param) < 0)
        return (-1);
	posX = param.pos_x;
	posY = param.pos_y;
	dirX = param.dir_x;
	dirY = param.dir_y;
	dis.mlx = mlx_init();
	dis.win = mlx_new_window(dis.mlx, param.res_x, param.res_y, "Cub3D");
	game.img.img = mlx_new_image(dis.mlx, param.res_x, param.res_y);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length, &game.img.endian);
	raycasting();
	mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
	mlx_hook(dis.win, 2, 1L<<0, manage_key, &dis);
    mlx_loop(dis.mlx);
	return (0);
}
