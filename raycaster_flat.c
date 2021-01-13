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

void	draw_ceil_floor(int width, int height)
{
	int		x;
	int		y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			if (y < height / 2)
				my_mlx_pixel_put(&game.img, x, y, param.floor_color);
			else
				my_mlx_pixel_put(&game.img, x, y, param.ceiling_color);
			y++;
		}
		x++;
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
		if ((param.map[(int)(posX + dirX * moveSpeed)][(int)(posY)]) == '0')
			posX += dirX * moveSpeed;
		if ((param.map[(int)(posX)][(int)(posY + dirY * moveSpeed)]) == '0')
			posY += dirY * moveSpeed;
		draw_ceil_floor(param.res_x, param.res_y);
		raycasting();
		mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
	}
	//move backwards if no wall behind you
	if(keycode == 125)
	{
		if ((param.map[(int)(posX - dirX * moveSpeed)][(int)(posY)]) == '0')
			posX -= dirX * moveSpeed;
		if ((param.map[(int)(posX)][(int)(posY - dirY * moveSpeed)]) == '0')
			posY -= dirY * moveSpeed;
		draw_ceil_floor(param.res_x, param.res_y);
		raycasting();
		mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
	}
	//rotate to the right
	if(keycode == 124)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - plane_y * sin(-rotSpeed);
		plane_y = oldPlaneX * sin(-rotSpeed) + plane_y * cos(-rotSpeed);
		draw_ceil_floor(param.res_x, param.res_y);
		raycasting();
		mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
	}
	//rotate to the left
	if(keycode == 123)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - plane_y * sin(rotSpeed);
		plane_y = oldPlaneX * sin(rotSpeed) + plane_y * cos(rotSpeed);
		draw_ceil_floor(param.res_x, param.res_y);
		raycasting();
		mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
	}
	if (keycode == 53)
        ft_close();
	return (1);
}

void raycasting()
{
	int		color;
	int		x;

	x = 0;
	while (x++ < param.res_x)
	{
		camera_x = 2 * x / (double)param.res_x - 1;
		ray_dir_x = dirX + planeX * camera_x;
		ray_dir_y = dirY + plane_y * camera_x;
		map_x = (int)(posX);
		map_y = (int)(posY);
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		hit = 0;
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
		if(param.map[map_x][map_y] != '0') hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map_x - posX + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - posY + (1 - step_y) / 2) / ray_dir_y;
		line_height = (int)(param.res_y / perp_wall_dist);
		draw_start = -line_height / 2 + param.res_y / 2;
		if(draw_start < 0)draw_start = 0;
			draw_end = line_height / 2 + param.res_y / 2;
		if(draw_end >= param.res_y)
			draw_end = param.res_y - 1;
		switch(param.map[map_x][map_y])
		{
			case '1':  color = 16711680;    break; //red
			case '2':  color = 65280;  break; //green
			case '3':  color = 255;   break; //blue
			case '4':  color = 16777215;  break; //white
			default: color = 16776960; break; //yellow
		}
		if(side == 1) {color = color / 2;}
		draw_ver_line(x, draw_start, draw_end, color);
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
	draw_ceil_floor(param.res_x, param.res_y);
	raycasting();
	mlx_put_image_to_window(dis.mlx, dis.win, game.img.img, 0, 0);
	mlx_hook(dis.win, 2, 1L<<0, manage_key, &dis);
    mlx_loop(dis.mlx);
	return (0);
}
