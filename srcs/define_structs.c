/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 13:32:57 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 01:28:12 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Creates a structure of "t_map" type and sets its contents.
** Returns pointer to the created structure of NULL on error.
*/

t_map	*define_map(t_file *f, t_all *a)
{
	t_map	*map;

	if (!(map = ft_calloc(1, sizeof(t_map))))
		return (cleanup(ERR_SYS, a, f));
	if (parse_color(f, map) && !destroy_map(map))
		return (cleanup(ERR_PARCLR, a, f));
	if (parse_tex(f, map) && !destroy_map(map))
		return (cleanup(ERR_PARTEX, a, f));
	if (parse_map(f, a, map))
		return (NULL);
	return (map);
}

/*
** Creates a structure of "t_win" type and sets its contents.
** If display resolution is lower, than the requested window size,
** the latter is set to the display resolution.
** Returns pointer to the created structure or NULL on error.
*/

t_win	*define_win(t_file *f, t_all *a)
{
	t_win	*win;
	int		display_width;
	int		display_height;

	if (!(win = ft_calloc(1, sizeof(t_win))))
		return (cleanup(ERR_SYS, a, f));
	display_width = 0;
	display_height = 0;
	if (!(win->mlx_ptr = mlx_init()) && !destroy_win(win))
		return (cleanup(ERR_MLX, a, f));
	mlx_get_screen_size(win->mlx_ptr, &display_width, &display_height);
	if (parse_resolution(f, win) && !destroy_win(win))
		return (cleanup(ERR_PARRES, a, f));
	win->win_width > display_width ? win->win_width = display_width : 0;
	win->win_height > display_height ? win->win_height = display_height : 0;
	if (!(win->win_ptr = mlx_new_window(win->mlx_ptr, win->win_width,
		win->win_height, WINDOW_NAME)) && !destroy_win(win))
		return (cleanup(ERR_MLX, a, f));
	return (win);
}

/*
** Creates a structure of "t_img" type and sets its contents.
** Returns pointer to the created structure or NULL on error.
*/

t_img	*define_img(t_file *f, t_all *a, char *filepath)
{
	t_img	*img;

	if (!(img = calloc(1, sizeof(t_img))))
		return (cleanup(ERR_SYS, a, f));
	img->mlx_ptr = a->w->mlx_ptr;
	if (!filepath)
	{
		img->img_width = a->w->win_width;
		img->img_height = a->w->win_height;
		if (!(img->img_ptr = mlx_new_image(img->mlx_ptr, img->img_width,
			img->img_height)) && !destroy_img(img))
			return (cleanup(ERR_MLX, a, f));
	}
	else
	{
		if (!(img->img_ptr = mlx_xpm_file_to_image(img->mlx_ptr, filepath,
			&(img->img_width), &(img->img_height))) && !destroy_img(img))
			return (cleanup(ERR_MLX, a, f));
	}
	if (!(img->img_addr = mlx_get_data_addr(img->img_ptr, &(img->img_bpp),
		&(img->img_line_size), &(img->img_endian))) && !destroy_img(img))
		return (cleanup(ERR_MLX, a, f));
	return (img);
}

/*
** Defines the contents of "frame" structure with all the structures
** used for frame rendering (textures, ray casting, etc).
*/

t_frame	*define_frame(t_file *f, t_all *a)
{
	t_frame	*frame;

	if (!(frame = ft_calloc(1, sizeof(t_frame))))
		return (cleanup(ERR_SYS, a, f));
	frame->r = ft_calloc(1, sizeof(t_ray));
	frame->wt = ft_calloc(1, sizeof(t_wtex));
	frame->ft = ft_calloc(1, sizeof(t_ftex));
	frame->skyt = ft_calloc(1, sizeof(t_skytex));
	frame->z_buf = ft_calloc(a->w->win_width, sizeof(double));
	if ((!frame->r || !frame->wt || !frame->ft || !frame->skyt ||
		!frame->z_buf) && !destroy_frame(frame))
		return (cleanup(ERR_SYS, a, f));
	return (frame);
}

/*
** Defines the contents of an "all" structure with all structures
** for the screen rendering.
*/

t_all	*define_all(t_file *f)
{
	t_all	*all;

	if (!(all = ft_calloc(1, sizeof(t_all))))
		return (cleanup(ERR_SYS, all, f));
	all->w = define_win(f, all);
	all->m = define_map(f, all);
	if (!(all->w) || !(all->m))
		return (NULL);
	all->i = define_img(f, all, NULL);
	all->tn = define_img(f, all, all->m->ntex_path);
	all->ts = define_img(f, all, all->m->stex_path);
	all->tw = define_img(f, all, all->m->wtex_path);
	all->te = define_img(f, all, all->m->etex_path);
	all->tspr = define_img(f, all, all->m->sprite_path);
	if (all->m->ftex_path)
		all->tf = define_img(f, all, all->m->ftex_path);
	if (all->m->ctex_path)
		all->tc = define_img(f, all, all->m->ctex_path);
	if (all->m->skytex_path)
		all->tsky = define_img(f, all, all->m->skytex_path);
	all->spr_list = parse_sprites(all, f);
	if (!(all->i) || !(all->tn) || !(all->ts) || !(all->tw) || !(all->te) ||
		!(all->tspr) || !(all->spr_list))
		return (NULL);
	return (all);
}
