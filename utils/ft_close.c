#include "../include/cub3D.h"

void       ft_close()
{
        mlx_destroy_window(dis.mlx, dis.win);
        free(dis.mlx);
        if (fd)
            close(fd);
        exit(0);
}