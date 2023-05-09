/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:58:50 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/09 15:59:54 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*get_texture_side(t_data *d)
{
	if (d->map->i_data[SIDE] == 0)
	{
		if (d->map->d_data[RAY_DIR_X] > 0)
			return ((t_texture *) \
			list_get_by_index(d->game->textures, 1)->content);
		else
			return ((t_texture *) \
			list_get_by_index(d->game->textures, 0)->content);
	}
	else
	{
		if (d->map->d_data[RAY_DIR_Y] > 0)
			return ((t_texture *) \
			list_get_by_index(d->game->textures, 2)->content);
		else
			return ((t_texture *) \
			list_get_by_index(d->game->textures, 3)->content);
	}
}
