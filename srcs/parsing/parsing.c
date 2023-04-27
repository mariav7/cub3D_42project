/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:03:10 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/27 12:39:03 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(char *path)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (i);
	else
	{
		line = get_next_line(fd);
		while (line)
		{
			i++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (i);
}

static char	**get_file(int nb_line, int fd)
{
	char	**tab;
	char	*line;
	int		i;

	tab = NULL;
	tab = malloc(sizeof(char *) * (nb_line + 1));
	if (!tab)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		tab[i] = ft_strdup(line);
		free(line);
		if (!tab[i])
			return (NULL);
		i++;
		line = get_next_line(fd);
	}
	tab[i] = 0;
	return (tab);
}

static void	check_data(t_data **d)
{
	int		ret;
	char	*err_msg;

	err_msg = NULL;
	ret = check_textures(d, &err_msg);
	if (ret == 0)
		error_exit(*d, err_msg, NULL);
	else if (ret == -1)
	{
		ft_putendl_fd(ERR_MSG, 2);
		perror(err_msg);
		error_exit(*d, NULL, NULL);
	}
	ret = check_map((*d)->map, &err_msg);
	if (ret == 0)
		error_exit(*d, err_msg, NULL);
}

static void	texture_or_color(t_data **d, int *i, char *row)
{
	char	*err_msg;

	err_msg = ERR_ID_INVALID;
	if (row[*i + 1] && ft_isalpha(row[*i + 1])
		&& !ft_isdigit(row[*i + 1]))
	{
		if (fill_textures((*d)->tex, row, i) == 0)
			error_exit(*d, err_msg, NULL);
	}
	else if (row[*i + 1]
		&& ft_isspace(row[*i + 1])
		&& !ft_isdigit(row[*i + 1]))
	{
		if (fill_colors((*d)->tex, row, i, &err_msg) == 0)
			error_exit(*d, err_msg, NULL);
	}
	else
		error_exit(*d, ERR_TEXCO_FORMAT, NULL);
}

static int	parse_row(t_data **d, char *row)
{
	int		i;
	int		start;

	i = 0;
	while (row[i])
	{
		start = i;
		while (row[i] && (row[i] == ' ' || row[i] == '\t' || row[i] == '\v'
				|| row[i] == '\f' || row[i] == '\r'))
			i++;
		if (row[i] && ft_isalpha(row[i]))
			texture_or_color(d, &i, row);
		else if (row[i] && (row[i] == '1' || row[i] == '0'))
		{
			if (!(*d)->tex->no || !(*d)->tex->so || !(*d)->tex->ea
				|| !(*d)->tex->we || !(*d)->tex->ce || !(*d)->tex->flo)
				error_exit(*d, ERR_MAP_ISFIRST, NULL);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

void	parse_file(t_data **d)
{
	int		nb_line;
	int		map_lines;
	int		i;

	nb_line = count_lines((*d)->map->path);
	if (nb_line == 0)
		error_exit(*d, ERR_FILE_EMPTY, NULL);
	(*d)->map->file = get_file(nb_line, (*d)->map->fd);
	if (!(*d)->map->file)
		error_exit(*d, ERR_MALLOC, NULL);
	map_lines = 0;
	i = 0;
	while (i < nb_line && (*d)->map->file[i])
	{
		map_lines = parse_row(d, (*d)->map->file[i]);
		if (map_lines == 1)
			fill_map(&i, nb_line, d);
		i++;
	}
	if (!(*d)->tex->ce || !(*d)->tex->flo || !(*d)->map->map)
		error_exit(*d, ERR_FILE_INVALID, NULL);
	check_data(d);
}
