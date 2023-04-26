#include "../../includes/cub3d.h"

void	points_color(t_game *game, double d_data[8], int i_data[10])
{
	if(i_data[SIDE] == 0)
		d_data[PERP_WALL_DIST] = (d_data[SIDE_DIST_X] - d_data[DELTA_DIST_X]);
	else
		d_data[PERP_WALL_DIST] = (d_data[SIDE_DIST_Y] - d_data[DELTA_DIST_Y]);
	i_data[LINE_HEIGHT] = (int)(screenHeight / d_data[PERP_WALL_DIST]);
	i_data[DRAW_START] = -i_data[LINE_HEIGHT] / 2 + screenHeight / 2;
	if(i_data[DRAW_START] < 0)
		i_data[DRAW_START] = 0;
	i_data[DRAW_END] = i_data[LINE_HEIGHT] / 2 + screenHeight / 2;
	if(i_data[DRAW_END] >= screenHeight)
		i_data[DRAW_END] = screenHeight - 1;
	switch(game->map->map[i_data[MAP_X]][i_data[MAP_Y]])
	{
		case 1:  i_data[COLOR] = 0x00FF0000;    break; //red
		case 2:  i_data[COLOR] = 0x0066CC00;  break; //green
		case 3:  i_data[COLOR] = 0x000000FF;   break; //blue
		case 4:  i_data[COLOR] = 0x00FFFFFF;  break; //white
		default: i_data[COLOR] = 0x00FFFF00; break; //yellow
	}
	if(i_data[SIDE] == 1)
		i_data[COLOR] = i_data[COLOR] / 2;
}

void	intersect_wall(t_game *game, double d_data[8], int i_data[10])
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
		if(game->map->map[i_data[MAP_X]][i_data[MAP_Y]] > 0)
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

void	handle_loop(t_game *game, t_image *image)
{
	for(int x = 0; x < screenWidth; x++)
	{
	  calc(game, game->map->d_data, game->map->i_data, x);
	  calc_ray_dir(game, game->map->d_data, game->map->i_data);
	  intersect_wall(game, game->map->d_data, game->map->i_data);
	  points_color(game, game->map->d_data, game->map->i_data);
	  for (int y = game->map->i_data[DRAW_START]; y <= game->map->i_data[DRAW_END]; y++)
		image_put_pixel(game->screen, image, x, y, game->map->i_data[COLOR]);
	}
}

t_image	*draw_map(t_game *game)
{
	t_image *image = init_image(game->screen, screenWidth, screenHeight);
	if (!image)
		return (NULL);
	handle_loop(game, image);
	return (image);
}
