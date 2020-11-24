/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:01:45 by larosale          #+#    #+#             */
/*   Updated: 2020/08/21 23:46:52 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Clears the contents of "ray" structure.
** Used by "cast_ray" function.
*/

void	clear_ray(t_ray *ray)
{
	ray->cam_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->perp_wall_dist = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->side = 0;
}

/*
** Clears the contents of "wtex" structure.
** Used by "render_walls" function.
*/

void	clear_wtex(t_wtex *wtex)
{
	wtex->line_height = 0;
	wtex->draw_start = 0;
	wtex->draw_end = 0;
	wtex->wall_x = 0;
	wtex->tex_x = 0;
	wtex->tex_ptr = NULL;
	wtex->step = 0;
	wtex->tex_pos = 0;
	wtex->tex_y = 0;
	return ;
}

/*
** Clears the contents of "ftex" structure.
** Used by "render_wall_and_ceil" function.
*/

void	clear_ftex(t_ftex *ftex)
{
	ftex->ray_dir_x0 = 0;
	ftex->ray_dir_y0 = 0;
	ftex->ray_dir_x1 = 0;
	ftex->ray_dir_y1 = 0;
	ftex->p = 0;
	ftex->pos_z = 0;
	ftex->row_distance = 0;
	ftex->floor_step_x = 0;
	ftex->floor_step_y = 0;
	ftex->floor_x = 0;
	ftex->floor_y = 0;
	ftex->cell_x = 0;
	ftex->cell_y = 0;
	ftex->ftex_x = 0;
	ftex->ftex_y = 0;
	ftex->ctex_x = 0;
	ftex->ctex_y = 0;
	return ;
}

/*
** Clears the contents of "skytex" structure.
** Used by "render_skybox" function.
*/

void	clear_skytex(t_skytex *skytex)
{
	skytex->step = 0;
	skytex->tex_pos = 0;
	skytex->tex_x = 0;
	skytex->tex_y = 0;
	skytex->unit_ray_x = 0;
	skytex->unit_ray_y = 0;
	skytex->ray_dir_len = 0;
	return ;
}
