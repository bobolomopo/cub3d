/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 15:42:52 by jandre            #+#    #+#             */
/*   Updated: 2020/12/02 09:26:13 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# ifndef GRIDSIZE
#  define GRIDSIZE 60
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif
# ifndef ROTSPEED
#  define ROTSPEED 0.1
# endif
# ifndef MOVESPEED
#  define MOVESPEED 0.8
# endif
# ifndef PI
#  define PI 3.141592653589
# endif
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include "../mlx/mlx.h"

typedef struct		s_display	{
	void				*mlx;
	void				*win;
}					t_display;

typedef struct		s_img		{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}					t_img;

typedef	struct		s_param		{
	int					res_x;
	int					res_y;
	int					max_res_x;
	int					max_res_y;
	char				*text_north;
	char				*text_south;
	char				*text_west;
	char				*text_east;
	char				*text_sprite;
	int					floor_color;
	int					ceiling_color;
	char				**map;
	int					num_sprite;
	int					map_w;
	int					map_h;
	int					step_x;
	int					step_y;
	int					map_x;
	int					map_y;
	int					hit;
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					tex_num;
	int					sprite_screen_x;
	int					sprite_height;
	int					draw_start_y;
	int					draw_end_y;
	int					sprite_width;
	int					draw_start_x;
	int					draw_end_x;
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				ray_dir_x;
	double				ray_dir_y;
	double				side_dist_x;
	double				side_dist_y;
	double				camera_x;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	double				sprite_x;
	double				sprite_y;
	double				inv_det;
	double				transform_x;
	double				transform_y;
	double				wall_x;
	double				step;
	double				tex_pos;
	int					fd;
	t_display			dis;
	t_img				game;
	t_img				textures[5];
}					t_param;

typedef struct		s_sprite	{
	double				x;
	double				y;
	t_img				text;
}					t_sprite;

typedef struct		s_bmp
{
	int					bmp_size;
	int					bytes_width;
	int					pad_size;
	int					fd;
	unsigned char		*fileheader;
	unsigned char		*imageheader;
	int					i;
	int					j;
	int					r;
	int					g;
	int					b;
}					t_bmp;

t_param				g_param;

int					ft_strlen(const char *str);
char				*ft_substr(char const *s, int start, int len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strchr(const char *s, int c);
int					pos(char *str, char c);
int					ft_initialize(int fd, char **line, char **rest);
int					ft_copy(char **rest, int fd);
int					get_next_line(int fd, char **line);
char				*ft_strnew(int size);
int					ft_strlen_n(char *str, char stop);
int					ft_nbrlen(int n);
int					ft_isdigit(int c);
int					ft_isin(char c, const char *str);
int					ft_atoi(const char *str);
char				*fill_char(char *line);
int					parsing(int fd, t_param *param);
int					fill_param(char *line, t_param *param);
int					fill_param_rgb(char *line, t_param *param, char c);
int					fill_param_res(char *line, t_param *param);
int					fill_param_char(char *line, t_param *param);
int					fill_param_map(int fd, t_param *param);
int					parsing_error(char *ptr, int ret);
void				doublefree(char *str, char *str2);
void				direction(char c, t_param *param);
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
int					initialize();
void				ft_close();
void				draw_ceil_floor(int width, int height);
void				raycasting();
int					manage_key(int keycode);
int					get_tex_color(t_img *tex, int x, int y);
void				sprite_value(t_sprite *sprite);
void				sortsprite(int *sprite_order, double *sprite_distance,
								int numsprite);
void				create_image(void);
void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *s, unsigned int n);
void				*ft_memset(void *b, int c, unsigned int len);
int					parsing_error(char *ptr, int ret);
int					ft_strcmp(const char *s1, const char *s2);
void				raycasting_drawing(int x);
void				raycasting_texturing();
void				raycasting_sprite_init(t_sprite *sprite,
									int *sprite_order, int i);
void				raycasting_sprite_draw(double *z_buffer);

#endif
