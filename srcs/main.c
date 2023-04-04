/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:56:18 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/04 12:28:45 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_extension(char *file, char *file_type)
{
	int	i;

	i = 0;
	while (file_type[i])
	{
		if (file_type[i] != file[i])
			return (0);
		i++;
	}
	if (file[i] == '\0')
		return (1);
	return (0);
}

static void	check_file(char *file)
{
	while (*file)
	{
		if (*file == '.')
		{
			if (find_extension(file, FILE_TYPE))
				return ;
		}
		file++;
	}
	basic_error_message(ERR_FILE, NULL);
}

int	main(int ac, char **av)
{
	void	*mlx;
	void	*win1;

	if (ac != 2)
		basic_error_message(ERR_USAGE, NULL);
	check_file(av[1]);
	printf("MinilibX Test Program\n");
	printf(" => Connection ...");
	mlx = mlx_init();
	//dfkdf;lg
	if (!mlx)
	{
		printf("KO!\n");
		exit(1);
	}
	printf(" => Window1 %dx%d "TITLE" ...", WIN1_SX, WIN1_SY);
	win1 = mlx_new_window(mlx, WIN1_SX, WIN1_SY, TITLE);
	if (!win1)
	{
		printf ("KO!\n");
		exit(1);
	}
	return (0);
}
