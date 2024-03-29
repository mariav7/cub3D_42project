/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:38:21 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/09 15:57:53 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_game *game, int right)
{
	if (right)
		rotate_right(game);
	else
		rotate_left(game);
}

void	rotate_right(t_game *game)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(-game->player->rot_speed) \
	- game->player->dir_y * sin(-game->player->rot_speed);
	game->player->dir_y = olddir_x * sin(-game->player->rot_speed) + \
	game->player->dir_y * cos(-game->player->rot_speed);
	oldplane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * \
	cos(-game->player->rot_speed) - game->player->plane_y * \
	sin(-game->player->rot_speed);
	game->player->plane_y = oldplane_x * sin(-game->player->rot_speed) + \
	game->player->plane_y * cos(-game->player->rot_speed);
}

void	rotate_left(t_game *game)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(game->player->rot_speed) \
	- game->player->dir_y * sin(game->player->rot_speed);
	game->player->dir_y = olddir_x * sin(game->player->rot_speed) + \
	game->player->dir_y * cos(game->player->rot_speed);
	oldplane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * \
	cos(game->player->rot_speed) - game->player->plane_y * \
	sin(game->player->rot_speed);
	game->player->plane_y = oldplane_x * sin(game->player->rot_speed) \
	+ game->player->plane_y * cos(game->player->rot_speed);
}
