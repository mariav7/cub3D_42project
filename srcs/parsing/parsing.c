/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:03:10 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/14 20:32:23 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*string_join(char *s1, char *s2, char **err_msg)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	if (!new_str)
		*err_msg = ERR_MALLOC;
	return (new_str);
}

static char	*get_texture_path(char *line, int *j)
{
	int		len;
	int		i;
	char	*path;

	*j = *j + 2;
	while (line[*j] && (line[*j] == ' ' || line[*j] == '\t'))
		(*j)++;
	len = *j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	path = malloc(sizeof(char) * (len - *j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[*j] && (line[*j] != ' ' && line[*j] != '\t' && line[*j] != '\n'))
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

static int	fill_textures(t_tex *tex, char *line, int *i)
{
	if (tex->no && tex->so && tex->ea && tex->we)
		return (1);
	if (line[*i + 2] && !ft_isspace(line[*i + 2]))
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

static void	parse_buffer(t_data **d, char *line)
{
	int		i;

	i = 0;
	(*d)->map->file = ft_strtrim(line, " \t\n\v\f\r");
	if (!(*d)->map->file)
		error_exit(*d, ERR_MALLOC, line);
	while ((*d)->map->file[i])
	{
/* 		if ((*d)->tex->no && (*d)->tex->so && (*d)->tex->ea && (*d)->tex->we && \
		(*d)->tex->ce && (*d)->tex->flo)
			break; */
		while ((*d)->map->file[i] && ft_isspace((*d)->map->file[i]) && ft_isdigit((*d)->map->file[i]))
			i++;
		if ((*d)->map->file[i] && ft_isprint((*d)->map->file[i]) && !ft_isdigit((*d)->map->file[i]))
		{
			if ((*d)->map->file[i + 1] && ft_isalpha((*d)->map->file[i + 1])
				&& !ft_isdigit((*d)->map->file[i + 1]))
			{
				if (fill_textures((*d)->tex, (*d)->map->file, &i) == 0)
					error_exit(*d, ERR_TEX_INVALID, line);
			}
			else if ((*d)->map->file[i + 1] && ft_isspace((*d)->map->file[i + 1]) 
				&& !ft_isdigit((*d)->map->file[i + 1]))
			{
				if (fill_colors((*d)->tex, (*d)->map->file, &i) == 0)
					error_exit(*d, ERR_COLOR_INVALID, line);
			}
		}
		else if ((*d)->map->file[i] && ft_isdigit((*d)->map->file[i]))
		{
			while ((*d)->map->file[i] && ft_isdigit((*d)->map->file[i]))
				i++;
/* 			if (create_map(d, map, i) == 0)
				return (err_msg(d->mapinfo.path, ERR_INVALID_MAP, FAILURE));
			return (1); */
		}
		else
			i++;
	}
}

void	parse_file(t_data **d)
{
	char	*line;
	char	*buffer;
	char	*err_msg;

	err_msg = ERR_FILE_EMPTY;
	buffer = ft_strdup("");
	if (!buffer)
		error_exit(*d, ERR_MALLOC, NULL);
	line = get_next_line((*d)->map->fd);
	while (line)
	{
		buffer = string_join(buffer, line, &err_msg);
		line = get_next_line((*d)->map->fd);
	}
	if (!buffer || buffer[0] == '\0')
		error_exit(*d, err_msg, buffer);
	parse_buffer(d, buffer);
	free(buffer);
}
