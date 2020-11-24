/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 00:42:38 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 12:55:17 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Handles exit when an Esc key is pressed, or the window is closed.
*/

int			handle_exit(t_all *a)
{
	cleanup(ERR_OK, a, a->file);
	return (0);
}

/*
** Handles mouse movement events. Rotates player direction vector if
** movement occurs and calls "handle_events" function for processing
** keyboard events (needed for smooth movement).
*/

int			handle_mouse_move(int x, int y, t_all *a)
{
	if (a->m->mouse_look)
	{
		a->w->mouse_x_prev = a->w->mouse_x;
		a->w->mouse_y_prev = a->w->mouse_y;
		a->w->mouse_x = x;
		a->w->mouse_y = y;
		a->w->mouse_x < 5 && (a->w->mouse_x - a->w->mouse_x_prev < 0) ?
			mlx_mouse_move(a->w->win_ptr, a->w->win_width - 1, y) : 0;
		a->w->mouse_x > a->w->win_width - 5 && (a->w->mouse_x -
			a->w->mouse_x_prev > 0) ? mlx_mouse_move(a->w->win_ptr, 0, y) : 0;
		a->w->mouse_y < 5 && (a->w->mouse_y - a->w->mouse_y_prev < 0) ?
			mlx_mouse_move(a->w->win_ptr, x, a->w->win_height - 1) : 0;
		a->w->mouse_y > a->w->win_height - 5 && (a->w->mouse_y -
			a->w->mouse_y_prev > 0) ? mlx_mouse_move(a->w->win_ptr, x, 0) : 0;
		rotate_player(a, MOUSE);
		handle_events(a);
	}
	return (0);
}

/*
** Sets status flag of the key to "pressed".
*/

int			handle_keypress(int keycode, t_all *a)
{
	keycode == KEY_A ? a->w->key_event |= EV_KEY_A : 0;
	keycode == KEY_S ? a->w->key_event |= EV_KEY_S : 0;
	keycode == KEY_D ? a->w->key_event |= EV_KEY_D : 0;
	keycode == KEY_W ? a->w->key_event |= EV_KEY_W : 0;
	keycode == KEY_LEFT ? a->w->key_event |= EV_KEY_LEFT : 0;
	keycode == KEY_RIGHT ? a->w->key_event |= EV_KEY_RIGHT : 0;
	keycode == KEY_UP ? a->w->key_event |= EV_KEY_UP : 0;
	keycode == KEY_DOWN ? a->w->key_event |= EV_KEY_DOWN : 0;
	if (keycode == KEY_ESC)
		handle_exit(a);
	if (keycode == KEY_L)
		a->m->shading = a->m->shading ? 0 : 1;
	if (keycode == KEY_M)
		a->m->mouse_look = a->m->mouse_look ? 0 : 1;
	return (0);
}

/*
** Sets status flag of the key to "not pressed".
*/

int			handle_keyrelease(int keycode, t_all *a)
{
	keycode == KEY_A ? a->w->key_event &= ~EV_KEY_A : 0;
	keycode == KEY_S ? a->w->key_event &= ~EV_KEY_S : 0;
	keycode == KEY_D ? a->w->key_event &= ~EV_KEY_D : 0;
	keycode == KEY_W ? a->w->key_event &= ~EV_KEY_W : 0;
	keycode == KEY_LEFT ? a->w->key_event &= ~EV_KEY_LEFT : 0;
	keycode == KEY_RIGHT ? a->w->key_event &= ~EV_KEY_RIGHT : 0;
	keycode == KEY_UP ? a->w->key_event &= ~EV_KEY_UP : 0;
	keycode == KEY_DOWN ? a->w->key_event &= ~EV_KEY_DOWN : 0;
	return (0);
}

/*
** Handles keyboard keys events and draws the frame.
*/

int			handle_events(t_all *a)
{
	a->w->key_event & EV_KEY_A ? move_player(a, KEY_A) : 0;
	a->w->key_event & EV_KEY_S ? move_player(a, KEY_S) : 0;
	a->w->key_event & EV_KEY_D ? move_player(a, KEY_D) : 0;
	a->w->key_event & EV_KEY_W ? move_player(a, KEY_W) : 0;
	a->w->key_event & EV_KEY_LEFT ? rotate_player(a, KEY_LEFT) : 0;
	a->w->key_event & EV_KEY_RIGHT ? rotate_player(a, KEY_RIGHT) : 0;
	a->w->key_event & EV_KEY_UP ? move_player(a, KEY_UP) : 0;
	a->w->key_event & EV_KEY_DOWN ? move_player(a, KEY_DOWN) : 0;
	show_frame(a);
	return (0);
}
