/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:14:54 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/21 17:17:14 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
