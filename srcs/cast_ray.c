/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 23:55:26 by larosale          #+#    #+#             */
/*   Updated: 2020/08/19 01:44:39 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Calculates values, necessary for the raycasting function and
** fills them to the "r" structure.
*/

static void	define_ray(int x, t_ray *r, t_map *m, t_win *w)
{
	r->cam_x = 2 * x / (double)w->win_width - 1;
	r->ray_dir_x = m->dir_x + m->plane_x * r->cam_x;
	r->ray_dir_y = m->dir_y + m->plane_y * r->cam_x;
	r->map_x = m->pos_x;
	r->map_y = m->pos_y;
	r->delta_dist_x = ft_absd(1 / r->ray_dir_x);
	r->delta_dist_y = ft_absd(1 / r->ray_dir_y);
	if (r->ray_dir_x < 0)
		r->step_x = -1;
	else
		r->step_x = 1;
	if (r->ray_dir_y < 0)
		r->step_y = -1;
	else
		r->step_y = 1;
	if (r->ray_dir_x < 0)
		r->side_dist_x = (m->pos_x - r->map_x) * r->delta_dist_x;
	else
		r->side_dist_x = (r->map_x + 1.0 - m->pos_x) * r->delta_dist_x;
	if (r->ray_dir_y < 0)
		r->side_dist_y = (m->pos_y - r->map_y) * r->delta_dist_y;
	else
		r->side_dist_y = (r->map_y + 1.0 - m->pos_y) * r->delta_dist_y;
	return ;
}

/*
** Calculates the distance between a wall and the camera plane
** (perpendicular distance, not Euclidean, to avoid "fisheye" effect.
** "side" variable contains the wall side, which was hit by the ray
** (0 for north, 1 for south, 2 for west and 3 for east).
*/

static void	calc_dist(t_ray *r, t_map *m)
{
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = (r->ray_dir_x < 0 ? 1 : 0);
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = (r->ray_dir_y < 0 ? 3 : 2);
		}
		if ((m->map)[m->map_width * r->map_x + r->map_y] == 1)
			r->hit = 1;
	}
	if (r->side == 0 || r->side == 1)
		r->perp_wall_dist =
			(r->map_x - m->pos_x + (1 - r->step_x) / 2) / r->ray_dir_x;
	else
		r->perp_wall_dist =
			(r->map_y - m->pos_y + (1 - r->step_y) / 2) / r->ray_dir_y;
	return ;
}

/*
** Casts a ray to the "x" horizontal screen coordinate.
** As a result, fills the "r" structure with calculated values,
** including the distance between a wall and the camera plane.
*/

void		cast_ray(int x, t_ray *r, t_all *a)
{
	clear_ray(r);
	define_ray(x, r, a->m, a->w);
	calc_dist(r, a->m);
	return ;
}
