#include "cub3d.h"

void	go_straight(t_data *d);
void	go_back(t_data *d);

int	handle_move(int key_code, t_data *d)
{
	t_game	*game;

	game = d->game;
	printf("keycode %d\n", key_code);
	if(key_code == 119)
		go_straight(d);
	else if(key_code == 115)
		go_back(d);
	else if(key_code == 100)
		rotate(game, 0);
	else if(key_code == 97)
		rotate(game, 1);
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
	if(ft_strchr("NSWE0", map->map[(int) game->player->posY][(int) (game->player->posX + game->player->dirX * game->player->move_speed)]))
		game->player->posX += game->player->dirX * game->player->move_speed;
	if(ft_strchr("NSWE0", map->map[(int) (game->player->posY + game->player->dirY * game->player->move_speed)][(int) game->player->posX]))
		game->player->posY += game->player->dirY * game->player->move_speed;
	printf("new posX %f new posY %f\n", game->player->posX, game->player->posY);
}

void	go_back(t_data *data)
{
	t_map	*map;
	t_game	*game;

	map = data->map;
	game = data->game;
	if(ft_strchr("NSWE0", map->map[(int) game->player->posY][(int) (game->player->posX - game->player->dirX * game->player->move_speed)]))
		game->player->posX -= game->player->dirX * game->player->move_speed;
	if(ft_strchr("NSWE0", map->map[(int) (game->player->posY - game->player->dirY * game->player->move_speed)][(int) game->player->posX]))
		game->player->posY -= game->player->dirY * game->player->move_speed;
}
