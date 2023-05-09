/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:38:29 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/08 20:38:31 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player *init_player(t_data *d)
{
	t_player *player = calloc(sizeof(t_player), 1);
	if (!player)
		return (NULL);
	player->plane_x =  0;
	player->plane_y = 0.66;
	player->pos_x = d->map->pos_y + 0.5;
	player->pos_y = d->map->pos_x + 0.5;
	player->move_speed = 1;
	player->rot_speed = 0.10;
	player->dir_x = -1;
	player->dir_y = 0;
	return (player);
}
