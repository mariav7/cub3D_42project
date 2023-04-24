/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:03:10 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/24 19:57:20 by mflores-         ###   ########.fr       */
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

static void	texture_or_color(t_data **d, int *i)
{
	char	*err_msg;

	err_msg = ERR_ID_INVALID;
	if ((*d)->map->file[*i + 1] && ft_isalpha((*d)->map->file[*i + 1])
		&& !ft_isdigit((*d)->map->file[*i + 1]))
	{
		if (fill_textures((*d)->tex, (*d)->map->file, i) == 0)
			error_exit(*d, err_msg, NULL);
	}
	else if ((*d)->map->file[*i + 1]
		&& ft_isspace((*d)->map->file[*i + 1])
		&& !ft_isdigit((*d)->map->file[*i + 1]))
	{
		if (fill_colors((*d)->tex, (*d)->map->file, i, &err_msg) == 0)
			error_exit(*d, err_msg, NULL);
	}
	else
		error_exit(*d, ERR_TEXCO_FORMAT, NULL);
}

static void	parse_buffer(t_data **d, int *flag)
{
	int		i;
	int		start;

	i = 0;
	while ((*d)->map->file[i])
	{
		start = i;
		while ((*d)->map->file[i] && ft_isspace((*d)->map->file[i]))
			i++;
		if ((*d)->map->file[i] && ft_isalpha((*d)->map->file[i]))
			texture_or_color(d, &i);
		else if ((*d)->map->file[i] && ft_isdigit((*d)->map->file[i]))
		{
			if (!(*d)->tex->no || !(*d)->tex->so || !(*d)->tex->ea
				|| !(*d)->tex->we || !(*d)->tex->ce || !(*d)->tex->flo)
				*flag = 1;
			i = start;
			if (fill_map((*d)->map, (*d)->map->file, &i) == 0)
				error_exit(*d, ERR_MAP_INVALID, NULL);
		}
		else
			error_exit(*d, ERR_TEXCO_FORMAT, NULL);
	}
	return ;
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
	ret = check_map(d, &err_msg);
	if (ret == 0)
		error_exit(*d, err_msg, NULL);
}

void	parse_file(t_data **d)
{
	char	*line;
	char	*err_msg;
	int		flag;

	err_msg = ERR_FILE_EMPTY;
	flag = 0;
	(*d)->map->file = ft_strdup("");
	line = get_next_line((*d)->map->fd);
	while (line)
	{
		(*d)->map->file = string_join((*d)->map->file, line, &err_msg);
		line = get_next_line((*d)->map->fd);
	}
	if (!(*d)->map->file || (*d)->map->file[0] == '\0')
		error_exit(*d, err_msg, NULL);
	parse_buffer(d, &flag);
	if (flag == 1 && (*d)->tex->no && (*d)->tex->so && (*d)->tex->ea
		&& (*d)->tex->we && (*d)->tex->ce && (*d)->tex->flo)
		error_exit(*d, ERR_MAP_ISFIRST, NULL);
	if (!(*d)->tex->ce || !(*d)->tex->flo)
		error_exit(*d, ERR_FILE_INVALID, NULL);
	check_data(d);
}
