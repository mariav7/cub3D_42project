/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:10:35 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/08 20:15:26 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->image->adr[pixel] = color;
}

static int	get_mmap_offset(t_minimap *minimap, int mapsize, int pos)
{
	if (pos > minimap->view_dist && mapsize - pos > minimap->view_dist + 1)
		return (pos - minimap->view_dist);
	if (pos > minimap->view_dist && mapsize - pos <= minimap->view_dist + 1)
		return (mapsize - minimap->size);
	return (0);
}

static int	is_valid_map_coord(int coord, int size)
{
	if (coord < size)
		return (1);
	return (0);
}

static char	*add_minimap_line(t_data *d, t_minimap *m, int y)
{
	char	*line;
	int		x;

	line = ft_calloc(m->size + 1, sizeof * line);
	if (!line)
		return (NULL);
	x = 0;
	while (x < m->size && x < SCREEN_WIDTH)
	{
		if (!is_valid_map_coord(y + m->offset_y, SCREEN_HEIGHT)
			|| !is_valid_map_coord(x + m->offset_x, SCREEN_WIDTH))
			line[x] = '\0';
		else if ((int)d->game->player->pos_x == (x + m->offset_x)
			&& (int)d->game->player->pos_y == (y + m->offset_y))
			line[x] = 'P';
		else if (d->map->map[y + m->offset_y][x + m->offset_x] == '1')
			line[x] = '1';
		else if (d->map->map[y + m->offset_y][x + m->offset_x] == '0')
			line[x] = '0';
		else
			line[x] = '\0';
		x++;
	}
	return (line);
}

static char	**generate_minimap(t_data *data, t_minimap *minimap)
{
	char	**mmap;
	int		y;

	mmap = ft_calloc(minimap->size + 1, sizeof * mmap);
	if (!mmap)
		return (NULL);
	y = 0;
	while (y < minimap->size && y < SCREEN_HEIGHT)
	{
		mmap[y] = add_minimap_line(data, minimap, y);
		if (!mmap[y])
		{
			free_tab((void **)mmap);
			return (NULL);
		}
		y++;
	}
	return (mmap);
}

static void	set_minimap_tile_pixels(t_minimap *minimap, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < minimap->tile_size)
	{
		j = 0;
		while (j < minimap->tile_size)
		{
			set_image_pixel(minimap->img, x + j, i + y, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_tile(t_minimap *minimap, int x, int y)
{
	if (minimap->map[y][x] == 'N' || minimap->map[y][x] == 'S' || minimap->map[y][x] == 'W' || minimap->map[y][x] == 'E')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0x00FF00);
	else if (minimap->map[y][x] == '1')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0x808080);
	else if (minimap->map[y][x] == '0')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0xE6E6E6);
	else if (minimap->map[y][x] == ' ')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0x404040);
}

static void	set_minimap_border_image_pixels(t_minimap *minimap, int color)
{
	int	size;
	int	x;
	int	y;

	size = 128 + minimap->tile_size;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x <= size)
		{
			if (x < 5 || x > size - 5 || y < 5 || y > size - 5)
				set_image_pixel(minimap->img, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_minimap(t_minimap *minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < minimap->size)
	{
		x = 0;
		while (x < minimap->size)
		{
			if (!minimap->map[y] || !minimap->map[y][x]
				|| minimap->map[y][x] == '\0')
				break ;
			draw_minimap_tile(minimap, x, y);
			x++;
		}
		y++;
	}
	set_minimap_border_image_pixels(minimap, 0x404040);
}

static void	render_minimap_image(t_data *data, t_minimap *minimap)
{
	int	img_size;

	img_size = 128 + minimap->tile_size;
	init_img(data, &data->game->screen->img, img_size, img_size);
	draw_minimap(minimap);
	mlx_put_image_to_window(data->game->screen->holder, data->game->screen->window, data->game->screen->img->holder,
		minimap->tile_size, SCREEN_HEIGHT
		- (128 + (minimap->tile_size * 2)));
	mlx_destroy_image(data->game->screen->holder, data->game->screen->img);
}

void	render_minimap(t_data *data)
{
	t_minimap	minimap;

	minimap.map = NULL;
	data->minimap = &minimap;
	minimap.img = &data->game->screen->img;
	minimap.view_dist = 4;
	minimap.size = (2 * minimap.view_dist) + 1;
	minimap.tile_size = 128 / (2 * minimap.view_dist);
	minimap.offset_x = get_mmap_offset(&minimap,
			SCREEN_WIDTH, (int)data->game->player->pos_x);
	minimap.offset_y = get_mmap_offset(&minimap,
			SCREEN_HEIGHT, (int)data->game->player->pos_y);
	minimap.map = generate_minimap(data, &minimap);
	if (!minimap.map)
		return ;
	render_minimap_image(data, &minimap);
	free_tab((void **)minimap.map);
}