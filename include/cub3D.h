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

/*
**structure comportant tout les parametre de mon cub3d
*/

typedef	struct		s_param 	{
	int		res_x;
	int		res_y;
	char	*text_north;
	char	*text_south;
	char	*text_west;
	char	*text_east;
	char	*text_sprite;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	int		numsprite;
	int		map_w;
	int		map_h;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
}					t_param;

/*
**structure pour le plan devant le perso
*/

typedef struct		s_cam 		{
	double	x;
	double	y;
}					t_cam;

/*
**simple structure avec tout ce qui est nécessaire pour définir une
**image
*/

typedef struct		s_img		{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}					t_img;

/*
**ecran et moniteur sur lequel s'affiche la fenetre, peut-être réunir
**avec la résolution
*/

typedef struct		s_display	{
	void	*mlx;
	void	*win;
}					t_display;

/*
**contiendra la position en temps réel du point de vue du personnage
**pourra peut-être aussi directement contenir la position de base
**surement pas nécessaire.
*/

typedef struct		s_game		{
	int		pos_x;
	int		pos_y;
	float	angle;
	t_img	img;
}					t_game;


typedef struct		s_sprite	{
	double	x;
	double	y;
	int		texture;
}					t_sprite;

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

t_display	dis;
t_game		game;
t_param		param;
t_img		textures[5];
t_sprite	sprites;
int			fd;
double		posX;
double		posY;
double		dirX;
double		dirY;
double		planeX;
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


#endif
