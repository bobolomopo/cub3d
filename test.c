#include "include/cub3d.h"

int main()
{
    char buffer[10];
    int fd = open("test.txt", O_RDONLY);
    get_to_map(fd);
    return (1);
}