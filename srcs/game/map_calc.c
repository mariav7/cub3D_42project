#include "../../includes/cub3d.h"

void	points_color(t_player *player, double d_data[8], int i_data[10])
{
	printf("MAP_X %d - MAP_Y %d - posX %f - posY %f - STEP_X %d - STEP_Y %d - DIR_X %f - DIR_Y %f\n", i_data[MAP_X], i_data[MAP_Y], player->posX, player->posY, i_data[STEP_X], i_data[STEP_Y], d_data[RAY_DIR_X], d_data[RAY_DIR_Y]);
	if(i_data[SIDE] == 0)
		d_data[PERP_WALL_DIST] = (i_data[MAP_X] - player->posX + (1 - i_data[STEP_X]) / 2) /  d_data[RAY_DIR_X];    //(d_data[SIDE_DIST_X] - d_data[DELTA_DIST_X]);
	else
		d_data[PERP_WALL_DIST] = (i_data[MAP_Y] - player->posY + (1 - i_data[STEP_Y]) / 2) / d_data[RAY_DIR_Y];    //(d_data[SIDE_DIST_Y] - d_data[DELTA_DIST_Y]);
	printf("screenHeight %d - PERP_WALL_DIST %f\n", screenHeight, d_data[PERP_WALL_DIST]);
	i_data[LINE_HEIGHT] = (int)(screenHeight / d_data[PERP_WALL_DIST]);
	i_data[PITCH] = 0;
	printf("line height %d\n", i_data[LINE_HEIGHT]);
	i_data[DRAW_START] = -(i_data[LINE_HEIGHT]) / 2 + screenHeight / 2 + i_data[PITCH];
	if(i_data[DRAW_START] < 0)
		i_data[DRAW_START] = 0;
	i_data[DRAW_END] = i_data[LINE_HEIGHT] / 2 + screenHeight / 2 + i_data[PITCH];;
	if(i_data[DRAW_END] >= screenHeight)
		i_data[DRAW_END] = screenHeight - 1;
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
		d_data[SIDE_DIST_X] = (game->player->posX - i_data[MAP_X]) * d_data[DELTA_DIST_X];
	}
	else
	{
		i_data[STEP_X] = 1;
		d_data[SIDE_DIST_X] = (i_data[MAP_X] + 1.0 - game->player->posX) * d_data[DELTA_DIST_X];
	}
	if(d_data[RAY_DIR_Y] < 0)
	{
		i_data[STEP_Y] = -1;
		d_data[SIDE_DIST_Y] = (game->player->posY - i_data[MAP_Y]) * d_data[DELTA_DIST_Y];
	}
	else
	{
		i_data[STEP_Y] = 1;
		d_data[SIDE_DIST_Y] = (i_data[MAP_Y] + 1.0 - game->player->posY) * d_data[DELTA_DIST_Y];
	}
}

void	calc(t_game *game, double d_data[8], int i_data[10], int x)
{
	d_data[CAMERA_X] = 2 * x / (double) screenWidth - 1;
	d_data[RAY_DIR_X] = game->player->dirX + game->player->planeX * d_data[CAMERA_X];
	d_data[RAY_DIR_Y] = game->player->dirY + game->player->planeY * d_data[CAMERA_X];
	i_data[MAP_X] = (int) game->player->posX;
	i_data[MAP_Y] = (int) game->player->posY;
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
