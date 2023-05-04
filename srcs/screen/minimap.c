/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:10:35 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/03 22:44:16 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_image_pixel(t_minimap_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

static int	get_mmap_offset(t_minimap *minimap, int mapsize, int pos)
{
	if (pos > minimap->view_dist && (mapsize - pos) > (minimap->view_dist + 1))
		return (pos - minimap->view_dist);
	if (pos > minimap->view_dist && (mapsize - pos) <= (minimap->view_dist + 1))
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
	while (x < m->size && x < d->map->width)
	{
		if (!is_valid_map_coord(y + m->offset_y, d->map->height)
			|| !is_valid_map_coord(x + m->offset_x, d->map->width))
			line[x] = '\0';
		else if ((int)d->game->player->posX == (x + m->offset_x)
			&& (int)d->game->player->posY == (y + m->offset_y))
			line[x] = 'P';
		else if (d->map->map[y + m->offset_y][x + m->offset_x] == '1'
			|| d->map->map[y + m->offset_y][x + m->offset_x] == ' ')
			line[x] = '1';
		else if (d->map->map[y + m->offset_y][x + m->offset_x] == '0')
			line[x] = '0';
		else
			line[x] = '0';
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
	while (y < minimap->size && y < data->map->height)
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
	while (i < (minimap->tile_size - 1))
	{
		j = 0;
		while (j < (minimap->tile_size - 1))
		{
			set_image_pixel(minimap->img, x + j, i + y, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_tile(t_minimap *minimap, int x, int y)
{
	if (minimap->map[y][x] == 'P')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, MINIMAP_PLAYER);
	else if (minimap->map[y][x] == '1')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, MINIMAP_WALL);
	else if (minimap->map[y][x] == '0')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, MINIMAP_FLOOR);
	else if (minimap->map[y][x] == ' ')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, MINIMAP_SPACE);
}

static void	set_minimap_border_image_pixels(t_minimap *minimap, int color)
{
	int	size;
	int	x;
	int	y;

	size = MINIMAP_PIXEL_SIZE + minimap->tile_size;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x <= size)
		{
			if (x < 5 || x > (size - 5) || y < 5 || y > (size - 5))
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
	set_minimap_border_image_pixels(minimap, MINIMAP_SPACE);
}

static void	init_img_clean(t_minimap_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

static void	ini_img(t_data *data, t_minimap_img *image, int width, int height)
{
	init_img_clean(image);
	image->img = mlx_new_image(data->game->screen->holder, width, height);
	if (image->img == NULL)
		return ;
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return ;
}

static void	render_minimap_image(t_data *data, t_minimap *minimap)
{
	int	img_size;

	img_size = MINIMAP_PIXEL_SIZE + minimap->tile_size;
	ini_img(data, &data->minimap, img_size, img_size);
	draw_minimap(minimap);
	mlx_put_image_to_window(data->game->screen->holder, data->game->screen->window->holder, data->minimap.img,
		minimap->tile_size, screenHeight
		- (MINIMAP_PIXEL_SIZE + (minimap->tile_size * 2)));
	mlx_destroy_image(data->game->screen->holder, data->minimap.img);
}

void	display_minimap(t_data *data)
{
	t_minimap	minimap;

	minimap.map = NULL;
	minimap.img = &data->minimap;
	minimap.view_dist = MINIMAP_VIEW_DIST;
	minimap.size = (2 * minimap.view_dist) + 1;
	minimap.tile_size = MINIMAP_PIXEL_SIZE / (2 * minimap.view_dist);
	minimap.offset_x = get_mmap_offset(&minimap,
			data->map->width, (int)data->game->player->posX);
	minimap.offset_y = get_mmap_offset(&minimap,
			data->map->height, (int)data->game->player->posY);
	minimap.map = generate_minimap(data, &minimap);
	if (!minimap.map)
		exit_game(data);
	render_minimap_image(data, &minimap);
	free_tab((void **)minimap.map);
}
