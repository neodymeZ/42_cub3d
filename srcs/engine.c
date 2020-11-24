/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 12:01:41 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 12:58:47 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Renders frame using the parameters, specified in "a" structure.
*/

int		render_frame(t_all *a)
{
	t_frame	*frame;
	int		x;
	int		y;

	if (!(frame = define_frame(a->file, a)))
		return (1);
	x = 0;
	y = a->w->win_height / 2;
	while (++y < a->w->win_height)
		render_floor_and_ceil(y, frame->ft, a);
	while (x < a->w->win_width)
	{
		cast_ray(x, frame->r, a);
		render_skybox(x, frame->r, frame->skyt, a);
		render_walls(x, frame->r, frame->wt, a);
		*(frame->z_buf + x) = frame->r->perp_wall_dist;
		x++;
	}
	render_sprites(a, frame);
	destroy_frame(frame);
	return (0);
}

/*
** Shows rendered frame on the screen.
** Uses mlx_sync for frame buffering to avoid image artifacts.
*/

void	show_frame(t_all *a)
{
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, a->i->img_ptr);
	render_frame(a);
	mlx_put_image_to_window(a->w->mlx_ptr, a->w->win_ptr, a->i->img_ptr, 0, 0);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, a->w->win_ptr);
	return ;
}

/*
** Sets MLX event hooks for pressing and releasing keyboard keys,
** moving mouse and closing window.
** Key auto repeat is turned off due to mlx_loop_hook usage.
*/

void	set_mlx_hooks(t_all *world)
{
	mlx_do_key_autorepeatoff(world->w->mlx_ptr);
	mlx_mouse_hide();
	mlx_hook(world->w->win_ptr, EV_KEYPRESS, 0, handle_keypress, world);
	mlx_hook(world->w->win_ptr, EV_KEYRELEASE, 0, handle_keyrelease, world);
	mlx_hook(world->w->win_ptr, EV_EXIT, 0, handle_exit, world);
	mlx_hook(world->w->win_ptr, EV_MOUSEMOVE, 0, handle_mouse_move, world);
	mlx_loop_hook(world->w->mlx_ptr, handle_events, world);
	return ;
}

/*
** Main routine
*/

int		start_cub3d(char *filename, char *save_flag)
{
	t_all	*world;
	t_file	*file;

	if (save_flag && ft_strncmp("--save", save_flag, ft_strlen(save_flag)))
		return (handle_errors(ERR_INVFLG));
	ft_putstr_fd("Reading map file... ", 1);
	if (!(file = read_cub_file(filename)))
		return (1);
	ft_putstr_fd("OK\nRendering world... ", 1);
	if (!(world = define_all(file)))
		return (1);
	world->file = file;
	show_frame(world);
	save_flag ? ft_putstr_fd("OK\nSaving screenshot to BMP file... ", 1) : 0;
	if (save_flag && save_bmp(file, world))
		return (1);
	set_mlx_hooks(world);
	ft_putstr_fd("OK\n", 1);
	mlx_loop(world->w->mlx_ptr);
	return (0);
}
