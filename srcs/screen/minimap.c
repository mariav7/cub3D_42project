/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:10:35 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/09 11:47:37 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	set_image_pixel(t_minimap_img *image, int x, int y, int color)
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
		else if ((int)d->game->player->pos_x == (x + m->offset_x)
			&& (int)d->game->player->pos_y == (y + m->offset_y))
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
		minimap->tile_size, SCREEN_HEIGHT
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
			data->map->width, (int)data->game->player->pos_x);
	minimap.offset_y = get_mmap_offset(&minimap,
			data->map->height, (int)data->game->player->pos_y);
	minimap.map = generate_minimap(data, &minimap);
	if (!minimap.map)
		exit_game(data);
	render_minimap_image(data, &minimap);
	free_tab((void **)minimap.map);
} */

static void	set_image_pixel(t_minimap_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

static void	set_minimap_tile_pixels(t_minimap *minimap, int x, int y, int color)
{
	int     i;
	int     j;

	// Draw each pixel of the current tile
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

/* static void draw_line(t_minimap_img *image, int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx, sy;

    if (x1 < x2) {
        sx = 1;
    } else {
        sx = -1;
    }

    if (y1 < y2) {
        sy = 1;
    } else {
        sy = -1;
    }

    int err = dx - dy;
    int x = x1;
    int y = y1;

    while (1) {
			set_image_pixel(image, x, y, color);

			if (x == x2 && y == y2) {
					break;
			}

			int e2 = 2 * err;
			if (e2 > -dy) {
					err -= dy;
					x += sx;
			}
			if (e2 < dx) {
					err += dx;
					y += sy;
			}
    }
} */

/* static void	draw_player(t_minimap *minimap, int x, int y, int color)
{
	int			r;
	int     i;
	int     j;

	r = 5;
  for (i = x - r; i <= x + r; i++)
  {
    for (j = y - r; j <= y + r; j++)
    {
      if ((i-x)*(i-x) + (j-y)*(j-y) <= r*r)
      {
				set_image_pixel(minimap->img, i, j, color);
      }
    }
  }
} */

static void	draw_player(t_minimap *minimap, int x, int y, int color)
{
	int			r;
	int     i;
	int     j;

	r = 3;
	for (i = x - r; i <= x + r; i++)
	{
		for (j = y - r; j <= y + r; j++)
		{
			if ((i-x)*(i-x) + (j-y)*(j-y) <= r*r)
			{
				set_image_pixel(minimap->img, j, i, color);
			}
		}
	}
}

static void	draw_minimap(t_data *d, t_minimap *minimap)
{
	unsigned int color;
	int	player_x;
	int	player_y;

	// Draw the map
	for (int y = 0; y < d->map->height; y++)
	{
		for (int x = 0; x < d->map->width; x++)
		{
			// Calculate the pixel coordinates
			int py = y * minimap->tile_size;
			int px = x * minimap->tile_size;

			// Get the tile color
			if (d->map->map[y][x] == ' ' || d->map->map[y][x] == '1')
				color = MINIMAP_WALL;
			else
				color = MINIMAP_FLOOR;
			// Draw the pixel
			set_minimap_tile_pixels(minimap, px, py, color);
		}
	}

	// Draw the player
	player_x = (int)d->game->player->pos_x * minimap->tile_size;
	player_y = (int)d->game->player->pos_y * minimap->tile_size;

	// Draw the player's field of view
/* 	for (int i = -FOV / 2; i < FOV / 2; i++) {
		float angle = d->player->dir + i * FOV_ANGLE / screenWidth;
		int dir_x = cos(angle) * minimap->tile_size * 10;
		int dir_y = sin(angle) * minimap->tile_size * 10;
		draw_line(minimap, player_x, player_y, player_x + dir_x, player_y + dir_y, MINIMAP_FOV);
	} */

	// Draw the player on top of the lines
	draw_player(minimap, player_x, player_y, MINIMAP_PLAYER);
	// set_minimap_tile_pixels(minimap, player_x, player_y, MINIMAP_PLAYER);
}

void	display_minimap(t_data *data)
{
	// Create a window
	t_minimap	minimap;

	minimap.img = &data->minimap;
	minimap.tile_size = 15;
	minimap.width = data->map->width * minimap.tile_size;
	minimap.height = data->map->height * minimap.tile_size;
	printf("player_pos_x:%f\nplayer_pos_y:%f\nminimap_height:%d\nminimap_width:%d\nminimap_tileSize:%d\n", data->game->player->pos_x, data->game->player->pos_y, minimap.height, minimap.width, minimap.tile_size);
	// Create a new image
	minimap.img->img = mlx_new_image(data->game->screen->holder, minimap.width, minimap.height);
	if (minimap.img->img == NULL)
		return ;
	// Get a pointer to the image data
	minimap.img->addr = (unsigned int *)mlx_get_data_addr(minimap.img->img, &minimap.img->pixel_bits,
			&minimap.img->size_line, &minimap.img->endian);
	draw_minimap(data, &minimap);
	// Draw the image on the window
	mlx_put_image_to_window(data->game->screen->holder, data->game->screen->window->holder, data->minimap.img,
		0, SCREEN_HEIGHT / 2);
	mlx_destroy_image(data->game->screen->holder, data->minimap.img);
}


	// Draw the player
	// player_x = d->game->player->pos_x * minimap->tile_size;
	// player_y = d->game->player->pos_y * minimap->tile_size;
	// int player_dir_x = cos(d->game->player->dirX) * minimap->tile_size * 2;
	// int player_dir_y = sin(d->game->player->dirY) * minimap->tile_size * 2;
	// set_minimap_tile_pixels(minimap, player_x, player_y, MINIMAP_PLAYER);

/* 	// Draw the player's field of view
	for (int i = -FOV / 2; i < FOV / 2; i++) {
		float angle = d->player->dir + i * FOV_ANGLE / screenWidth;
		int dir_x = cos(angle) * minimap->tile_size * 10;
		int dir_y = sin(angle) * minimap->tile_size * 10;
		draw_line(minimap, player_x, player_y, player_x + dir_x, player_y + dir_y, MINIMAP_FOV);
	} */


/* 		// Calculate the player's field of view angle
	double fov_angle = 60 * (3.14 / 180.0);

	// Calculate the distance from the player to the center of the tile
	double center_distance = minimap->tile_size / 2;

	// Draw the lines of the player's field of view
	for (int i = 0; i < fov_angle; i++) {
		// Calculate the endpoint of the line
		int line_x = player_x + (center_distance * cos(fov_angle));
		int line_y = player_y + (center_distance * sin(fov_angle));

		// Draw the line
		draw_line(minimap->img, player_x, player_y, line_x, line_y, MINIMAP_PLAYER);

		// Increment the field of view angle
		fov_angle += fov_angle / (double)minimap->width;
	} */