/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 00:52:24 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 17:02:04 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Checks the elements part of .cub file for duplicates and missing required
** elements.
** Returns 1 on error and 0 otherwise.
*/

static	int	check_elements(char *el, t_file *f)
{
	int dup;

	dup = 0;
	if (!ft_strnstr(el, "R", 1) && !ft_strnstr(el, "NO", 2) &&
		!ft_strnstr(el, "SO", 2) && !ft_strnstr(el, "WE", 2) &&
		!ft_strnstr(el, "EA", 2) && !ft_strnstr(el, "S", 1) &&
		!ft_strnstr(el, "F", 1) && !ft_strnstr(el, "C", 1))
		return (!cleanup(ERR_PARREQ, NULL, f) ? 1 : 0);
	*el == 'R' && f->resolution ? dup = 1 : 0;
	*el == 'N' && *(el + 1) == 'O' && f->ntex_path ? dup = 1 : 0;
	*el == 'S' && *(el + 1) == 'O' && f->stex_path ? dup = 1 : 0;
	*el == 'W' && *(el + 1) == 'E' && f->wtex_path ? dup = 1 : 0;
	*el == 'E' && *(el + 1) == 'A' && f->etex_path ? dup = 1 : 0;
	*el == 'S' && *(el + 1) == 'T' && f->skytex_path ? dup = 1 : 0;
	*el == 'S' && *(el + 1) != 'T' && *(el + 1) != 'O' &&
		f->sprite_path ? dup = 1 : 0;
	*el == 'F' && *(el + 1) == 'T' && f->ftex_path ? dup = 1 : 0;
	*el == 'F' && *(el + 1) != 'T' && f->floor_color ? dup = 1 : 0;
	*el == 'C' && *(el + 1) == 'T' && f->ctex_path ? dup = 1 : 0;
	*el == 'C' && *(el + 1) != 'T' && f->ceil_color ? dup = 1 : 0;
	if (dup)
		return (!cleanup(ERR_PARDUP, NULL, f) ? 1 : 0);
	return (0);
}

/*
** Parses the elements part of .cub file and saves the respective lines
** to the "f" structure.
*/

static int	save_elements(char *el, t_file *f)
{
	*el == 'R' ? f->resolution = el + 1 : 0;
	*el == 'N' && *(el + 1) == 'O' ? f->ntex_path = el + 2 : 0;
	*el == 'S' && *(el + 1) == 'O' ? f->stex_path = el + 2 : 0;
	*el == 'W' && *(el + 1) == 'E' ? f->wtex_path = el + 2 : 0;
	*el == 'E' && *(el + 1) == 'A' ? f->etex_path = el + 2 : 0;
	*el == 'S' && *(el + 1) == 'T' ? f->skytex_path = el + 2 : 0;
	*el == 'S' && *(el + 1) != 'T' && *(el + 1) != 'O' ?
		f->sprite_path = el + 1 : 0;
	*el == 'F' && *(el + 1) == 'T' ? f->ftex_path = el + 2 : 0;
	*el == 'F' && *(el + 1) != 'T' ? f->floor_color = el + 1 : 0;
	*el == 'C' && *(el + 1) == 'T' ? f->ctex_path = el + 2 : 0;
	*el == 'C' && *(el + 1) != 'T' ? f->ceil_color = el + 1 : 0;
	return (0);
}

/*
** Parses the map part of .cub file and saves the respective
** lines to the "f" structure.
** Returns 1 on error, or 0 otherwise.
*/

static int	save_map(t_list *file, t_file *f, int map_size)
{
	char	**temp;

	if (!(f->resolution) || !(f->ntex_path) || !(f->stex_path) ||
		!(f->wtex_path) || !(f->etex_path) || !(f->sprite_path) ||
		!(f->floor_color) || !(f->ceil_color))
		return (!cleanup(ERR_PARREQ, NULL, f) ? 1 : 0);
	if (!(f->map = ft_calloc(map_size + 1, sizeof(char *))))
		return (!cleanup(ERR_SYS, NULL, f) ? 1 : 0);
	temp = f->map;
	while (file)
	{
		if (*(char *)(file->content) == ' ' || *(char *)(file->content) == '1')
		{
			*temp = file->content;
			temp++;
		}
		else if (*(char *)(file->content) != '\0')
			return (!cleanup(ERR_PARMNL, NULL, f) ? 1 : 0);
		file = file->next;
	}
	*temp = NULL;
	return (0);
}

/*
** Parses the linked list with lines of text, as read from .cub file.
** Saves the obtained information to the structure "f".
** Uses auxillary functions "save_elements" and "save_map".
** Returns 1 on error, or 0 otherwise.
*/

static int	parse_file(t_list *saved_file, t_file *f)
{
	t_list	*t;
	int		map_size;

	t = saved_file;
	map_size = 0;
	while (t)
	{
		if (*(char *)(t->content) == '\0')
		{
			t = t->next;
			continue ;
		}
		else if (*(char *)(t->content) == ' ' || *(char *)(t->content) == '1')
			break ;
		if (check_elements((char *)t->content, f) ||
			save_elements((char *)t->content, f))
			return (1);
		t = t->next;
	}
	saved_file = t;
	while (*(char *)(t->content) == ' ' || *(char *)(t->content) == '1')
		t = t->next;
	if (save_map(saved_file, f, ft_lstsize(saved_file) - ft_lstsize(t)))
		return (1);
	return (0);
}

/*
** Reads .cub file line by line and saves each line to the linked list.
** Then passes the list to the "parse_file" function for the first pass
** of parsing.
** Returns the structure of "t_file" type for further processing.
*/

t_file		*read_cub_file(char *fpath)
{
	char	*line;
	t_file	*f;
	t_list	*read_line;

	if (!(ft_strnstr(fpath, "cub", ft_strlen(fpath))))
		return (cleanup(ERR_FNOEXT, NULL, NULL));
	if (!(f = ft_calloc(1, sizeof(t_file))) ||
		(f->fd = open(fpath, O_RDONLY)) < 0)
		return (cleanup(ERR_SYS, NULL, f));
	while (get_next_line(f->fd, &line) > 0)
	{
		if (!(read_line = ft_lstnew(line)))
			return (cleanup(ERR_SYS, NULL, f));
		ft_lstadd_back(&(f->saved_file), read_line);
	}
	if (!(read_line = ft_lstnew(line)))
		return (cleanup(ERR_SYS, NULL, f));
	ft_lstadd_back(&(f->saved_file), read_line);
	if (parse_file(f->saved_file, f))
		return (NULL);
	close(f->fd);
	f->fd = -1;
	return (f);
}
