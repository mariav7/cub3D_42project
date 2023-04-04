/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:03:10 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/04 15:16:48 by mflores-         ###   ########.fr       */
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

void	check_file(char *file)
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

void	init_structs(t_data **d, t_map **m)
{
	*d = ft_calloc(sizeof(t_data), 1);
	if (*d == NULL)
		basic_error_message(ERR_CALLOC, NULL);
	*m = ft_calloc(sizeof(t_map), 1);
	if (*m == NULL)
		basic_error_message(ERR_CALLOC, *d);
	(*d)->map = *m;
}

void	init_game(t_data *d)
{
	d->window = mlx_new_window(d->mlx_ptr, WIN1_SX, WIN1_SY, TITLE);
	if (d->window == NULL)
		error_exit(d, ERR_MLX_WIN, NULL);
}
