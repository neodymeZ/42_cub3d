/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:09:59 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 03:23:38 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

/*
** "t_map" structure type is for structures that describe Cub3D map
** characteristics, as read from *.cub file. It contains:
**   - pointer to the map (one-dimensional integer array, terminated by -2,
**     where -1 values represent spaces);
**     NB: In map, x-coordinate is vertical, y-coordinate is horizontal.
**     NB: Zero coordinates are in the top left corner of the map.
**   - map height and width;
**   - position and direction vectors of the player, camera plane;
**   - paths to wall textures (for north, south, east and west walls);
**   - path to sprite texture;
**   - floor and ceiling color;
**   - paths to the floor, ceiling and skybox textures;
**   - shading on/off switch (0 - off, 1 - on);
** The structure of t_map type is initialized via "init_map" function.
*/

typedef struct		s_map
{
	int				*map;
	int				map_width;
	int				map_height;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	char			*ntex_path;
	char			*stex_path;
	char			*wtex_path;
	char			*etex_path;
	char			*sprite_path;
	unsigned int	floor_color;
	unsigned int	ceil_color;
	char			*ftex_path;
	char			*ctex_path;
	char			*skytex_path;
	int				shading;
	int				mouse_look;
}					t_map;

/*
** "t_win" structure type is for structures that describe MLX windows.
** It contains:
**   - pointers to connection and window;
**   - rendering resolution (window width and height);
** The structure of t_win type is initialized via "init_win" function.
*/

typedef struct		s_win
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				win_width;
	int				win_height;
	unsigned int	key_event;
	int				mouse_moved;
	int				mouse_x;
	int				mouse_y;
	int				mouse_x_prev;
	int				mouse_y_prev;
}					t_win;

/*
** "t_img" structure type is for structures that describe MLX images.
** It contains:
**   - pointers to connection and image;
**   - image height and width;
** The structure of t_img type is initialized via "init_img" function.
*/

typedef	struct		s_img
{
	void			*mlx_ptr;
	void			*img_ptr;
	int				img_width;
	int				img_height;
	char			*img_addr;
	int				img_bpp;
	int				img_line_size;
	int				img_endian;
}					t_img;

/*
** "t_all" structure type contains pointers to all structures that define
** the properties of the rendered world, including textures.
*/

typedef struct		s_all
{
	t_win			*w;
	t_map			*m;
	t_img			*i;
	t_img			*tn;
	t_img			*ts;
	t_img			*tw;
	t_img			*te;
	t_img			*tf;
	t_img			*tc;
	t_img			*tspr;
	t_img			*tsky;
	t_list			*spr_list;
	t_file			*file;
}					t_all;

#endif
