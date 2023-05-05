#include "cub3d.h"

unsigned int buffer[screenWidth][screenHeight];

void	points_color(double d_data[8], int i_data[10])
{
	if(i_data[SIDE] == 0)
		d_data[PERP_WALL_DIST] = (d_data[SIDE_DIST_X] - d_data[DELTA_DIST_X]);
	else
		d_data[PERP_WALL_DIST] = (d_data[SIDE_DIST_Y] - d_data[DELTA_DIST_Y]);
	i_data[LINE_HEIGHT] = (int)(screenHeight / d_data[PERP_WALL_DIST]);
	i_data[DRAW_START] = -i_data[LINE_HEIGHT] / 2 + screenHeight / 2 + i_data[PITCH];
	if(i_data[DRAW_START] < 0)
		i_data[DRAW_START] = 0;
	i_data[DRAW_END] = i_data[LINE_HEIGHT] / 2 + screenHeight / 2 + i_data[PITCH];;
	if(i_data[DRAW_END] >= screenHeight)
		i_data[DRAW_END] = screenHeight - 1;
	i_data[COLOR] = 0x00FFFF00;
	if(i_data[SIDE] == 1)
		i_data[COLOR] = i_data[COLOR] / 2;
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
		if(map->map[i_data[MAP_Y]][i_data[MAP_X]] == '1' || map->map[i_data[MAP_Y]][i_data[MAP_X]] == ' ')
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

void	vert_line(t_data *d, t_image *image, int x) {
	int xx;

	for (int y = d->map->i_data[DRAW_START]; y <= d->map->i_data[DRAW_END]; y++)
	{
		if(d->map->dir == 'N' || d->map->dir == 'S')
			xx = x;
		else
			xx = screenWidth - x - 1;
		image_put_pixel(d->game->screen, image, xx, y, d->map->i_data[COLOR]);
	}
}

void	handle_loop(t_data *d, t_image *image)
{
	t_game	*game;
	t_map	*map;

	game = d->game;
	map = d->map;
	map->i_data[PITCH] = 100;
	for(int x = 0; x < screenWidth; x++)
	{
	  calc(game, map->d_data, map->i_data, x);
	  calc_ray_dir(game, map->d_data, map->i_data);
	  intersect_wall(map, map->d_data, map->i_data);
	  points_color(map->d_data, map->i_data);
	  map->i_data[TEXT_NUM] = map->map[map->i_data[MAP_Y]][map->i_data[MAP_X]] - 48 - 1; //1 subtracted from it so that texture 0 can be used!
	  if(map->i_data[SIDE] == 0)
		  map->d_data[WALL_X] = game->player->posY + map->d_data[PERP_WALL_DIST] * map->d_data[RAY_DIR_Y];
	  else
		  map->d_data[WALL_X] = game->player->posX + map->d_data[PERP_WALL_DIST] * map->d_data[RAY_DIR_X];
	  map->d_data[WALL_X] -= floor((map->d_data[WALL_X]));
	  map->i_data[TEX_X] = (int) (map->d_data[WALL_X] * (double) (texWidth));
	  if(map->i_data[SIDE] == 0 && map->d_data[RAY_DIR_X] > 0)
		  map->i_data[TEX_X] = texWidth - map->i_data[TEX_X] - 1;
	  if(map->i_data[SIDE] == 1 && map->d_data[RAY_DIR_Y] < 0)
		  map->i_data[TEX_X] = texWidth - map->i_data[TEX_X] - 1;
	  map->d_data[STEP] = 1.0 * texHeight / map->i_data[LINE_HEIGHT];
	  map->d_data[TEX_POS] = (map->i_data[DRAW_START] - screenHeight / 2 + map->i_data[LINE_HEIGHT] / 2) * map->d_data[STEP];
	  for(int y = map->i_data[DRAW_START]; y < d->map->i_data[DRAW_END]; y++)
	  {
		int texY = ((y - (map->d_data[RAY_DIR_Y] / 2) + (map->i_data[LINE_HEIGHT] / 2)) * 1024) / (map->i_data[LINE_HEIGHT]);
		//printf("texy %d\n", texY);
		map->d_data[TEX_POS] += map->d_data[STEP];
		unsigned int color = (unsigned int) ((t_texture *) game->textures->head->content)->buffer[1024 * texY + map->i_data[TEX_X]];
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		image_put_pixel(d->game->screen, image, x, y, color);
	  }
	  //vert_line(d, image, x);
	}
	printf("hola\n");
}

t_image	*draw_map(t_data *d)
{
	t_image *image = init_image(d->game->screen, screenWidth, screenHeight);
	if (!image)
		return (NULL);
	handle_loop(d, image);
	return (image);
}
