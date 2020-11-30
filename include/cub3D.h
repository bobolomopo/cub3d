/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 15:42:52 by jandre            #+#    #+#             */
/*   Updated: 2020/11/30 16:00:02 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>

/*Simple structure avec tout ce qui est nécessaire pour définir une
image*/

typedef struct	s_img		{
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}		t_img;

/*ecran et moniteur sur lequel s'affiche la fenetre, peut-être réunir
avec la résolution*/

typedef struct	s_display	{
	void	*mlx;
	void	*win;
}		t_display;

/*contiendra la position en temps réel du point de vue du personnage
pourra peut-être aussi directement contenir la position de base
surement pas nécessaire.*/

typedef struct	s_perso		{
	int	x;
	int	y;
	t_img	perso;
}		t_perso;

/*structure contenant la résolution de l'écran, devras faire une 
vérification d'erreur pour pouvoir la séparer en parts éégales.
intéressants de le réunir avec d'autres variables en une structure
peut-être*/

typedef struct	s_reso		{
	int	x;
	int	y;
}		t_reso;

/* structure de la map, doit contenir la taille x et y, et la liste
d'entier qu'on ira chercher dans le fichier .cub, par la suite, 
devra aussi contenir les textures */

typedef struct	s_map		{
	int	xsize;
	int	ysize;
	t_img	map;
	int	map[map.xsize * map.ysize];
}		t_map;

/*Valeurs définies par défauts pour les tests, plus tard elles
viendront du fichier .cub*/

reso.x = 1000;
reso.y = 1000;

map.xsize = 10;
map.ysize = 10;
map.map = 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1}


#endif
