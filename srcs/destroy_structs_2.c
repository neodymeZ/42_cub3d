/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_structs_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 00:05:11 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 14:13:00 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Destructor function for t_file type structures.
*/

int	destroy_file(t_file *f)
{
	if (f)
	{
		f->fd >= 0 ? close(f->fd) : 0;
		f->map ? free(f->map) : 0;
		f->saved_file ? ft_lstclear(&(f->saved_file), free) : 0;
		free(f);
	}
	return (0);
}

/*
** Destructor function for "t_frame" type structures.
*/

int	destroy_frame(t_frame *fr)
{
	if (fr)
	{
		fr->r ? free(fr->r) : 0;
		fr->wt ? free(fr->wt) : 0;
		fr->ft ? free(fr->ft) : 0;
		fr->skyt ? free(fr->skyt) : 0;
		fr->z_buf ? free(fr->z_buf) : 0;
		free(fr);
	}
	return (0);
}

/*
** Destructor function for "t_bmp" type structures.
*/

int	destroy_bmp(t_bmp *bmp)
{
	if (bmp)
	{
		bmp->fd >= 0 ? close(bmp->fd) : 0;
		free(bmp);
	}
	return (0);
}
