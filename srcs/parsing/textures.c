/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:14:54 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/28 11:45:29 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	file_exists(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static char	*get_texture_path(char *line, int *j)
{
	int		i;
	char	*path;

	*j = *j + 2;
	while (line[*j] && (line[*j] == ' ' || line[*j] == '\t'))
		(*j)++;
	i = *j;
	while (line[i] && (line[i] != ' ' && line[i] != '\t'))
		i++;
	path = malloc(sizeof(char) * (i - *j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[*j] && (line[*j] != ' ' && line[*j] != '\t'
			&& line[*j] != '\n'))
		path[i++] = line[(*j)++];
	path[i] = '\0';
	while (line[*j] && (line[*j] == ' ' || line[*j] == '\t'))
		(*j)++;
	if (line[*j] && line[*j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

int	fill_textures(t_tex *tex, char *line, int *i)
{
	if (tex->no && tex->so && tex->ea && tex->we)
		return (0);
	if (line[*i] == 'N' && line[*i + 1] == 'O' && !(tex->no))
		tex->no = get_texture_path(line, i);
	else if (line[*i] == 'S' && line[*i + 1] == 'O' && !(tex->so))
		tex->so = get_texture_path(line, i);
	else if (line[*i] == 'W' && line[*i + 1] == 'E' && !(tex->we))
		tex->we = get_texture_path(line, i);
	else if (line[*i] == 'E' && line[*i + 1] == 'A' && !(tex->ea))
		tex->ea = get_texture_path(line, i);
	else
		return (0);
	return (1);
}

int	check_textures(t_data **d, char **err_msg)
{
	if (!(*d)->tex->no || !(*d)->tex->so || !(*d)->tex->ea || !(*d)->tex->we)
		return (0);
	if (file_exists((*d)->tex->we) == 0 || file_exists((*d)->tex->ea) == 0
		|| file_exists((*d)->tex->so) == 0 || file_exists((*d)->tex->no) == 0)
	{
		*err_msg = ERR_TEX_NOTFOUND;
		return (-1);
	}
	if (is_file_dir((*d)->tex->we) || is_file_dir((*d)->tex->ea)
		|| is_file_dir((*d)->tex->so) || is_file_dir((*d)->tex->no))
	{
		*err_msg = ERR_TEX_ISDIR;
		return (0);
	}
	if (!file_ext((*d)->tex->we, TEX_TYPE)
		|| !file_ext((*d)->tex->ea, TEX_TYPE)
		|| !file_ext((*d)->tex->so, TEX_TYPE)
		|| !file_ext((*d)->tex->no, TEX_TYPE))
	{
		*err_msg = ERR_TEX_FILE;
		return (0);
	}
	return (1);
}
