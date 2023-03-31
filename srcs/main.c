/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:56:18 by mflores-          #+#    #+#             */
/*   Updated: 2023/03/31 15:11:18 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	void	*mlx;
	void	*win1;
	
	if (ac == 1)
	{
		(void)av;
		coucou();
		printf("MinilibX Test Program\n");
		printf(" => Connection ...");
		if (!(mlx = mlx_init()))
		{
		printf("KO!\n");
		exit(1);
		}
		printf(" => Window1 %dx%d \"Title 1\" ...",WIN1_SX,WIN1_SY);
		if (!(win1 = mlx_new_window(mlx,WIN1_SX,WIN1_SY,"Title1")))
			{
			printf(" !! KO !!\n");
			exit(1);
			}
		printf("OK\n");
	}
	return (0);
}
