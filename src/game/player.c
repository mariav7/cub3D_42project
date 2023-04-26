#include "../../includes/cub3d.h"


t_player *init_player(double planeX, double planeY, double posX, double posY)
{
	t_player *player = calloc(sizeof(t_player), 1);
	if (!player)
		return (NULL);
	player->planeX = planeX;
	player->planeY = planeY;
	player->posX = posX;
	player->posY = posY;
	player->move_speed = 0.5;
	player->rot_speed = 0.3;
	player->dirX = -1;
	player->dirY = 0;
	return (player);
}
