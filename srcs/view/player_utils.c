#include "cub3d.h"

/*void	will_hit(t_data *d)
{
	t_player 	*p;

	p = d->player;
	float ray_angle = p->angle - (FOV * (M_PI / 180)) / 2 + (float)p->x / SCREEN_WIDTH * (FOV * (M_PI / 180));

	float ray_dir_x = cos(ray_angle);
	float ray_dir_y = sin(ray_angle);

	float x_pos = p->x;
	float y_pos = p->y;
	float delta_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
	float delta_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
	float step_x = 0;
	float step_y = 0;
	float distance_to_wall = 0;
	int map_x = (int)p->x;
	int map_y = (int)p->y;
	int wall_height = 0;
	int wall_texture = 0;
	int hit_wall = 0;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		distance_to_wall = (p->x - map_x) * delta_x;
	}
	else if (ray_dir_x > 0)
	{
		step_x = 1;
		distance_to_wall = (map_x + 1.0 - p->x) * delta_x;
	}

	if (ray_dir_y < 0)
	{
		step_y = -1;
		distance_to_wall = (p->y - map_y) * delta_y;
	}
	else if (ray_dir_y > 0)
	{
		step_y = 1;
		distance_to_wall = (map_y + 1.0 - p->y) * delta_y;
	}
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
			//break;
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
}*/
