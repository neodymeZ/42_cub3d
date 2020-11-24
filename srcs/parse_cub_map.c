/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 01:05:30 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 01:32:59 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Based on direction symbol on char map, fills the "pos_x", "pos_y",
** "dir_x", "dir_y", "plane_x" and "plane_y" values of "m" structure.
** NB: In map, x-coordinate is vertical, y-coordinate is horizontal.
** Zero coordinates are in the top left corner of the map.
*/

static void	parse_pos(t_file *f, t_map *m, int x, int y)
{
	char	**map;

	map = f->map;
	m->pos_x = x + 0.5;
	m->pos_y = y + 0.5;
	map[x][y] == 'N' ? m->dir_x = -1 : 0;
	map[x][y] == 'N' ? m->plane_y = tan(FOV / 360 * PI) : 0;
	map[x][y] == 'S' ? m->dir_x = 1 : 0;
	map[x][y] == 'S' ? m->plane_y = -tan(FOV / 360 * PI) : 0;
	map[x][y] == 'W' ? m->dir_y = -1 : 0;
	map[x][y] == 'W' ? m->plane_x = -tan(FOV / 360 * PI) : 0;
	map[x][y] == 'E' ? m->dir_y = 1 : 0;
	map[x][y] == 'E' ? m->plane_x = tan(FOV / 360 * PI) : 0;
	map[x][y] = '0';
	return ;
}

/*
** Checks a zero cell of the map (at the position "i") for neighboring
** -1 cells.
** Returns 1 on error, or 0 otherwise.
*/

static int	check_zero_cell(t_map *m, int i)
{
	int *map;
	int	w;

	map = m->map;
	w = m->map_width;
	if ((map[i - 1] == -1) || (map[i + 1] == -1) || (map[i + w] == -1) ||
		(map[i - w] == -1) || (map[i - w - 1] == -1) || (map[i - w + 1] == -1)
		|| (map[i + w - 1] == -1) || (map[i + w + 1] == -1))
		return (1);
	return (0);
}

/*
** Checks, if the player position was set.
** Then checks, whether the map is correctly surrounded by walls.
** To do so, it first checks perimeter for 0 cells.
** Then it checks every inner 0-cells for the neighbor -1 cells using
** "check_zero_cell" helper function.
** Returns 1 on error, or 0 otherwise.
*/

static int	check_map(t_file *f, t_all *a, t_map *m)
{
	int	*map;
	int i;

	i = -1;
	map = m->map;
	if ((!m->pos_x || !m->pos_y) && !destroy_map(m))
		return (cleanup(ERR_PARNPP, a, f) ? 0 : 1);
	while (map[++i] != -2)
	{
		if (!(i % m->map_width) || (i % m->map_width == m->map_width - 1) ||
			(i < m->map_width) || (i >= m->map_width * (m->map_height - 1)))
		{
			if (map[i] == 0 && !destroy_map(m))
				return (cleanup(ERR_PARNCL, a, f) ? 0 : 1);
		}
		else
		{
			if (map[i] == 0 && check_zero_cell(m, i) && !destroy_map(m))
				return (cleanup(ERR_PARNCL, a, f) ? 0 : 1);
		}
	}
	return (0);
}

/*
** Converts char map to integer map and saves it in "m" for further handling.
** Checks the map for incorrect symbols.
** The integer map is an one-dimensional array, terminated with -2.
** Spaces are represented as -1.
** Returns 1 on error, or 0 otherwise.
*/

static int	convert_map(t_file *f, t_all *a, t_map *m)
{
	int		*i_map;
	int		i;
	int		j;

	i = -1;
	if (!(i_map = ft_calloc(m->map_height * m->map_width + 1, sizeof(int))) &&
		!destroy_map(m))
		return (cleanup(ERR_SYS, a, f) ? 0 : 1);
	m->map = i_map;
	while ((f->map)[++i])
	{
		j = -1;
		while ((f->map)[i][++j])
		{
			if (!(ft_strchr(MAP_GEO, (f->map)[i][j])) && !destroy_map(m))
				return (cleanup(ERR_PARGEO, a, f) ? 0 : 1);
			(f->map)[i][j] == ' ' ? *i_map = -1 : 0;
			ft_isdigit((f->map)[i][j]) ? *i_map = (f->map)[i][j] - '0' : 0;
			i_map++;
		}
		while (j++ < m->map_width)
			*i_map++ = -1;
	}
	*i_map = -2;
	return (0);
}

/*
** Parses map, checks its validity and converts to int array for handling.
** To do so, the function traverses the "f->map" char array and finds
** position marker (and passes it to "parse_pos" function), then counts
** map dimensions (and passes it to "convert_map" function).
** Returns 1 on error (duplicate position marker, incorrect symbols in the
** map and other errors), or 0 otherwise.
*/

int			parse_map(t_file *f, t_all *a, t_map *m)
{
	char	**map;
	int		i;
	int		j;

	i = -1;
	map = f->map;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr(MAP_POS, map[i][j]))
			{
				if ((m->pos_x || m->pos_y) && !destroy_map(m))
					return (cleanup(ERR_PARMDP, a, f) ? 0 : 1);
				parse_pos(f, m, i, j);
			}
		}
		if (j > m->map_width)
			m->map_width = j;
	}
	m->map_height = i;
	if (convert_map(f, a, m) || check_map(f, a, m))
		return (1);
	return (0);
}
