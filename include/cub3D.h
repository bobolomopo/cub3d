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
# include <mlx.h>

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

typedef	struct		s_param 	{
	int					res_x;
	int					res_y;
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
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	t_display			dis;
	t_img				game;
}					t_param;

/*
**simple structure avec tout ce qui est nécessaire pour définir une
**image
*/



/*
**ecran et moniteur sur lequel s'affiche la fenetre, peut-être réunir
**avec la résolution
*/

/*
**contiendra la position en temps réel du point de vue du personnage
**pourra peut-être aussi directement contenir la position de base
**surement pas nécessaire.
*/

typedef struct		s_game		{
	int					pos_x;
	int					pos_y;
	float	angle;
	t_img				img;
}					t_game;


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

typedef struct		s_raycast	{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				camera_x;
	double				ray_dir_x;
	double				ray_dir_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					sprite_x;
	int					sprite_y;
	t_img				sprite_text;
	int					tex_num;
	double				inv_det;
	double				transform_x;
	double				transform_y;
	int					sprite_screen_x;
	int					sprite_height;
	int					draw_start_y;
	int					draw_end_y;
	int					sprite_width;
	int					draw_start_x;
	int					draw_end_x;
}					t_raycast;

/*
**structure contenant la résolution de l'écran, devras faire une 
**vérification d'erreur pour pouvoir la séparer en parts éégales.
**intéressants de le réunir avec d'autres variables en une structure
**peut-être
*/

/*
**Valeurs définies par défauts pour les tests, plus tard elles
**viendront du fichier .cub
*/

t_param		g_param;
t_img		textures[5];
t_sprite	sprites;
int			fd;
double		plane_x;
double		plane_y;
double		camera_x;
double		ray_dir_x;
double		ray_dir_y;
double		side_dist_x;
double		side_dist_y;
double		delta_dist_x;
double		delta_dist_y;
double		perp_wall_dist;
int			step_x;
int			step_y;
int			hit;
int			side;
int			line_height;
int			draw_start;
int			draw_end;
int			map_x;
int			map_y;
int			tex_num;
double		sprite_x;
double		sprite_y;
double		inv_det;
double		transform_x;
double		transform_y;
int			sprite_screen_x;
int			sprite_height;
int			draw_start_y;
int			draw_end_y;
int			sprite_width;
int			draw_start_x;
int			draw_end_x;


int			ft_strlen(const char *str);
char		*ft_substr(char const *s, int start, int len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strchr(const char *s, int c);
int			pos(char *str, char c);
int			ft_initialize(int fd, char **line, char **rest);
int			ft_copy(char **rest, int fd);
int			get_next_line(int fd, char **line);
char		*ft_strnew(int size);
int			ft_strlen_n(char *str, char stop);
int			ft_nbrlen(int n);
int			ft_isdigit(int c);
int     	ft_isin(char c, const char *str);
int			ft_atoi(const char *str);
char		*fill_char(char *line);
int			parsing(int fd, t_param *param);
int			fill_param(char *line, t_param *param);
int			fill_param_rgb(char *line, t_param *param, char c);
int			fill_param_res(char *line, t_param *param);
int			fill_param_char(char *line, t_param *param);
int			fill_param_map(int fd, t_param *param);
int			parsing_error(char *ptr, int ret);
void		doublefree(char *str, char *str2);
void    	direction(char c, t_param *param);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
int			initialize();
void		ft_close();
void		draw_ver_line(int x, int drawStart, int drawEnd, int color);
void		draw_ceil_floor(int width, int height);
void		raycasting();
int			manage_key(int keycode);
int			get_tex_color(t_img *tex, int x, int y);
void		sprite_value(t_sprite *sprite);
void		sortsprite(int *sprite_order, double *spriteDistance, int numsprite);
void		create_image();
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, unsigned int n);
void		*ft_memset(void *b, int c, unsigned int len);
int			parsing_error(char *ptr, int ret);
int			ft_strcmp(const char *s1, const char *s2);

#endif
