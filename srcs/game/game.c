#include "cub3d.h"

int	exit_game(t_data *d)
{
	t_game *game;

	game = d->game;
	mlx_destroy_image(game->screen->holder, game->screen->img->holder);
	mlx_clear_window(game->screen->holder, game->screen->window->holder);
	mlx_destroy_window(game->screen->holder, game->screen->window->holder);
	mlx_destroy_display(game->screen->holder);
	free(game->screen->img);
	free(game->screen->utils);
	free(game->screen->window);
	free(game->screen->holder);
	free(game->screen);
	free(game->player);
	free(game);
	free_n_exit_safe(d);
	return 0;
}

void	refresh(t_data *d)
{
	t_game *game;
	t_image	*image;

	game = d->game;
	image = draw_map(d);
	mlx_clear_window(game->screen->holder, game->screen->window->holder);
	display_image(game->screen, image);
	display_minimap(d);
	mlx_destroy_image(game->screen->holder, game->screen->img->holder);
	free(game->screen->img);
	game->screen->img = image;
}

t_game *init_game(t_screen *screen, t_player *player)
{
	if (!screen || !player)
		return (NULL);
	t_game *game = calloc(sizeof(t_game), 1);
	if (!game)
		return (NULL);
	game->screen = screen;
	game->player = player;
	return (game);
}
