/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:25 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/17 12:13:21 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_structs(t_data **d, int fd, char *file)
{
	t_map	*m;
	t_tex	*t;

	*d = ft_calloc(sizeof(t_data), 1);
	if (*d == NULL)
		basic_error_message(ERR_CALLOC, NULL, fd);
	m = ft_calloc(sizeof(t_map), 1);
	if (m == NULL)
		basic_error_message(ERR_CALLOC, *d, fd);
	t = ft_calloc(sizeof(t_tex), 1);
	if (t == NULL)
		basic_error_message(ERR_CALLOC, *d, fd);
	(*d)->map = m;
	(*d)->tex = t;
	m->fd = fd;
	m->path = file;
	parse_file(d);
}

void	start_game(t_data *d)
{
	d->mlx_ptr = mlx_init();
	if (d->mlx_ptr == NULL)
		error_exit(d, ERR_MLX, NULL);
	d->window = mlx_new_window(d->mlx_ptr, WIN1_SX, WIN1_SY, TITLE);
	if (d->window == NULL)
		error_exit(d, ERR_MLX_WIN, NULL);
	mlx_hook(d->window, 2, 1L << 0, key_event, d);
	mlx_hook(d->window, 17, 1L << 17, close_window, d);
	mlx_loop(d->mlx_ptr);
}
