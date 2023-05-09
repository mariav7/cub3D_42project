#include "cub3d.h"

void	rotate_right(t_game *game);
void	rotate_left(t_game *game);

void	rotate(t_game *game, int right)
{
	if (right)
		rotate_right(game);
	else
		rotate_left(game);
}

void	rotate_right(t_game *game)
{
	double oldDirX = game->player->dirX;
	game->player->dirX = game->player->dirX * cos(-game->player->rot_speed) - game->player->dirY * sin(-game->player->rot_speed);
	game->player->dirY = oldDirX * sin(-game->player->rot_speed) + game->player->dirY * cos(-game->player->rot_speed);
	double oldPlaneX = game->player->planeX;
	game->player->planeX = game->player->planeX * cos(-game->player->rot_speed) - game->player->planeY * sin(-game->player->rot_speed);
	game->player->planeY = oldPlaneX * sin(-game->player->rot_speed) + game->player->planeY * cos(-game->player->rot_speed);
	printf("posX %f posY %f dirX %f dirY %f\n", game->player->posX, game->player->posY, game->player->dirX, game->player->dirY);
}

void	rotate_left(t_game *game)
{
	double oldDirX = game->player->dirX;
	game->player->dirX = game->player->dirX * cos(game->player->rot_speed) - game->player->dirY * sin(game->player->rot_speed);
	game->player->dirY = oldDirX * sin(game->player->rot_speed) + game->player->dirY * cos(game->player->rot_speed);
	double oldPlaneX = game->player->planeX;
	game->player->planeX = game->player->planeX * cos(game->player->rot_speed) - game->player->planeY * sin(game->player->rot_speed);
	game->player->planeY = oldPlaneX * sin(game->player->rot_speed) + game->player->planeY * cos(game->player->rot_speed);
	printf("planeX %f planeY %f dirX %f dirY %f\n", game->player->planeX, game->player->planeY, game->player->dirX, game->player->dirY);
}

