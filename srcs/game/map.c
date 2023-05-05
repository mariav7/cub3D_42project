#include "cub3d.h"

unsigned int buffer[screenWidth][screenHeight];

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

int	get_textel_val(t_data *d, t_texture *texture, int texY)
{
	int				res;
	int				tex_i;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	tex_i = texY * texture->utils->line_length + \
			d->map->i_data[TEX_X] * (texture->utils->bits_per_pixel / 8);
	r = (unsigned char)(texture->image->addr)[tex_i + 2];
	g = (unsigned char)(texture->image->addr)[tex_i + 1];
	b = (unsigned char)(texture->image->addr)[tex_i];
	res = ((int)r << 16) + ((int)g << 8) + (int)b;
	return (res);
}

void	handle_loop(t_data *d, t_image *image)
{
	t_game	*game;
	t_map	*map;

	(void) image;
	game = d->game;
	map = d->map;
	for(int x = 0; x < screenWidth; x++)
	{
	  calc(game, map->d_data, map->i_data, x);
	  calc_ray_dir(game, map->d_data, map->i_data);
	  intersect_wall(map, map->d_data, map->i_data);
	  points_color(d->game->player, map->d_data, map->i_data);
	  map->i_data[TEXT_NUM] = map->map[map->i_data[MAP_X]][map->i_data[MAP_Y]] - 48 - 1; //1 subtracted from it so that texture 0 can be used!
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
	  map->d_data[TEX_POS] = (map->i_data[DRAW_START] - map->i_data[PITCH] - screenHeight / 2 + map->i_data[LINE_HEIGHT] / 2) * map->d_data[STEP];
	  for(int y = map->i_data[DRAW_START]; y < d->map->i_data[DRAW_END]; y++)
	  {
		int texY = (int) map->d_data[TEX_POS] & (((t_texture *) game->textures->head->content)->image->holder->height - 1);
		map->d_data[TEX_POS] += map->d_data[STEP];
		int color = get_textel_val(d, (t_texture *) game->textures->head->content, texY);
		int index = (y * d->game->screen->utils->line_length + x * \
				(d->game->screen->utils->bits_per_pixel / 8));
		printf("index %d - y %d - line_len %d - x %d - bpp %d\n", index, y, d->game->screen->utils->line_length , x, d->game->screen->utils->bits_per_pixel);
		char *dst = d->game->screen->img->addr + index;
		*(int *)dst = color;
		//int texY = (int) map->d_data[TEX_POS] & (((t_texture *) game->textures->head->content)->image->holder->height - 1);// ((y - (map->d_data[RAY_DIR_Y] / 2) + (map->i_data[LINE_HEIGHT] / 2)) * texHeight) / (map->i_data[LINE_HEIGHT]);
		//map->d_data[TEX_POS] += map->d_data[STEP];
		//unsigned int color = (unsigned int) ((t_texture *) game->textures->head->content)->buffer[texHeight * texY + map->i_data[TEX_X]];
		//printf("%x\n", color);
		//image_put_pixel(d->game->screen, image, x, y, color);
	  }
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
