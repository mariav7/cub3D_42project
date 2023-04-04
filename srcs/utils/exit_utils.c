/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:17:59 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/04 11:53:01 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	basic_error_message(char *err, void *free_this)
{
	if (free_this)
		free(free_this);
	ft_putstr_fd(ERR_MSG, 2);
	ft_putendl_fd(err, 2);
	exit(EXIT_FAILURE);
}
