/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:27:02 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 13:33:32 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/*
** The "e_errors" enum and corresponding type determine the list of error
** codes used for error handling with the following meaning:
**   - ERR_SYS: system call error (file opening, memory allocation, etc);
**   - ERR_UNKNOWN: used in main to handle an error, not catched earlier
**     in helper functions;
**   - ERR_NOCUBF: no .cub file path was specified with the second command-line
**     argument;
**   - ERR_INVARG: more than two command-line arguments were specified;
**   - ERR_INVFLG: second command-line argument was not "--save";
**   - ERR_FNOEXT: file name specified as the first command-line argument
**     has no .cub extension;
**   - ERR_FNOREQ: the supplied .cub file is missing some of the required
**     elements;
**   - ERR_FMAPNL: some text exists after the map in .cub file (empty lines
**     are permitted);
**   - ERR_PARRES: incorrect resolution specified in .cub file (negative,
**     too large, or that couldn't be parsed by ft_atoi function);
**   - ERR_PARCLR: incorrect floor/ceiling color values specified in .cub file
**     (out of bounds or could not be parsed by ft_atoi function);
**   - ERR_PARTEX: texture paths are incorrectly specified in .cub file
**     (extra symbols are found in the string);
**   - ERR_PARMDP: player position has duplicates on the map;
**   - ERR_PARGEO: map contains not permitted symbols;
**   - ERR_PARNPP: no player position is specified on the map;
**   - ERR_PARNCL: map is not closed (not surrounded by walls properly);
*/

typedef enum	e_errors
{
	ERR_OK = 0,
	ERR_UNKNOWN = -1,
	ERR_SYS = -2,
	ERR_MLX = -3,
	ERR_NOCUBF = -4,
	ERR_INVARG = -5,
	ERR_INVFLG = -6,
	ERR_FNOEXT = -10,
	ERR_PARREQ = -11,
	ERR_PARDUP = -12,
	ERR_PARMNL = -13,
	ERR_PARRES = -14,
	ERR_PARCLR = -15,
	ERR_PARTEX = -16,
	ERR_PARMDP = -17,
	ERR_PARGEO = -18,
	ERR_PARNPP = -19,
	ERR_PARNCL = -20
}				t_errors;

#endif
