#include "cub3d.h"

void	go_straight(t_data *d);
void	go_back(t_data *d);

int	handle_move(int key_code, t_data *d)
{
	t_game	*game;

	game = d->game;
	if(key_code == 119)
		go_straight(d);
	else if(key_code == 115)
		go_back(d);
	else if(key_code == 100)
		rotate(game, 1);
	else if(key_code == 97)
		rotate(game, 0);
	else if(key_code == 65307)
		exit_game(d);
	else
		return 1;
	refresh(d);
	return 0;
}

void	go_straight(t_data *data)
{
	t_map	*map;
	t_game	*game;

	map = data->map;
	game = data->game;
	if(ft_strchr("0NESW", map->map[(int) (game->player->posX + game->player->dirX * game->player->move_speed)][(int) game->player->posY]) != 0)
		game->player->posX += game->player->dirX * game->player->move_speed;
	if(ft_strchr("0NESW", map->map[(int) game->player->posX][(int) (game->player->posY + game->player->dirY * game->player->move_speed)]) != 0)
		game->player->posY += game->player->dirY * game->player->move_speed;
}

void	go_back(t_data *data)
{
	t_map	*map;
	t_game	*game;

	map = data->map;
	game = data->game;
	if(ft_strchr("0NESW", map->map[(int) (game->player->posX - game->player->dirX * game->player->move_speed)][(int) game->player->posY]) != 0)
		game->player->posX -= game->player->dirX * game->player->move_speed;
	if(ft_strchr("0NESW", map->map[(int) game->player->posX][(int) (game->player->posY - game->player->dirY * game->player->move_speed)]) != 0)
		game->player->posY -= game->player->dirY * game->player->move_speed;
}
