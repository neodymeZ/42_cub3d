/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 19:52:39 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 01:41:57 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_H
# define FILES_H

# include <stdint.h>
# include <fcntl.h>
# include <unistd.h>

/*
** "t_file" structure type is for structures that contain information,
** parsed from .cub file.
*/

typedef struct		s_file
{
	char			*resolution;
	char			*ntex_path;
	char			*stex_path;
	char			*wtex_path;
	char			*etex_path;
	char			*sprite_path;
	char			*floor_color;
	char			*ceil_color;
	char			*ftex_path;
	char			*ctex_path;
	char			*skytex_path;
	char			**map;
	t_list			*saved_file;
	int				fd;
}					t_file;

/*
** "t_bmp" structure contains bmp header and other relevant information.
*/

typedef struct		s_bmp
{
	uint16_t		file_type;
	uint32_t		file_size;
	uint16_t		reserved1;
	uint16_t		reserved2;
	uint32_t		pd_offset;
	uint32_t		head_size;
	int32_t			img_width;
	int32_t			img_height;
	uint16_t		planes;
	uint16_t		bpp;
	uint32_t		compression;
	uint32_t		img_size;
	int32_t			x_pix_pm;
	int32_t			y_pix_pm;
	uint32_t		total_colors;
	uint32_t		imp_colors;
	int				fd;
}					t_bmp;

#endif
