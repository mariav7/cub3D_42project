/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:37:04 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/08 20:37:08 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_move(int key_code, t_data *d)
{
	t_game	*game;

	game = d->game;
	printf("keycode %d\n", key_code);
	if(key_code == 119)
		go_straight(d);
	else if(key_code == 115)
		go_back(d);
	else if(key_code == 100)
		rotate(game, 0);
	else if(key_code == 97)
		rotate(game, 1);
	else if(key_code == 65307)
		exit_game(d);
	else
		return 1;
	refresh(d);
	return 0;
}

void	go_straight(t_data *data)
{
	t_map	*map;
	t_game	*game;

	map = data->map;
	game = data->game;
	if(ft_strchr("0NESW", map->map[(int) (game->player->pos_x + game->player->dir_x * game->player->move_speed)][(int) game->player->pos_y]) != 0)
		game->player->pos_x += game->player->dir_x * game->player->move_speed;
	if(ft_strchr("0NESW", map->map[(int) game->player->pos_x][(int) (game->player->pos_y + game->player->dir_y * game->player->move_speed)]) != 0)
		game->player->pos_y += game->player->dir_y * game->player->move_speed;
	printf("new pos_x %f new pos_y %f\n", game->player->pos_x, game->player->pos_y);
}

void	go_back(t_data *data)
{
	t_map	*map;
	t_game	*game;

	map = data->map;
	game = data->game;
	if(ft_strchr("0NESW", map->map[(int) (game->player->pos_x - game->player->dir_x * game->player->move_speed)][(int) game->player->pos_y]) != 0)
		game->player->pos_x -= game->player->dir_x * game->player->move_speed;
	if(ft_strchr("0NESW", map->map[(int) game->player->pos_x][(int) (game->player->pos_y - game->player->dir_y * game->player->move_speed)]) != 0)
		game->player->pos_y -= game->player->dir_y * game->player->move_speed;
}
