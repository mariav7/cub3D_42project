/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:56:18 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/04 15:40:33 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_event(int key_code, t_data *d)
{
	if (key_code == LOOK_LEFT)
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
		free_n_exit_safe(d);
	return (0);
}

static int	close_window(t_data *d)
{
	free_n_exit_safe(d);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*mlx;
	t_map	*fmap;

	if (ac != 2)
		basic_error_message(ERR_USAGE, NULL);
	check_file(av[1]);
	init_structs(&mlx, &fmap);
	printf(PURPLE"<======\tTesting Program\t=====>\n"DEFAULT);
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		error_exit(mlx, ERR_MLX, NULL);
	printf(WHITE" => Connection to Minilibx...\n"DEFAULT);
	init_game(mlx);
	printf(WHITE" => Window1 %dx%d "TITLE"\n"DEFAULT, WIN1_SX, WIN1_SY);
	mlx_hook(mlx->window, 2, 1L << 0, key_event, mlx);
	mlx_hook(mlx->window, 17, 1L << 17, close_window, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
