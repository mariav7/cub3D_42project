/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:20:06 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/24 16:00:05 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	file_exists(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (fd);
	return (fd);
}

int	file_ext(char *file, char *file_ext)
{
	if (ft_strlen(file) < 5 || ft_strncmp(&file
			[ft_strlen(file) - ft_strlen(file_ext)], file_ext, \
			ft_strlen(file_ext)) != 0)
		return (0);
	return (1);
}

int	is_file_dir(char *file)
{
	int		fd;

	fd = open(file, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		return (1);
	}
	return (0);
}

int	check_file(int ac, char **av)
{
	int	fd;

	fd = -1;
	if (ac != 2)
		return (basic_error_message(ERR_USAGE, NULL, -1), -1);
	if (is_file_dir(av[1]))
		return (basic_error_message(ERR_FILE_ISDIR, NULL, -1), -1);
	if (file_ext(av[1], FILE_TYPE) == 0)
		return (basic_error_message(ERR_FILE, NULL, -1), -1);
	fd = file_exists(av[1]);
	if (fd < 0)
		return (ft_putendl_fd(ERR_MSG, 2), perror(ERR_FILE_NOTFOUND), -1);
	return (fd);
}
