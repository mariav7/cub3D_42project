#include "../../includes/cub3d.h"


t_player *init_player(t_data *d)
{
	t_player *player = calloc(sizeof(t_player), 1);
	if (!player)
		return (NULL);
	player->planeX =  0;
	player->planeY = 0.66;
	player->posX = d->map->pos_x + 0.5;
	player->posY = d->map->pos_y + 0.5;
	player->move_speed = 1;
	player->rot_speed = 0.10;
	player->dirX = -1;
	player->dirY = 0;
	return (player);
}
