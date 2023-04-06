/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:17:59 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/06 15:53:40 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	basic_error_message(char *err, void *free_this, int fd)
{
	if (free_this)
		free(free_this);
	if (fd >= 0)
		close(fd);
	ft_putendl_fd(ERR_MSG, 2);
	ft_putendl_fd(err, 2);
	exit(EXIT_FAILURE);
}

void	error_exit(t_data *d, char *err, void *free_this)
{
	if (d->mlx_ptr)
	{
		if (d->window)
			mlx_destroy_window(d->mlx_ptr, d->window);
		mlx_destroy_display(d->mlx_ptr);
		free(d->mlx_ptr);
	}
	if (d->map)
	{
		if (d->map->fd >= 0)
			close(d->map->fd);
		free(d->map);
	}
	free(d);
	basic_error_message(err, free_this, -1);
}

void	free_n_exit_safe(t_data *d)
{
	if (d->mlx_ptr)
	{
		if (d->window)
			mlx_destroy_window(d->mlx_ptr, d->window);
		mlx_destroy_display(d->mlx_ptr);
		free(d->mlx_ptr);
	}
	if (d->map)
	{
		if (d->map->fd >= 0)
			close(d->map->fd);
		free(d->map);
	}
	free(d);
	exit(EXIT_SUCCESS);
}
