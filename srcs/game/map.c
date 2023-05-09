#include "cub3d.h"

void texture_calc(t_data *d, t_texture *tex)
{
	t_map	*map;

	map = d->map;
	map->i_data[TEXT_NUM] = map->map[map->i_data[MAP_X]][map->i_data[MAP_Y]] - 48 - 1; //1 subtracted from it so that texture 0 can be used!
	if(map->i_data[SIDE] == 0)
	map->d_data[WALL_X] = d->game->player->posY + map->d_data[PERP_WALL_DIST] * map->d_data[RAY_DIR_Y];
	else
	map->d_data[WALL_X] = d->game->player->posX + map->d_data[PERP_WALL_DIST] * map->d_data[RAY_DIR_X];
	map->d_data[WALL_X] -= floor((map->d_data[WALL_X]));
	map->i_data[TEX_X] = (int) (map->d_data[WALL_X] * (double) (tex->image->holder->width));
	if(map->i_data[SIDE] == 0 && map->d_data[RAY_DIR_X] > 0)
	map->i_data[TEX_X] = tex->image->holder->width - map->i_data[TEX_X] - 1;
	if(map->i_data[SIDE] == 1 && map->d_data[RAY_DIR_Y] < 0)
	map->i_data[TEX_X] = tex->image->holder->width - map->i_data[TEX_X] - 1;
	map->d_data[STEP] = 1.0 * tex->image->holder->height / map->i_data[LINE_HEIGHT];
	map->d_data[TEX_POS] = (map->i_data[DRAW_START] - map->i_data[PITCH] - screenHeight / 2 + map->i_data[LINE_HEIGHT] / 2) * map->d_data[STEP];
}

int	get_texture(t_data *d, t_texture *texture, int texY)
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

void	draw_texture(t_data *d, t_image *image, int x, t_texture *tex)
{
	int	y;

	y = d->map->i_data[DRAW_START] - 1;
	while(++y < d->map->i_data[DRAW_END])
	{
		int texY = (int) d->map->d_data[TEX_POS] & (tex->image->holder->height - 1);
		d->map->d_data[TEX_POS] += d->map->d_data[STEP];
		int color = get_texture(d, tex, texY);
		int index = (y * d->game->screen->utils->line_length + (screenWidth - x - 1) * \
				(d->game->screen->utils->bits_per_pixel / 8));
		char *dst = image->addr + index;
		*(int *)dst = color;
	}
}

void	draw_floor(t_data *d, t_image *image)
{
	for(int y = 0; y < screenHeight; y++)
	{
	  for(int x = 0; x < screenWidth; ++x)
	  {
		image_put_pixel(d->game->screen, image, x, y, FLOOR_COLOR);
		image_put_pixel(d->game->screen, image, x, screenHeight - y - 1, CEIL_COLOR);
	  }
	}
}

t_image	*draw_map(t_data *d)
{
	t_image *image;
	t_texture	*tex;
	int	x;

	image = init_image(d->game->screen, screenWidth, screenHeight);
	if (!image)
		return (NULL);
	x = -1;
	draw_floor(d, image);
	while(++x < screenWidth)
	{
	  map_calc(d, x);
	  tex = get_texture_side(d);
	  texture_calc(d, tex);
	  draw_texture(d, image, x, tex);
	}
	printf("%d\n", ((t_texture *) d->game->textures->head->content)->image->holder->width);
	return (image);
}
