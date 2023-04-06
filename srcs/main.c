/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:56:18 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/06 14:42:00 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_event(int key_code, t_data *d)
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

int	close_window(t_data *d)
{
	free_n_exit_safe(d);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*mlx;
	t_map	*map;
	int		fd;

	fd = check_file(ac, av);
	if (fd != -1)
	{
		init_structs(&mlx, &map, fd);
		printf(PURPLE"<======\tTesting Program\t=====>\n"DEFAULT);
		printf(WHITE" => Connection to Minilibx...\n"DEFAULT);
		printf(WHITE" => Window %dx%d "TITLE"\n"DEFAULT, WIN1_SX, WIN1_SY);
		start_game(mlx);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
