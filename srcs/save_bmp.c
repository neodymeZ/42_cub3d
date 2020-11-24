/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 13:53:04 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 14:14:30 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Defines a structure which contains .bmp file header parameters.
** Returns NULL on error, or the resulting structure otherwise.
*/

static t_bmp	*define_bmp(t_all *a)
{
	t_bmp	*bmp;

	if (!(bmp = ft_calloc(1, sizeof(t_bmp))))
		return (NULL);
	bmp->file_type = 0x4d42;
	bmp->pd_offset = 0x36;
	bmp->head_size = 0x28;
	bmp->img_width = a->i->img_width;
	bmp->img_height = a->i->img_height;
	bmp->planes = 0x1;
	bmp->bpp = a->i->img_bpp;
	return (bmp);
}

/*
** Helper function to write an element "el" of size "size" bytes to the
** .bmp file.
** Returns 1 on error, or 0 otherwise.
*/

static int		write_el(int fd, void *el, int size)
{
	if (write(fd, (unsigned char *)el, size) < 0)
		return (1);
	return (0);
}

/*
** Writes header to the .bmp file, using the values defined in
** "bmp" structure.
** Returns 1 on error, or 0 otherwise.
*/

static int		write_headers(int fd, t_bmp *bmp)
{
	if (write_el(fd, &(bmp->file_type), sizeof(bmp->file_type)) ||
		write_el(fd, &(bmp->file_size), sizeof(bmp->file_size)) ||
		write_el(fd, &(bmp->reserved1), sizeof(bmp->reserved1)) ||
		write_el(fd, &(bmp->reserved2), sizeof(bmp->reserved2)) ||
		write_el(fd, &(bmp->pd_offset), sizeof(bmp->pd_offset)) ||
		write_el(fd, &(bmp->head_size), sizeof(bmp->head_size)) ||
		write_el(fd, &(bmp->img_width), sizeof(bmp->img_width)) ||
		write_el(fd, &(bmp->img_height), sizeof(bmp->img_height)) ||
		write_el(fd, &(bmp->planes), sizeof(bmp->planes)) ||
		write_el(fd, &(bmp->bpp), sizeof(bmp->bpp)) ||
		write_el(fd, &(bmp->compression), sizeof(bmp->compression)) ||
		write_el(fd, &(bmp->img_size), sizeof(bmp->img_size)) ||
		write_el(fd, &(bmp->x_pix_pm), sizeof(bmp->x_pix_pm)) ||
		write_el(fd, &(bmp->y_pix_pm), sizeof(bmp->y_pix_pm)) ||
		write_el(fd, &(bmp->total_colors), sizeof(bmp->total_colors)) ||
		write_el(fd, &(bmp->imp_colors), sizeof(bmp->imp_colors)))
		return (1);
	return (0);
}

/*
** Writes line of pixels to the .bmp file.
** Returns 1 on error, or 0 otherwise.
*/

static int		write_line(int fd, int line, t_img *i)
{
	int		x;
	char	*pixel;

	x = 0;
	while (x < i->img_width)
	{
		pixel = i->img_addr + line * i->img_line_size + x * i->img_bpp / 8;
		if (write_el(fd, pixel, i->img_bpp / 8))
			return (1);
		x++;
	}
	return (0);
}

/*
** Saves the first rendered frame to the .bmp file.
** Path to the .bmp file is specified in engine.h ("BMP_SAVE_PATH").
** Returns 1 on error, or 0 otherwise.
*/

int				save_bmp(t_file *f, t_all *a)
{
	int				line;
	t_bmp			*bmp;

	if (!(bmp = define_bmp(a)))
		return (!cleanup(ERR_SYS, a, f) ? 1 : 0);
	if ((bmp->fd = open(BMP_SAVE_PATH, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR |
		S_IWUSR)) < 0 && !destroy_bmp(bmp))
		return (!cleanup(ERR_SYS, a, f) ? 1 : 0);
	if (write_headers(bmp->fd, bmp) && !destroy_bmp(bmp))
		return (!cleanup(ERR_SYS, a, f) ? 1 : 0);
	line = a->i->img_height;
	while (--line >= 0)
	{
		if (write_line(bmp->fd, line, a->i) && !destroy_bmp(bmp))
			return (!cleanup(ERR_SYS, a, f) ? 1 : 0);
	}
	destroy_bmp(bmp);
	return (0);
}
