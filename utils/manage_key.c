#include "../include/cub3D.h"

int		manage_key(int keycode)
{
	double moveSpeed = 1.0;
	double rotSpeed = 0.1;
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
	if(keycode == 124)
	{
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
	if(keycode == 123)
	{
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