#include "cub3d.h"

void move(t_data *d);

int	key_event(int key_code, t_data *d)
{
	printf("works %d\n", key_code);
	(void) d;
	//will_hit(d);
	/*if (key_code == LOOK_LEFT)
		printf(GREEN"Looking left\n"DEFAULT);
	else if (key_code == LOOK_RIGHT)
		printf(BLUE"Looking right\n"DEFAULT);
	else if (key_code == MOVE_FORWARD)
		printf(CYAN"Moving forward\n"DEFAULT);
	else if (key_code == MOVE_BACKWARDS)
		printf(PURPLE"Moving backwards\n"DEFAULT);
	else if (key_code == MOVE_LEFT)
		printf(YELLOW"Moving left\n"DEFAULT);
	else if (key_code == MOVE_RIGHT)
		printf(GREY"Moving right\n"DEFAULT);
	else if (key_code == ESCAPE)
		free_n_exit_safe(d);*/
	//move(d);
	return (0);
}

/*void move(t_data *d) {
	// Calcular el ángulo del rayo
	float ray_angle = d->player->angle - (FOV * (M_PI / 180)) / 2 + (float)d->player->x / SCREEN_WIDTH * (FOV * (M_PI / 180));

	// Variables para detectar colisiones
	float distance_to_wall = 0;
	int hit_wall = 0;
	int wall_height = 0;
	int wall_texture = 0;

	// Calcular la dirección del rayo
	float ray_dir_x = cos(ray_angle);
	float ray_dir_y = sin(ray_angle);

	// Calcular la posición del jugador en el mapa
	int map_x = (int)d->player->x;
	int map_y = (int)d->player->y;

	// Calcular la longitud del rayo hasta la pared
	float step_x = 0;
	float step_y = 0;
	float delta_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
	float delta_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
	float x_pos = d->player->x;
	float y_pos = d->player->y;

	if (ray_dir_x < 0)
	{
		step_x = -1;
		distance_to_wall = (d->player->x - map_x) * delta_x;
	}
	else if (ray_dir_x > 0)
	{
		step_x = 1;
		distance_to_wall = (map_x + 1.0 - d->player->x) * delta_x;
	}

	if (ray_dir_y < 0)
	{
		step_y = -1;
		distance_to_wall = (d->player->y - map_y) * delta_y;
	}
	else if (ray_dir_y > 0)
	{
		step_y = 1;
		distance_to_wall = (map_y + 1.0 - d->player->y) * delta_y;
	}

	// Bucle para detectar colisiones con las paredes del mapa
	while (!hit_wall)
	{
		// Avanzar un paso en la dirección del rayo
		if (distance_to_wall < 1.0)
		{
			// Se ha detectado una colisión con la pared
			hit_wall = 1;
			wall_height = SCREEN_HEIGHT / distance_to_wall;
			if (wall_height > SCREEN_HEIGHT)
			{
				wall_height = SCREEN_HEIGHT;
			}
			wall_texture = d->map[map_y][map_x];
		}
		else
		{
			// Avanzar un paso
			x_pos += step_x / delta_x;
			y_pos += step_y / delta_y;
			map_x = (int)x_pos;
			map_y = (int)y_pos;
			if (map_x < 0 || map_x >= 10 || map_y < 0 || map_y >= 10)
			{
				// Se ha salido del mapa, abortar
				break;
			}
			if (d->map[map_y][map_x] != 0)
			{
				// Se ha detectado una colisión con la pared
				hit_wall = 1;
				wall_height = SCREEN_HEIGHT / distance_to_wall;
				if (wall_height > SCREEN_HEIGHT)
				{
					wall_height = SCREEN_HEIGHT;
				}
				wall_texture = d->map[map_y][map_x];
			}
			else
			{
				distance_to_wall += (step_x * step_x + step_y * step_y);
			}
		}
	}
}*/

