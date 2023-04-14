/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:20:06 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/13 18:57:19 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	file_is_dir(char *arg)
{
	int		fd;
	int		ret;

	ret = 0;
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = 1;
	}
	return (ret);
}

static int	check_filename(char *file)
{
	if (ft_strlen(file) < 5 || ft_strncmp(&file
			[ft_strlen(file) - 4], FILE_TYPE, 4) != 0)
		return (0);
	return (1);
}

static int	file_exists(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (fd);
	return (fd);
}

int	check_file(int ac, char **av)
{
	int	fd;

	fd = -1;
	if (ac != 2)
		return (basic_error_message(ERR_USAGE, NULL, -1), -1);
	if (file_is_dir(av[1]))
		return (basic_error_message(ERR_ISDIR, NULL, -1), -1);		
	if (check_filename(av[1]) == 0)
		return (basic_error_message(ERR_FILE, NULL, -1), -1);
	fd = file_exists(av[1]);
	if (fd < 0)
		return (ft_putendl_fd(ERR_MSG, 2), perror(ERR_FILE_NOTFOUND), -1);
	return (fd);
}
