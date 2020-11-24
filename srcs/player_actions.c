/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 03:01:57 by larosale          #+#    #+#             */
/*   Updated: 2020/08/23 02:21:06 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Performs calculations for rotating player (with left and right arrows).
*/

void	rotate_player(t_all *a, int key)
{
	int		direction;
	double	speed;
	double	old_dir_x;
	double	old_plane_x;

	speed = (key == MOUSE) ? -2 * PI *
		(double)(a->w->mouse_x - a->w->mouse_x_prev) / a->w->win_width : SPEED;
	direction = (key == KEY_LEFT || key == MOUSE) ? 1 : -1;
	if (key == KEY_LEFT || key == KEY_RIGHT || key == MOUSE)
	{
		old_dir_x = a->m->dir_x;
		a->m->dir_x = a->m->dir_x * cos(speed) -
			direction * a->m->dir_y * sin(speed);
		a->m->dir_y = direction * old_dir_x * sin(speed) +
			a->m->dir_y * cos(speed);
		old_plane_x = a->m->plane_x;
		a->m->plane_x = a->m->plane_x * cos(speed) -
			direction * a->m->plane_y * sin(speed);
		a->m->plane_y = direction * old_plane_x * sin(speed) +
			a->m->plane_y * cos(speed);
	}
	return ;
}

/*
** Performs calculations for moving player viewpoint (w, a, s, d keys).
** Checks for wall collisions.
*/

void	move_player(t_all *a, int key)
{
	int		direction;
	double	dx;
	double	dy;

	direction = (key == KEY_W || key == KEY_UP || key == KEY_A ? 1 : -1);
	if (key == KEY_W || key == KEY_UP || key == KEY_S || key == KEY_DOWN)
	{
		dx = direction * SPEED * a->m->dir_x;
		dy = direction * SPEED * a->m->dir_y;
		(a->m->map)[(int)(a->m->pos_x + dx) * a->m->map_width +
			(int)a->m->pos_y] == 0 ? a->m->pos_x += dx : 0;
		(a->m->map)[(int)a->m->pos_x * a->m->map_width +
			(int)(a->m->pos_y + dy)] == 0 ? a->m->pos_y += dy : 0;
	}
	else if (key == KEY_A || key == KEY_D)
	{
		dx = direction * SPEED * -(a->m->dir_y);
		dy = direction * SPEED * a->m->dir_x;
		(a->m->map)[(int)(a->m->pos_x + dx) * a->m->map_width +
			(int)a->m->pos_y] == 0 ? a->m->pos_x += dx : 0;
		(a->m->map)[(int)a->m->pos_x * a->m->map_width +
			(int)(a->m->pos_y + dy)] == 0 ? a->m->pos_y += dy : 0;
	}
	return ;
}
