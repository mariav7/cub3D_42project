/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:25 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/11 19:20:40 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw(t_data *d);
void initial_draw(t_data *d);
void calculate(t_data *d);

void	init_structs(t_data **d, int fd, char *file)
{
	t_map	*m;
	t_tex	*t;
	t_view	*v;
	t_player	*p;

	*d = ft_calloc(sizeof(t_data), 1);
	if (*d == NULL)
		basic_error_message(ERR_CALLOC, NULL, fd);
	m = ft_calloc(sizeof(t_map), 1);
	if (m == NULL)
		basic_error_message(ERR_CALLOC, *d, fd);
	t = ft_calloc(sizeof(t_tex), 1);
	if (t == NULL)
		basic_error_message(ERR_CALLOC, *d, fd);
	v = ft_calloc(sizeof(t_view), 1);
	if (v == NULL)
		basic_error_message(ERR_CALLOC, v, fd);
	p = ft_calloc(sizeof(t_player), 1);
	if(p == NULL)
		basic_error_message(ERR_CALLOC, p, fd);
	(*d)->map_after = m;
	(*d)->tex = t;
	(*d)->view = v;
	(*d)->player = p;
	m->fd = fd;
	m->path = file;
	//parse_file(d);
}

void	start_game(t_data *d)
{
	view_init(d);
	view_hooks(d);
	initial_draw(d);
	calculate(d);
	draw(d);
	mlx_loop(d->view->mlx_ptr);
}

void	my_mlx_pixel_put(t_data *d, int x, int y, int color)
{
	char	*dst;

	dst = d->view->addr + (y * d->view->line_length + x * (d->view->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	initial_draw(t_data *d)
{

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		d->view->buffer[i] = (int *)mlx_get_data_addr(d->view->img_ptr, &d->view->bits_per_pixel, &d->view->line_length, &d->view->endian);
	}

	// Inicializar la textura de ladrillos
	for (int y = 0; y < TILE_SIZE_TEXTURE; y++)
	{
		for (int x = 0; x < TILE_SIZE_TEXTURE; x++)
		{
			int color = (x % 32 == 0 || y % 32 == 0) ? 0xFF0000 : 0xFFFFFF;
			d->view->textures[0][TILE_SIZE_TEXTURE * y + x] = color;
		}
	}

	// Inicializar la textura de hierba
	for (int y = 0; y < TILE_SIZE_TEXTURE; y++)
	{
		for (int x = 0; x < TILE_SIZE_TEXTURE; x++)
		{
			int color = (x % 16 == 0 && y % 16 == 0) ? 0x00FF00 : 0xFFFFFF;
			d->view->textures[1][TILE_SIZE_TEXTURE * y + x] = color;
		}
	}

	//Inicializar el mapa
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			d->map[y][x] = (y == 0 || y == 9 || x == 0 || x == 9) ? 1 : 0;
		}
	}
	d->player->floats[ANGLE] = 0;
	d->player->floats[X] = 1.5;
	d->player->floats[Y] = 1.5;
}

