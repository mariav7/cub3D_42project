/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:47:30 by nmunoz            #+#    #+#             */
/*   Updated: 2023/05/09 15:50:09 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*init_image(t_screen *screen, int width, int height)
{
	t_image	*image;

	image = calloc(sizeof(t_image), 1);
	if (!image)
		return (NULL);
	image->holder = mlx_new_image(screen->holder, width, height);
	image->addr = mlx_get_data_addr(image->holder, \
	&screen->utils->bits_per_pixel, &screen->utils->line_length,
			&screen->utils->endian);
	return (image);
}

t_window	*init_window(t_screen *screen, int width, int height, char *name)
{
	t_window	*window;

	window = calloc(sizeof(t_window), 1);
	if (!window)
		return (NULL);
	window->holder = mlx_new_window(screen->holder, width, height, name);
	return (window);
}

t_screen	*init_screen(int width, int height, char *name)
{
	t_screen	*screen;

	screen = calloc(sizeof(t_screen), 1);
	if (!screen)
		return (NULL);
	screen->utils = calloc(sizeof(t_screen_utils), 1);
	screen->holder = mlx_init();
	screen->window = init_window(screen, width, height, name);
	return (screen);
}

void	display_image(t_screen *screen, t_image *image)
{
	mlx_put_image_to_window(screen->holder, screen->window->holder, \
	image->holder, 0, 0);
}
