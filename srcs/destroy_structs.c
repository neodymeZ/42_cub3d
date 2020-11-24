/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 01:26:58 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 14:13:12 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Destructor for "t_win" structure.
*/

int	destroy_win(t_win *win)
{
	if (win)
	{
		win->mlx_ptr && win->win_ptr ?
			mlx_destroy_window(win->mlx_ptr, win->win_ptr) : 0;
		free(win);
	}
	return (0);
}

/*
** Destructor for "t_map" structure.
*/

int	destroy_map(t_map *map)
{
	if (map)
	{
		map->map ? free(map->map) : 0;
		free(map);
	}
	return (0);
}

/*
** Destructor for "t_img" structure.
*/

int	destroy_img(t_img *img)
{
	if (img)
	{
		img->img_ptr ? mlx_destroy_image(img->mlx_ptr, img->img_ptr) : 0;
		free(img);
	}
	return (0);
}

/*
** Destructor for "t_sprite" structure and "t_list" sprites list.
*/

int	destroy_spr(t_sprite *spr, t_list *sprites)
{
	if (spr)
		free(spr);
	if (sprites)
		ft_lstclear(&sprites, free);
	return (0);
}

/*
** Destructor for "t_all" structure.
*/

int	destroy_all(t_all *a)
{
	if (a)
	{
		a->tn ? destroy_img(a->tn) : 0;
		a->ts ? destroy_img(a->ts) : 0;
		a->tw ? destroy_img(a->tw) : 0;
		a->te ? destroy_img(a->te) : 0;
		a->tspr ? destroy_img(a->tspr) : 0;
		a->tf ? destroy_img(a->tf) : 0;
		a->tc ? destroy_img(a->tc) : 0;
		a->tsky ? destroy_img(a->tsky) : 0;
		a->spr_list ? destroy_spr(NULL, a->spr_list) : 0;
		a->m ? destroy_map(a->m) : 0;
		a->i ? destroy_img(a->i) : 0;
		a->w ? destroy_win(a->w) : 0;
		free(a);
	}
	return (0);
}
