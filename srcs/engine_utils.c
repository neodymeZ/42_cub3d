/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:29:11 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 14:12:07 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Image-based function to draw a pixel (faster alternative of
** mlx_pixel_put function.
*/

void	pixel_put(t_img *i, int x, int y, unsigned int color)
{
	int		offset;
	char	*dst_addr;

	offset = y * i->img_line_size + x * i->img_bpp / 8;
	dst_addr = i->img_addr + offset;
	*(unsigned int *)dst_addr = color;
}

/*
** Adjusts "color" according to the "distance".
*/

void	color_shading(unsigned int *color, double distance)
{
	double			decay_c;
	unsigned int	res_color;

	decay_c = distance < 1.0 ? 1.0 : 1.0 / distance / sqrt(distance);
	res_color = (unsigned int)((*color >> 16) * decay_c) << 16;
	res_color += (unsigned int)(((*color & 0xFF00) >> 8) * decay_c) << 8;
	res_color += (unsigned int)((*color & 0xFF) * decay_c);
	*color = res_color;
}
