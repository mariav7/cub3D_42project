/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:37:35 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/09 11:24:27 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_texture_imgs(t_screen *mlx, t_list *list)
{
	t_list_elem		*start;	
	t_list_elem		*tmp;
	t_texture		*elem;

	start = list->head;
	while (list->head)
	{
		elem = (t_texture *)list->head->content;
		tmp = list->head->next;
		mlx_destroy_image(mlx->holder, elem->image->holder);
		list->head = tmp;
	}
	list->head = start;
}

int	exit_game(t_data *d)
{
	t_game *game;

	game = d->game;
	destroy_texture_imgs(game->screen, game->textures);
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
	list_delete(game->textures);
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
	if (BONUS)
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
