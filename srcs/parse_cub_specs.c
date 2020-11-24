/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_specs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 00:51:20 by larosale          #+#    #+#             */
/*   Updated: 2020/08/21 18:55:06 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Trims leading spaces of the input string "str". Then iterates the string
** until the next space (if any) and puts NUL char. If non-space characters
** are found after NUL, the function returns NULL. Otherwise, a pointer to
** the first non-space symbol is returned.
*/

static char		*trim_spaces(char *str)
{
	char	*temp;

	if (!str)
		return (NULL);
	while (*str == ' ')
		str++;
	temp = str;
	while (*temp && *temp != ' ')
		temp++;
	if (*temp == ' ')
	{
		*temp++ = '\0';
		while (*temp)
		{
			if (*temp != ' ')
				return (NULL);
			temp++;
		}
	}
	return (str);
}

/*
** Converts numeric string to integer for parsing color (with "flag" == 0)
** and for parsing resolution (with "flag" == 1).
** If the resulting number is out of bounds, or if "str" contains non-numeric
** symbols (except for delimiters), the function returns -1.
** Otherwise, it returns the resulting number and modifies the "str" pointer
** to point at the next number (after delimiter).
*/

static int		convert_num(char **str, int flag)
{
	int		atoi_res;
	char	*string;

	if (!(string = *str))
		return (-1);
	if ((!flag && ((atoi_res = ft_atoi(string)) < 0 || atoi_res > 255)) ||
		(flag && (atoi_res = ft_atoi(string)) < 0))
		return (-1);
	while (*string && ft_isdigit(*string))
		string++;
	if ((!flag && *string && *string != ',') ||
		(flag && *string && *string != ' ') || string == *str)
		return (-1);
	if (*string == '\0')
		*str = string;
	else
		*str = ++string;
	return (atoi_res);
}

/*
** Parses texturing information from the .cub file.
** Fills the resulting texture paths to the "m" map structure.
** Returns 1 on error, or 0 if successful.
*/

int				parse_tex(t_file *f, t_map *m)
{
	if (!(m->ntex_path = trim_spaces(f->ntex_path)) ||
		!(m->stex_path = trim_spaces(f->stex_path)) ||
		!(m->wtex_path = trim_spaces(f->wtex_path)) ||
		!(m->etex_path = trim_spaces(f->etex_path)) ||
		!(m->sprite_path = trim_spaces(f->sprite_path)))
		return (1);
	m->ftex_path = trim_spaces(f->ftex_path);
	m->ctex_path = trim_spaces(f->ctex_path);
	m->skytex_path = trim_spaces(f->skytex_path);
	return (0);
}

/*
** Parses information about floor and ceiling colors from the .cub file.
** Fills the resulting integers to the "m" map structure.
** Returns 1 on error, or 0 if successful.
*/

int				parse_color(t_file *f, t_map *m)
{
	int color_f;
	int color_c;

	if (!(f->floor_color = trim_spaces(f->floor_color)) ||
		!(f->ceil_color = trim_spaces(f->ceil_color)) ||
		(color_f = convert_num(&(f->floor_color), 0)) < 0 ||
		(color_c = convert_num(&(f->ceil_color), 0)) < 0)
		return (1);
	m->floor_color = (unsigned int)color_f << 16;
	m->ceil_color = (unsigned int)color_c << 16;
	if ((color_f = convert_num(&(f->floor_color), 0)) < 0 ||
		(color_c = convert_num(&(f->ceil_color), 0)) < 0)
		return (1);
	m->floor_color += (unsigned int)color_f << 8;
	m->ceil_color += (unsigned int)color_c << 8;
	if ((color_f = convert_num(&(f->floor_color), 0)) < 0 ||
		(color_c = convert_num(&(f->ceil_color), 0)) < 0)
		return (1);
	m->floor_color += (unsigned int)color_f;
	m->ceil_color += (unsigned int)color_c;
	return (0);
}

/*
** Parses information about screen resolution from the .cub file.
** Fills the resulting integers to the "w" map structure.
** Returns 1 on error of 0 if successful.
*/

int				parse_resolution(t_file *f, t_win *w)
{
	int	res_x;
	int	res_y;

	while (*(f->resolution) == ' ')
		f->resolution += 1;
	if ((res_x = convert_num(&(f->resolution), 1)) < 0)
		return (1);
	while (*(f->resolution) == ' ')
		f->resolution += 1;
	if ((res_y = convert_num(&(f->resolution), 1)) < 0)
		return (1);
	w->win_width = res_x;
	w->win_height = res_y;
	return (0);
}
