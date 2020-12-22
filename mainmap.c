#include "include/cub3D.h"

int     main()
{
    int fd = open("./test.cub", O_RDONLY);
    fill_param_map(fd);
    close(fd);
    return (0);
}