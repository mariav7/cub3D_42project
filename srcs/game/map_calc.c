/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:37:45 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/08 20:37:45 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	points_color(t_player *player, double d_data[8], int i_data[10])
{
	// printf("MAP_X %d - MAP_Y %d - pos_x %f - pos_y %f - STEP_X %d - STEP_Y %d - DIR_X %f - DIR_Y %f\n", i_data[MAP_X], i_data[MAP_Y], player->pos_x, player->pos_y, i_data[STEP_X], i_data[STEP_Y], d_data[RAY_DIR_X], d_data[RAY_DIR_Y]);
	if(i_data[SIDE] == 0)
		d_data[PERP_WALL_DIST] = (i_data[MAP_X] - player->pos_x + (1 - i_data[STEP_X]) / 2) /  d_data[RAY_DIR_X];    //(d_data[SIDE_DIST_X] - d_data[DELTA_DIST_X]);
	else
		d_data[PERP_WALL_DIST] = (i_data[MAP_Y] - player->pos_y + (1 - i_data[STEP_Y]) / 2) / d_data[RAY_DIR_Y];    //(d_data[SIDE_DIST_Y] - d_data[DELTA_DIST_Y]);
	// printf("SCREEN_HEIGHT %d - PERP_WALL_DIST %f\n", SCREEN_HEIGHT, d_data[PERP_WALL_DIST]);
	i_data[LINE_HEIGHT] = (int)(SCREEN_HEIGHT / d_data[PERP_WALL_DIST]);
	i_data[PITCH] = 0;
	// printf("line height %d\n", i_data[LINE_HEIGHT]);
	i_data[DRAW_START] = -(i_data[LINE_HEIGHT]) / 2 + SCREEN_HEIGHT / 2 + i_data[PITCH];
	if(i_data[DRAW_START] < 0)
		i_data[DRAW_START] = 0;
	i_data[DRAW_END] = i_data[LINE_HEIGHT] / 2 + SCREEN_HEIGHT / 2 + i_data[PITCH];;
	if(i_data[DRAW_END] >= SCREEN_HEIGHT)
		i_data[DRAW_END] = SCREEN_HEIGHT - 1;
}

void	intersect_wall(t_map *map, double d_data[8], int i_data[10])
{
	while(i_data[HIT] == 0)
	{
		if(d_data[SIDE_DIST_X] < d_data[SIDE_DIST_Y])
		{
			d_data[SIDE_DIST_X] += d_data[DELTA_DIST_X];
			i_data[MAP_X] += i_data[STEP_X];
			i_data[SIDE] = 0;
		}
		else
		{
			d_data[SIDE_DIST_Y] += d_data[DELTA_DIST_Y];
			i_data[MAP_Y] += i_data[STEP_Y];
			i_data[SIDE] = 1;
		}
		if(map->map[i_data[MAP_X]][i_data[MAP_Y]] == '1' || map->map[i_data[MAP_X]][i_data[MAP_Y]] == ' ')
			i_data[HIT] = 1;
	}
}

void	calc_ray_dir(t_game *game, double d_data[8], int i_data[10])
{
	if(d_data[RAY_DIR_X] < 0)
	{
		i_data[STEP_X] = -1;
		d_data[SIDE_DIST_X] = (game->player->pos_x - i_data[MAP_X]) * d_data[DELTA_DIST_X];
	}
	else
	{
		i_data[STEP_X] = 1;
		d_data[SIDE_DIST_X] = (i_data[MAP_X] + 1.0 - game->player->pos_x) * d_data[DELTA_DIST_X];
	}
	if(d_data[RAY_DIR_Y] < 0)
	{
		i_data[STEP_Y] = -1;
		d_data[SIDE_DIST_Y] = (game->player->pos_y - i_data[MAP_Y]) * d_data[DELTA_DIST_Y];
	}
	else
	{
		i_data[STEP_Y] = 1;
		d_data[SIDE_DIST_Y] = (i_data[MAP_Y] + 1.0 - game->player->pos_y) * d_data[DELTA_DIST_Y];
	}
}

void	calc(t_game *game, double d_data[8], int i_data[10], int x)
{
	d_data[CAMERA_X] = 2 * x / (double) SCREEN_WIDTH - 1;
	d_data[RAY_DIR_X] = game->player->dir_x + game->player->plane_x * d_data[CAMERA_X];
	d_data[RAY_DIR_Y] = game->player->dir_y + game->player->plane_y * d_data[CAMERA_X];
	i_data[MAP_X] = (int) game->player->pos_x;
	i_data[MAP_Y] = (int) game->player->pos_y;
	d_data[DELTA_DIST_X] = (d_data[RAY_DIR_X] == 0) ? 1e30 : fabs(1 / d_data[RAY_DIR_X]);
	d_data[DELTA_DIST_Y] = (d_data[RAY_DIR_Y] == 0) ? 1e30 : fabs(1 / d_data[RAY_DIR_Y]);
	i_data[HIT] = 0;
}

void	map_calc(t_data *d, int x)
{
	calc(d->game, d->map->d_data, d->map->i_data, x);
	calc_ray_dir(d->game, d->map->d_data, d->map->i_data);
	intersect_wall(d->map, d->map->d_data, d->map->i_data);
	points_color(d->game->player, d->map->d_data, d->map->i_data);
}
