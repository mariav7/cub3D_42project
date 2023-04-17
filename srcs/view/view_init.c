/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz- <nmunoz@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:56:18 by nmunoz-           #+#    #+#             */
/*   Updated: 2023/04/14 12:14:04 by nmunoz-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	view_init(t_data *d) {

	t_view	*v;

	v = d->view;

	v->mlx_ptr = mlx_init();
	if (v->mlx_ptr == NULL)
		error_exit(d, ERR_MLX, NULL);
	v->win_ptr = mlx_new_window(v->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	if (v->win_ptr == NULL)
		error_exit(d, ERR_MLX_WIN, NULL);
	v->img_ptr = mlx_new_image(v->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (v->img_ptr == NULL)
		error_exit(d, ERR_MLX_IMG, NULL);
	v->addr = mlx_get_data_addr(v->img_ptr, &v->bits_per_pixel, &v->line_length,
								&v->endian);


	int map_data[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			d->map[i][j] = map_data[i][j];
		}
	}
}

void	view_hooks(t_data *d) {
	mlx_hook(d->view->win_ptr, 2, 1L << 0, key_event, d);
	mlx_hook(d->view->win_ptr, 17, 1L << 17, close_window, d);
}
