/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:37:54 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/09 16:12:56 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_calc(t_data *d, t_texture *tex)
{
	t_map	*map;

	map = d->map;
	map->i_data[TEXT_NUM] = map->map[map->i_data[MAP_X]][map->i_data[MAP_Y]] \
	- 48 - 1;
	if (map->i_data[SIDE] == 0)
		map->d_data[WALL_X] = d->game->player->pos_y + \
		map->d_data[PERP_WALL_DIST] * map->d_data[RAY_DIR_Y];
	else
		map->d_data[WALL_X] = d->game->player->pos_x + \
		map->d_data[PERP_WALL_DIST] * map->d_data[RAY_DIR_X];
	map->d_data[WALL_X] -= floor((map->d_data[WALL_X]));
	map->i_data[TEX_X] = (int)(map->d_data[WALL_X] * \
	(double)(tex->image->holder->width));
	if (map->i_data[SIDE] == 0 && map->d_data[RAY_DIR_X] > 0)
	map->i_data[TEX_X] = tex->image->holder->width - map->i_data[TEX_X] - 1;
	if (map->i_data[SIDE] == 1 && map->d_data[RAY_DIR_Y] < 0)
	map->i_data[TEX_X] = tex->image->holder->width - map->i_data[TEX_X] - 1;
	map->d_data[STEP] = 1.0 * tex->image->holder->height / \
	map->i_data[LINE_HEIGHT];
	map->d_data[TEX_POS] = (map->i_data[DRAW_START] - map->i_data[PITCH] - \
	SCREEN_HEIGHT / 2 + map->i_data[LINE_HEIGHT] / 2) * map->d_data[STEP];
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
	int		y;
	int		tex_y;
	int		color;
	int		index;
	char	*dst;

	y = d->map->i_data[DRAW_START] - 1;
	while (++y < d->map->i_data[DRAW_END])
	{
		tex_y = (int) d->map->d_data[TEX_POS] & \
		(tex->image->holder->height - 1);
		d->map->d_data[TEX_POS] += d->map->d_data[STEP];
		color = get_texture(d, tex, tex_y);
		index = (y * d->game->screen->utils->line_length \
		+ (SCREEN_WIDTH - x - 1) * \
		(d->game->screen->utils->bits_per_pixel / 8));
		dst = image->addr + index;
		*(int *)dst = color;
	}
}

void	draw_floor(t_data *d, t_image *image)
{
	char	*dst;
	int		y;
	int		x;

	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			dst = image->addr + (y * d->game->screen->utils->line_length + x * \
			(d->game->screen->utils->bits_per_pixel / 8));
			*(unsigned int *)dst = d->tex->hex_flo;
			dst = image->addr + ((SCREEN_HEIGHT - y - 1) * \
			d->game->screen->utils->line_length + x * \
			(d->game->screen->utils->bits_per_pixel / 8));
			*(unsigned int *)dst = d->tex->hex_ce;
		}
	}
}

t_image	*draw_map(t_data *d)
{
	int			x;
	t_image		*image;
	t_texture	*tex;

	image = init_image(d->game->screen, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!image)
		return (NULL);
	x = -1;
	draw_floor(d, image);
	while (++x < SCREEN_WIDTH)
	{
		map_calc(d, x);
		tex = get_texture_side(d);
		texture_calc(d, tex);
		draw_texture(d, image, x, tex);
	}
	return (image);
}
