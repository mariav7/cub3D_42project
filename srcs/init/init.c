/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:25 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/03 10:01:22 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_data(t_data **d)
{
	int		ret;
	char	*err_msg;

	err_msg = NULL;
	ret = check_textures(d, &err_msg);
	if (ret == 0)
		error_exit(*d, err_msg, NULL);
	else if (ret == -1)
	{
		ft_putendl_fd(ERR_MSG, 2);
		perror(err_msg);
		error_exit(*d, NULL, NULL);
	}
	ret = check_map((*d)->map, &err_msg);
	if (ret == 0)
		error_exit(*d, err_msg, NULL);
}

void	initial_position(t_data *d)
{
	t_player	*player;

	player = d->game->player;
	player->dirX = -1;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0.66;
	if(d->map->dir == 'E')
	{
		player->dirX = 1;
		player->dirY = 0;
		player->planeX = 0;
		player->planeY = -0.66;
	}
	else if(d->map->dir == 'N')
	{
		player->dirX = 0;
		player->dirY = -1;
		player->planeX = 0.66;
		player->planeY = 0;
	} else if(d->map->dir == 'S')
	{
		player->dirX = 0;
		player->dirY = 1;
		player->planeX = -0.66;
		player->planeY = 0;
	}
}

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
	check_data(d);
	(*d)->game = init_game(
			init_screen(screenWidth, screenHeight, TITLE),
			init_player(*d)
	);
	initial_position(*d);
}

void	start_game(t_data *d)
{
	t_game	*game;

	game = d->game;
	game->screen->img = draw_map(d);
	display_image(game->screen, game->screen->img);
	display_minimap(d);
	mlx_hook(game->screen->window->holder, 2, KeyPressMask, exit_game, d);
	mlx_hook(game->screen->window->holder, 17, KeyPressMask, exit_game, d);
	mlx_hook(game->screen->window->holder, 2, 1L << 0, handle_move, d);
	mlx_loop(game->screen->holder);
}
