/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 00:32:03 by larosale          #+#    #+#             */
/*   Updated: 2020/08/27 15:22:37 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int		main(int argc, char **argv)
{
	char	*cub_path;
	char	*save_flag;

	cub_path = NULL;
	save_flag = NULL;
	if (argc == 2 || argc == 3)
	{
		cub_path = *(argv + 1);
		if (argc == 3)
			save_flag = *(argv + 2);
		if (start_cub3d(cub_path, save_flag))
			return (handle_errors(ERR_UNKNOWN));
	}
	else if (argc == 1)
		return (handle_errors(ERR_NOCUBF));
	else
		return (handle_errors(ERR_INVARG));
	return (EXIT_SUCCESS);
}
