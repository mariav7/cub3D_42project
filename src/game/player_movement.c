#include "../../includes/cub3d.h"

void	go_straight(t_game *game);
void	go_back(t_game *game);

int	handle_move(int key_code, t_game *game)
{
	if(key_code == 119)
		go_straight(game);
	else if(key_code == 115)
		go_back(game);
	else if(key_code == 100)
		rotate(game, 1);
	else if(key_code == 97)
		rotate(game, 0);
	else if(key_code == 65307)
		exit_game(game);
	else
		return 1;
	refresh(game);
	return 0;
}

void	go_straight(t_game *game)
{
	if(game->map->map[(int) (game->player->posX + game->player->dirX * game->player->move_speed)][(int) game->player->posY] == 0)
		game->player->posX += game->player->dirX * game->player->move_speed;
	if(game->map->map[(int) game->player->posX][(int) (game->player->posY + game->player->dirY * game->player->move_speed)] == 0)
		game->player->posY += game->player->dirY * game->player->move_speed;
}

void	go_back(t_game *game)
{
	if(game->map->map[(int) (game->player->posX - game->player->dirX * game->player->move_speed)][(int) game->player->posY] == 0)
	game->player->posX -= game->player->dirX * game->player->move_speed;
	if(game->map->map[(int) game->player->posX][(int) (game->player->posY - game->player->dirY * game->player->move_speed)] == 0)
	game->player->posY -= game->player->dirY * game->player->move_speed;
}
