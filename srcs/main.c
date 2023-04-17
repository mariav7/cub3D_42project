/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:56:18 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/14 12:14:04 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *d)
{
	free_n_exit_safe(d);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*d;
	int		fd;

	fd = check_file(ac, av);
	if (fd != -1)
	{
		init_structs(&d, fd, av[1]);
		debug(d);
		start_game(d);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