void calculate(t_data *d) {
	float ray_angle = d->player->floats[ANGLE] - (FOV * (M_PI / 180)) / 2 + (float)d->player->floats[X] / SCREEN_WIDTH * (FOV * (M_PI / 180));

	// Variables para detectar colisiones
	d->player->floats[DISTANCE_TO_WALL] = 0;
	d->player->ints[HIT_WALL] = 0;
	d->player->ints[WALL_HEIGHT] = 0;
	d->player->ints[WALL_TEXTURE] = 0;

	// Calcular la dirección del rayo
	d->player->floats[RAY_DIR_X] = cos(ray_angle);
	d->player->floats[RAY_DIR_Y] = sin(ray_angle);

	// Calcular la posición del jugador en el mapa
	d->player->ints[MAP_X] = (int)d->player->floats[X];
	d->player->ints[MAP_Y] = (int)d->player->floats[Y];

	// Calcular la longitud del rayo hasta la pared
	d->player->floats[STEP_X] = 0;
	d->player->floats[STEP_Y] = 0;
	d->player->floats[DELTA_X] = sqrt(1 + (d->player->floats[RAY_DIR_Y] * d->player->floats[RAY_DIR_Y]) / (d->player->floats[RAY_DIR_X] * d->player->floats[RAY_DIR_X]));
	d->player->floats[DELTA_Y] = sqrt(1 + (d->player->floats[RAY_DIR_X] * d->player->floats[RAY_DIR_X]) / (d->player->floats[RAY_DIR_Y] * d->player->floats[RAY_DIR_Y]));
	d->player->floats[X_POS] = d->player->floats[X];
	d->player->floats[Y_POS] = d->player->floats[Y];

	if (d->player->floats[RAY_DIR_X] < 0)
	{
		d->player->floats[STEP_X] = -1;
		d->player->floats[DISTANCE_TO_WALL] = (d->player->floats[X] - d->player->floats[MAP_X]) * d->player->floats[DELTA_X];
	}
	else if (d->player->floats[RAY_DIR_X] > 0)
	{
		d->player->floats[STEP_X] = 1;
		d->player->floats[DISTANCE_TO_WALL] = (d->player->ints[MAP_X] + 1.0 - d->player->floats[X]) * d->player->floats[DELTA_X];
	}

	if (d->player->floats[RAY_DIR_Y] < 0)
	{
		d->player->floats[STEP_Y] = -1;
		d->player->floats[DISTANCE_TO_WALL] = (d->player->floats[Y] - d->player->ints[MAP_Y]) * d->player->floats[DELTA_Y];
	}
	else if (d->player->floats[RAY_DIR_Y] > 0)
	{
		d->player->floats[STEP_Y] = 1;
		d->player->floats[DISTANCE_TO_WALL] = (d->player->ints[MAP_Y] + 1.0 - d->player->floats[Y]) * d->player->floats[DELTA_Y];
	}

	// Bucle para detectar colisiones con las paredes del mapa
	// Avanzar un paso en la dirección del rayo
	if (d->player->floats[DISTANCE_TO_WALL] < 1.0)
	{
		// Se ha detectado una colisión con la pared
		d->player->ints[HIT_WALL] = 1;
		d->player->ints[WALL_HEIGHT] = SCREEN_HEIGHT / d->player->floats[DISTANCE_TO_WALL];
		if (d->player->ints[WALL_HEIGHT] > SCREEN_HEIGHT)
		{
			d->player->ints[WALL_HEIGHT] = SCREEN_HEIGHT;
		}
		d->player->ints[WALL_TEXTURE] = d->map[d->player->ints[MAP_Y]][d->player->ints[MAP_X]];
	}
	else
	{
		// Avanzar un paso
		d->player->floats[X_POS] += d->player->floats[STEP_X] / d->player->floats[DELTA_X];
		d->player->floats[Y_POS] += d->player->floats[STEP_Y] / d->player->floats[DELTA_Y];
		d->player->ints[MAP_X] = (int)d->player->floats[X_POS];
		d->player->ints[MAP_Y] = (int)d->player->floats[Y_POS];
		if (d->player->ints[MAP_X] < 0 || d->player->ints[MAP_X] >= 10 || d->player->ints[MAP_Y] < 0 || d->player->ints[MAP_Y] >= 10)
		{
			// Se ha salido del mapa, abortar

		} else if (d->map[d->player->ints[MAP_Y]][d->player->ints[MAP_X]] != 0)
		{
			// Se ha detectado una colisión con la pared
			d->player->ints[HIT_WALL] = 1;
			d->player->ints[WALL_HEIGHT] = SCREEN_HEIGHT / d->player->floats[DISTANCE_TO_WALL];
			if (d->player->ints[WALL_HEIGHT] > SCREEN_HEIGHT)
			{
				d->player->ints[WALL_HEIGHT] = SCREEN_HEIGHT;
			}
			d->player->ints[WALL_TEXTURE] = d->map[d->player->ints[MAP_Y]][d->player->ints[MAP_X]];
		}
		else
		{
			d->player->floats[DISTANCE_TO_WALL] += (d->player->floats[STEP_X] * d->player->floats[STEP_X] + d->player->floats[STEP_Y] * d->player->floats[STEP_Y]);
		}
	}
}

void draw(t_data *d) {



	// Dibujar las paredes
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		int map_x = (int)d->player->floats[X];
		int map_y = (int)d->player->floats[Y];
	 // Dibujar el techo y el suelo
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{

			if (y < SCREEN_HEIGHT / 2)
			{
				// Dibujar el techo
				int color = 0xCCCCCC;
				my_mlx_pixel_put(d, x, y, color);
			}
			else
			{
				// Dibujar el suelo
				int color = 0x777777;
				my_mlx_pixel_put(d, x, y, color);
			}
		}

		// Dibujar la pared
		int texture_x = (int)(d->map[map_y][map_x] - 1) * TILE_SIZE_TEXTURE;
		for (int y = SCREEN_HEIGHT / 2 - d->player->ints[WALL_HEIGHT] / 2; y < SCREEN_HEIGHT / 2 + d->player->ints[WALL_HEIGHT] / 2; y++)
		{
			int texture_y = (y - (SCREEN_HEIGHT / 2 - d->player->ints[WALL_HEIGHT] / 2)) * TILE_SIZE_TEXTURE / d->player->ints[WALL_HEIGHT];
			int color = d->view->textures[d->player->ints[WALL_TEXTURE]][TILE_SIZE_TEXTURE * texture_y + texture_x];
			my_mlx_pixel_put(d, x, y, color);
			printf("pared %d %d\n", x, y);
		}
	}
	mlx_put_image_to_window(d->view->mlx_ptr, d->view->win_ptr, d->view->img_ptr, 0, 0);
}
