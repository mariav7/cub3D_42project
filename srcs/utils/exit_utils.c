/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:17:59 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/24 10:54:29 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_data *d)
{
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
}

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
	if (err)
	{
		ft_putendl_fd(ERR_MSG, 2);
		ft_putendl_fd(err, 2);
	}
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
		if (d->map->file)
			free(d->map->file);
		if (d->map->map)
			free_tab((void **)d->map->map);
		free(d->map);
	}
	free_textures(d);
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
		if (d->map->file)
			free(d->map->file);
		if (d->map->map)
			free_tab((void **)d->map->map);
		free(d->map);
	}
	free_textures(d);
	free(d);
	exit(EXIT_SUCCESS);
}
