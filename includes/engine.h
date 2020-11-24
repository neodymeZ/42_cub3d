/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 01:45:09 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 14:14:52 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "mlx.h"
# include "libft.h"
# include "events.h"
# include "files.h"
# include "window.h"
# include "rendering.h"
# include "errors.h"

/*
** SPEED defines moving and rotating speed of the player (the larger the value,
** the larger is moving speed).
** FOV defines field of view in degrees. "Natural" eye-like FOV is 70 degrees.
** MAP_GEO and MAP_POS define strings with all permitted symbols on the map.
*/

# define WINDOW_NAME "Cub3D"
# define BMP_SAVE_PATH "./frame.bmp"
# define SPEED 0.05
# define FOV 70.0
# define MAP_GEO " 012"
# define MAP_POS "NSWE"
# define PI 3.14159265358979323846

/*
** Key function launched from main function.
*/

int					start_cub3d(char *filename, char *save_flag);

/*
** These functions are used to construct and reset structures.
*/

t_map				*define_map(t_file *f, t_all *a);
t_win				*define_win(t_file *f, t_all *a);
t_img				*define_img(t_file *f, t_all *a, char *filepath);
t_all				*define_all(t_file *f);
t_frame				*define_frame(t_file *f, t_all *a);
void				clear_ray(t_ray *ray);
void				clear_wtex(t_wtex *wtex);
void				clear_ftex(t_ftex *ftex);
void				clear_skytex(t_skytex *skytex);

/*
** Ray casting and frame rendering functions.
*/

void				cast_ray(int x, t_ray *r, t_all *a);
void				pixel_put(t_img *i, int x, int y, unsigned int color);
void				color_shading(unsigned int *color, double distance);
void				render_walls(int x, t_ray *r, t_wtex *wt, t_all *a);
void				render_floor_and_ceil(int y, t_ftex *ft, t_all *a);
void				render_skybox(int x, t_ray *r, t_skytex *skyt, t_all *a);
void				render_sprites(t_all *a, t_frame *f);
int					render_frame(t_all *a);
void				show_frame(t_all *a);

/*
** Event handling functions.
*/

int					handle_events(t_all *a);
int					handle_keypress(int keycode, t_all *a);
int					handle_keyrelease(int keycode, t_all *a);
int					handle_exit(t_all *a);
int					handle_mouse_move(int x, int y, t_all *a);
void				move_player(t_all *a, int key);
void				rotate_player(t_all *a, int key);

/*
** Cub file parsing functions.
*/

int					parse_resolution(t_file *f, t_win *w);
int					parse_color(t_file *f, t_map *m);
int					parse_tex(t_file *f, t_map *m);
int					parse_map(t_file *f, t_all *a, t_map *m);
t_list				*parse_sprites(t_all *a, t_file *f);

/*
** Working with files.
*/

int					save_bmp(t_file *f, t_all *a);
t_file				*read_cub_file(char *fpath);

/*
** Handling errors.
*/

int					handle_errors(int errnum);

/*
** Cleanup functions.
*/

void				*cleanup(int errnum, t_all *a, t_file *f);
int					destroy_file(t_file *file);
int					destroy_win(t_win *win);
int					destroy_map(t_map *map);
int					destroy_img(t_img *img);
int					destroy_spr(t_sprite *spr, t_list *sprites);
int					destroy_all(t_all *all);
int					destroy_frame(t_frame *fr);
int					destroy_bmp(t_bmp *bmp);

#endif
