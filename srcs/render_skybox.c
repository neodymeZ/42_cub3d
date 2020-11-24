/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_skybox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 12:54:32 by larosale          #+#    #+#             */
/*   Updated: 2020/08/14 15:21:19 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Renders skybox for the specified horizontal screen coordinate "x".
** Uses cylinder texture mapping.
*/

void	render_skybox(int x, t_ray *r, t_skytex *skyt, t_all *a)
{
	int				y;
	unsigned int	color;

	if (!(a->tc) && (a->tsky))
	{
		clear_skytex(skyt);
		y = 0;
		skyt->step = (double)(a->tsky->img_height) / (a->w->win_height / 2);
		skyt->ray_dir_len = sqrt(r->ray_dir_x * r->ray_dir_x +
			r->ray_dir_y * r->ray_dir_y);
		skyt->unit_ray_x = r->ray_dir_x / skyt->ray_dir_len;
		skyt->unit_ray_y = r->ray_dir_y / skyt->ray_dir_len;
		skyt->tex_x = (int)(ft_math_arclen(skyt->unit_ray_x, skyt->unit_ray_y) /
			(2 * PI) * a->tsky->img_width);
		while (y < a->w->win_height / 2)
		{
			skyt->tex_y = (int)(skyt->tex_pos);
			skyt->tex_pos += skyt->step;
			color = *(unsigned int *)(a->tsky->img_addr + skyt->tex_y *
				a->tsky->img_line_size + skyt->tex_x * a->tsky->img_bpp / 8);
			pixel_put(a->i, x, y, color);
			y++;
		}
	}
	return ;
}
