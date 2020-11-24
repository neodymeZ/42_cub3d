/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_and_ceil.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 01:20:32 by larosale          #+#    #+#             */
/*   Updated: 2020/08/21 01:47:59 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Calculates necessary values for texturing floor and ceiling, fills
** them to the "ft" structure.
*/

static void	calc_render_floor_and_ceil(int y, t_ftex *ft, t_all *a)
{
	ft->ray_dir_x0 = a->m->dir_x - a->m->plane_x;
	ft->ray_dir_y0 = a->m->dir_y - a->m->plane_y;
	ft->ray_dir_x1 = a->m->dir_x + a->m->plane_x;
	ft->ray_dir_y1 = a->m->dir_y + a->m->plane_y;
	ft->p = y - a->w->win_height / 2;
	ft->pos_z = 0.5 * a->w->win_height;
	ft->row_distance = ft->pos_z / ft->p;
	ft->floor_step_x = ft->row_distance * (ft->ray_dir_x1 - ft->ray_dir_x0) /
		a->w->win_width;
	ft->floor_step_y = ft->row_distance * (ft->ray_dir_y1 - ft->ray_dir_y0) /
		a->w->win_width;
	ft->floor_x = a->m->pos_x + ft->row_distance * ft->ray_dir_x0;
	ft->floor_y = a->m->pos_y + ft->row_distance * ft->ray_dir_y0;
	return ;
}

/*
** If textures for floor and/or ceiling are defined, draws horizontal
** texturized floor (ceiling) line, corresponding to the vertical
** screen coordinate y.
*/

static void	draw_line(int x, int y, t_ftex *ft, t_all *a)
{
	unsigned int	color;

	color = 0;
	if (a->tf)
	{
		ft->ftex_x = (int)(a->tf->img_width * (ft->floor_x - ft->cell_x)) &
			(a->tf->img_width - 1);
		ft->ftex_y = (int)(a->tf->img_height * (ft->floor_y - ft->cell_y)) &
			(a->tf->img_height - 1);
		color = *(unsigned int *)(a->tf->img_addr + ft->ftex_y *
			a->tf->img_line_size + ft->ftex_x * a->tf->img_bpp / 8);
		a->m->shading ? color_shading(&color, ft->row_distance) : 0;
		pixel_put(a->i, x, y, color);
	}
	if (a->tc)
	{
		ft->ctex_x = (int)(a->tc->img_width * (ft->floor_x - ft->cell_x)) &
			(a->tc->img_width - 1);
		ft->ctex_y = (int)(a->tc->img_height * (ft->floor_y - ft->cell_y)) &
			(a->tc->img_height - 1);
		color = *(unsigned int *)(a->tc->img_addr + ft->ctex_y *
			a->tc->img_line_size + ft->ctex_x * a->tc->img_bpp / 8);
		a->m->shading ? color_shading(&color, ft->row_distance) : 0;
		pixel_put(a->i, x, a->w->win_height - y - 1, color);
	}
}

/*
** Renders the horizontal texturized line of floor and ceiling, if the
** respective textures are defined for every vertical screen pixel "y".
*/

void		render_floor_and_ceil(int y, t_ftex *ft, t_all *a)
{
	int				x;

	x = 0;
	if (!(a->tf) && !(a->tc))
		return ;
	clear_ftex(ft);
	calc_render_floor_and_ceil(y, ft, a);
	while (x < a->w->win_width)
	{
		ft->cell_x = (int)(ft->floor_x);
		ft->cell_y = (int)(ft->floor_y);
		draw_line(x, y, ft, a);
		ft->floor_x += ft->floor_step_x;
		ft->floor_y += ft->floor_step_y;
		x++;
	}
	return ;
}
