/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:03:10 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/13 18:40:36 by mflores-         ###   ########.fr       */
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

static void	parse_buffer(t_data **d, char *line)
{
/* 	int	i;

	i = 0; */
	(*d)->map->file = ft_strtrim(line, " ");
	if (!(*d)->map->file)
		error_exit(*d, ERR_MALLOC, line);
	printf("(*d)->map->file:%s\n", (*d)->map->file);
/*     if (ft_isprint((*d)->map->file[i]) && !ft_isdigit((*d)->map->file[i]))
    {
        if (!(*d)->tex->no && ft_strncmp(*line, "no ", 3))
    }
    else if (ft_isdigit((*d)->map->file[i]))
    {
        
    } */
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
