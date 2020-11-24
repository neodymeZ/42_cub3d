/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 20:15:31 by larosale          #+#    #+#             */
/*   Updated: 2020/08/21 01:16:01 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Calculates the precise x-position of the wall when the ray hit it (wall_x),
** and the corresponding x-coordinate (in pixels) on the texture (tex_x),
** depending on the side of the wall, which was hit.
** Makes other necessary calculations and fills values to the "wt" structure.
*/

static void	calc_render_walls(t_ray *r, t_wtex *wt, t_all *a)
{
	wt->line_height = (int)(a->w->win_height / r->perp_wall_dist);
	if ((wt->draw_start = -(wt->line_height) / 2 + a->w->win_height / 2) < 0)
		wt->draw_start = 0;
	if ((wt->draw_end = wt->line_height / 2 + a->w->win_height / 2) >=
		a->w->win_height)
		wt->draw_end = a->w->win_height - 1;
	if (r->side == 0 || r->side == 1)
		wt->wall_x = a->m->pos_y + r->perp_wall_dist * r->ray_dir_y;
	else
		wt->wall_x = a->m->pos_x + r->perp_wall_dist * r->ray_dir_x;
	wt->wall_x -= floor(wt->wall_x);
	r->side == 0 ? wt->tex_ptr = a->tn : 0;
	r->side == 1 ? wt->tex_ptr = a->ts : 0;
	r->side == 2 ? wt->tex_ptr = a->tw : 0;
	r->side == 3 ? wt->tex_ptr = a->te : 0;
	wt->tex_x = (int)(wt->wall_x * wt->tex_ptr->img_width);
	if (((r->side == 0 || r->side == 1) && r->ray_dir_x > 0) ||
		((r->side == 2 || r->side == 3) && r->ray_dir_y < 0))
		wt->tex_x = wt->tex_ptr->img_width - wt->tex_x - 1;
	wt->step = (double)(wt->tex_ptr->img_height) / wt->line_height;
	wt->tex_pos = (wt->draw_start + wt->line_height / 2 -
		a->w->win_height / 2) * wt->step;
	return ;
}

/*
** Renders a vertical wall stripe which corresponds to the "x" screen
** position.
** Wall stripe is rendered textured, as defined by "wt" texture.
** If no floor and ceiling (or skybox) textures are defined, paints
** floor and ceiling with the map-defined colors.
*/

void		render_walls(int x, t_ray *r, t_wtex *wt, t_all *a)
{
	int				y;
	unsigned int	color;

	clear_wtex(wt);
	calc_render_walls(r, wt, a);
	y = 0;
	while (y < a->w->win_height)
	{
		if (y >= wt->draw_start && y < wt->draw_end)
		{
			wt->tex_y = (int)(wt->tex_pos) & (wt->tex_ptr->img_height - 1);
			wt->tex_pos += wt->step;
			color = *(unsigned int *)(wt->tex_ptr->img_addr + wt->tex_y *
				wt->tex_ptr->img_line_size + wt->tex_x *
				wt->tex_ptr->img_bpp / 8);
			a->m->shading ? color_shading(&color, r->perp_wall_dist) : 0;
			pixel_put(a->i, x, y, color);
		}
		else if (y < wt->draw_start && !(a->tc) && !(a->tsky))
			pixel_put(a->i, x, y, a->m->ceil_color);
		else if (y >= wt->draw_end && !(a->tf))
			pixel_put(a->i, x, y, a->m->floor_color);
		y++;
	}
	return ;
}
