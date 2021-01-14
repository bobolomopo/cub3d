#include "include/cub3D.h"

int main()
{
    int     test;
    t_img   barrel;
    int     img_w;
    int     img_h;
    char    *cacao = "cacao";

    dis.mlx = mlx_init();
	dis.win = mlx_new_window(dis.mlx, 1024, 760, "Cub3D");
    barrel.img = mlx_xpm_file_to_image(dis.mlx, "./textures/wood.xpm", &barrel.width, &barrel.height);
    barrel.addr = mlx_get_data_addr(barrel.img, &barrel.bits_per_pixel,
                                    &barrel.line_length, &barrel.endian);
    mlx_put_image_to_window(dis.mlx, dis.win, barrel.img, 0, 0);
    mlx_loop(dis.mlx);
}