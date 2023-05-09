/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:37:04 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/09 17:03:50 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_move(int key_code, t_data *d)
{
	t_game	*game;

	game = d->game;
	if (key_code == MOVE_FORWARD)
		go_straight(d);
	else if (key_code == MOVE_BACKWARDS)
		go_back(d);
	else if (key_code == MOVE_LEFT)
		go_left(d);
	else if (key_code == MOVE_RIGHT)
		go_right(d);
	else if (key_code == LOOK_RIGHT)
		rotate(game, 1);
	else if (key_code == LOOK_LEFT)
		rotate(game, 0);
	else if (key_code == ESCAPE)
		exit_game(d);
	else
		return (1);
	refresh(d);
	return (0);
}

void	go_straight(t_data *data)
{
	t_map	*map;
	t_game	*game;

	map = data->map;
	game = data->game;
	if (ft_strchr("0NESW", \
	map->map[(int)(game->player->pos_x + game->player->dir_x * \
	game->player->move_speed)][(int)game->player->pos_y]) != 0)
		game->player->pos_x += game->player->dir_x * \
		game->player->move_speed;
	if (ft_strchr("0NESW", map->map[(int)game->player->pos_x] \
	[(int)(game->player->pos_y + game->player->dir_y * \
	game->player->move_speed)]) != 0)
		game->player->pos_y += game->player->dir_y * \
		game->player->move_speed;
}

void	go_left(t_data *data)
{
	t_map	*map;
	t_game	*game;

	map = data->map;
	game = data->game;
	if (ft_strchr("0NESW", map->map[(int)(game->player->pos_x - \
	game->player->dir_y * (game->player->move_speed))] \
	[(int)game->player->pos_y]))
		game->player->pos_x -= game->player->dir_y * game->player->move_speed;
	if (ft_strchr("0NESW", map->map[(int)game->player->pos_x] \
	[(int)(game->player->pos_y + data->game->player->dir_x * \
	(game->player->move_speed))]))
		game->player->pos_y += game->player->dir_x * game->player->move_speed;
}

void	go_right(t_data *data)
{
	t_map	*map;
	t_game	*game;

	map = data->map;
	game = data->game;
	if (ft_strchr("0NESW", map->map[(int)(game->player->pos_x + \
	game->player->dir_y * (game->player->move_speed))] \
	[(int)game->player->pos_y]))
		game->player->pos_x += game->player->dir_y * game->player->move_speed;
	if (ft_strchr("0NESW", map->map[(int)game->player->pos_x] \
	[(int)(game->player->pos_y - game->player->dir_x * \
	(game->player->move_speed))]))
		game->player->pos_y -= game->player->dir_x * game->player->move_speed;
}

void	go_back(t_data *data)
{
	t_map	*map;
	t_game	*game;

	map = data->map;
	game = data->game;
	if (ft_strchr("0NESW", map->map[(int)(game->player->pos_x - \
	game->player->dir_x * game->player->move_speed)] \
	[(int)game->player->pos_y]) != 0)
		game->player->pos_x -= game->player->dir_x * game->player->move_speed;
	if (ft_strchr("0NESW", map->map[(int)game->player->pos_x] \
	[(int)(game->player->pos_y - game->player->dir_y * \
	game->player->move_speed)]) != 0)
		game->player->pos_y -= game->player->dir_y * game->player->move_speed;
}
