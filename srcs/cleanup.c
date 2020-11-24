/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 15:08:37 by larosale          #+#    #+#             */
/*   Updated: 2020/08/28 12:24:22 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Cleans up and releases all resources used by the application.
*/

void	*cleanup(int errnum, t_all *a, t_file *f)
{
	destroy_file(f);
	destroy_all(a);
	handle_errors(errnum);
	return (NULL);
}
