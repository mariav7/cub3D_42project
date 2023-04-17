/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:17:59 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/14 19:35:50 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

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
	if (d->view->mlx_ptr)
	{
		if (d->view->win_ptr)
			mlx_destroy_window(d->view->mlx_ptr, d->view->win_ptr);
		mlx_destroy_display(d->view->mlx_ptr);
		free(d->view->mlx_ptr);
	}
	if (d->map_after)
	{
		if (d->map_after->fd >= 0)
			close(d->map_after->fd);
		if (d->map_after->file)
			free(d->map_after->file);
		free(d->map);
	}
	if (d->tex)
	{
		if (d->tex->no)
			free(d->tex->no);
		if (d->tex->so)
			free(d->tex->so);
		if (d->tex->ea)
			free(d->tex->ea);
		if (d->tex->we)
			free(d->tex->we);
		if (d->tex->ce)
			free(d->tex->ce);
		if (d->tex->flo)
			free(d->tex->flo);
		free(d->tex);
	}
	free(d);
	basic_error_message(err, free_this, -1);
}

void	free_n_exit_safe(t_data *d)
{
	if (d->view->mlx_ptr)
	{
		if (d->view->win_ptr)
			mlx_destroy_window(d->view->mlx_ptr, d->view->win_ptr);
		mlx_destroy_display(d->view->mlx_ptr);
		free(d->view->mlx_ptr);
	}
	if (d->map_after)
	{
		if (d->map_after->fd >= 0)
			close(d->map_after->fd);
		if (d->map_after->file)
			free(d->map_after->file);
		free(d->map);
	}
	if (d->tex)
	{
		if (d->tex->no)
			free(d->tex->no);
		if (d->tex->so)
			free(d->tex->so);
		if (d->tex->ea)
			free(d->tex->ea);
		if (d->tex->we)
			free(d->tex->we);
		if (d->tex->ce)
			free(d->tex->ce);
		if (d->tex->flo)
			free(d->tex->flo);
		free(d->tex);
	}
	free(d);
	exit(EXIT_SUCCESS);
}
