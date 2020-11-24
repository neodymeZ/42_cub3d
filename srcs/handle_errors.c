/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 00:41:24 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 17:01:23 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Prints error code based on error number "e" (see also errors.h).
*/

void	print_error(int e)
{
	e == ERR_SYS ? ft_putstr_fd("A system call error occured\n", 2) : 0;
	e == ERR_MLX ? ft_putstr_fd("An MLX ptr creation error occured\n", 2) : 0;
	e == ERR_UNKNOWN ? ft_putstr_fd("Unknown error occurred\n", 2) : 0;
	e == ERR_NOCUBF ? ft_putstr_fd("No map (.cub file) specified\n", 2) : 0;
	e == ERR_INVARG ? ft_putstr_fd("Invalid command-line arguments\n", 2) : 0;
	e == ERR_INVFLG ? ft_putstr_fd("Invalid flag. Use --save\n", 2) : 0;
	e == ERR_FNOEXT ? ft_putstr_fd("File has no .cub extension\n", 2) : 0;
	e == ERR_PARREQ ?
		ft_putstr_fd("Required elements are missing in .cub file\n", 2) : 0;
	e == ERR_PARDUP ? ft_putstr_fd("Duplicate elements in .cub file\n", 2) : 0;
	e == ERR_PARMNL ? ft_putstr_fd("Symbols after map in .cub file\n", 2) : 0;
	e == ERR_PARRES ? ft_putstr_fd("Incorrect resolution value\n", 2) : 0;
	e == ERR_PARCLR ? ft_putstr_fd("Incorrect floor/ceil color value\n", 2) : 0;
	e == ERR_PARTEX ? ft_putstr_fd("Incorrect texture path(-s)\n", 2) : 0;
	e == ERR_PARMDP ? ft_putstr_fd("Duplicate player position\n", 2) : 0;
	e == ERR_PARGEO ? ft_putstr_fd("Incorrect symbols on the map\n", 2) : 0;
	e == ERR_PARNPP ? ft_putstr_fd("No player position on the map\n", 2) : 0;
	e == ERR_PARNCL ? ft_putstr_fd("Map is not surrounded with walls\n", 2) : 0;
	return ;
}

/*
** Prints error message related to the error code "errnum".
** If "errno" was set by failed system calls or mlx, prints errno debug info.
** In case of successful exit, nothing is printed.
*/

int		handle_errors(int errnum)
{
	if (errnum)
	{
		ft_putstr_fd("Error\n", 2);
		print_error(errnum);
		if (errno && (errnum == ERR_SYS || errnum == ERR_MLX ||
			errnum == ERR_UNKNOWN))
			perror("Additional debugging info (errno)");
		exit(EXIT_FAILURE);
		return (1);
	}
	else
	{
		exit(EXIT_SUCCESS);
		return (0);
	}
}
