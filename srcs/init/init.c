/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:25 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/28 11:09:59 by mflores-         ###   ########.fr       */
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
	player->dirX = 0;
	player->dirY = 1;
	player->planeX = -0.66;
	player->planeY = 0;
	if(d->map->dir == 'W')
	{
		player->dirX = 1;
		player->dirY = 0;
		player->planeY = -player->planeY;
	}
	else if(d->map->dir == 'E')
	{
		player->dirX = -1;
		player->dirY = 0;
	}
	else if(d->map->dir == 'N')
	{
		player->dirX = 0;
		player->dirY = -1;
		player->planeX = 0.66;
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
	//debug_map(*d);
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
	mlx_hook(game->screen->window->holder, 2, KeyPressMask, exit_game, d);
	mlx_hook(game->screen->window->holder, 17, KeyPressMask, exit_game, d);
	mlx_hook(game->screen->window->holder, 2, 1L << 0, handle_move, d);
	//exit_game(game);
	mlx_loop(game->screen->holder);
}

/*void	start_game(t_data *d)
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
}*/
