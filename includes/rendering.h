/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 19:54:23 by larosale          #+#    #+#             */
/*   Updated: 2020/08/25 12:20:57 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

/*
** "t_ray" structure type is for structures that hold raycasting
** calculations for each ray.
** It contains:
**   - ray coordinate in camera plane coordinates ("cam_x");
**   - ray vector ("ray_dir_x" and "ray_dir_y");
**   - map block coordinates that correspond to the current player position
**     ("map_x" and "map_y");
**   - distance travelled by ray from player position to the next x or
**     y map border ("side_dist_x" and "side_dist_y");
**   - increments of the distances ("delta_dist_x" and "delta_dist_y");
**   - distance from the wall to the camera plane ("perp_wall_dist");
**   - increments of map coordinates ("step_x" and "step_y");
**   - was the wall hit bool value ("hit") and the side it was hit
**     ("side", 0 for north, 1 for south, 2 for west, 3 for east);
*/

typedef struct		s_ray
{
	double			cam_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
}					t_ray;

/*
** "s_wtex" structure type is for structures that hold wall texturing values.
** It contains:
**   - "line height", "draw_start" and "draw_end" values, used on rendering
**     stage to determine the parameters of the drawn column;
**   - coordinate of the wall when the ray hit it ("wall_x"),
**     the respective texture x-coordinate ("tex_x");
**   - ptr to the texture to use in the pixel column being drawn ("tex_ptr");
**   - "step" variable tells how much to increase texture y-coordinate with
**     every pixel of the screen. After casting to (int) it becomes the
**     actual texture y-coordinate in pixels;
**   - "tex_pos" is the floating-point texture y-coordinate;
**   - "tex_y" is the integer (pixel) texture y-coordinate;
*/

typedef	struct		s_wtex
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x;
	t_img			*tex_ptr;
	double			step;
	double			tex_pos;
	int				tex_y;
}					t_wtex;

/*
** "s_ftex" structure type is for structures that hold floor and ceiling
** texturing calculations. It contains:
**   - real world coordinates of leftmost and rightmost rays that go through
**     x = 0 and x = screen_width;
**   - current y position "p" compared to the center of the screen (horizon);
**   - vertical position of the camera "pos_z" (in the middle of the screen
**     height);
**   - horizontal distance from the camera to the floor for the current
**     rendered line ("row_distance");
**   - real world (map) coordinates of the floor_step vector.
**     This vector goes left to right on the camera plane and has a length,
**     proportional to the floor distance ("row_distance");
**   - real world coordinates of the floor vector, which initally is at
**     leftmost screen column;
**   - integer parts of the "floor" vector coordinates ("cell_x" and "cell_y");
**   - texture coordinates ("tex_x" and "tex_y");
*/

typedef	struct		s_ftex
{
	double			ray_dir_x0;
	double			ray_dir_y0;
	double			ray_dir_x1;
	double			ray_dir_y1;
	int				p;
	double			pos_z;
	double			row_distance;
	double			floor_step_x;
	double			floor_step_y;
	double			floor_x;
	double			floor_y;
	int				cell_x;
	int				cell_y;
	int				ftex_x;
	int				ftex_y;
	int				ctex_x;
	int				ctex_y;
}					t_ftex;

/*
** "s_skytex" structure type is for structures that hold skybox texturing
** calculations. It contains:
**   - texture vertical stepping variable ("step"), which is a number of texels
**     per each screen pixel;
**   - vertical texture position in floating point ("tex_pos");
**   - vertical texture position in int ("tex_y");
**   - horizontal texture position in int ("tex_x");
**   - coordinates of a unit vector pointing at the current (x) screen
**     coordinate;
**   - length of a ray_dir_x (calculated while casting ray and stored in a
**     "s_ray" structure. Length is used to calculate unit vector.
*/

typedef struct		s_skytex
{
	double			step;
	double			tex_pos;
	int				tex_x;
	int				tex_y;
	double			unit_ray_x;
	double			unit_ray_y;
	double			ray_dir_len;
}					t_skytex;

/*
** "s_sprite" structure type is for structures that contain sprite specs.
** It contains:
**   - sprite coordinates;
**   - sprite texture path;
*/

typedef struct		s_sprite
{
	double			spr_x;
	double			spr_y;
	t_img			*spr_tex;
	double			spr_dist;
	double			spr_r_x;
	double			spr_r_y;
	double			spr_t_x;
	double			spr_t_y;
	int				screen_x;
	int				spr_height;
	int				draw_start_y;
	int				draw_end_y;
	int				spr_width;
	int				draw_start_x;
	int				draw_end_x;
	int				tex_x;
	int				tex_y;
}					t_sprite;

/*
** "t_frame" structure type contains pointers to all structures that define
** rendering process (ray casting and texturing).
*/

typedef struct		s_frame
{
	t_ray			*r;
	t_wtex			*wt;
	t_ftex			*ft;
	t_skytex		*skyt;
	double			*z_buf;
}					t_frame;

#endif
