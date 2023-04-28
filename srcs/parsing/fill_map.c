/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:31:03 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/28 11:37:49 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_rest_of_map(int nb_line, t_data **d, int *i)
{
	while (*i < nb_line && (*d)->map->file[*i])
	{
		if (ft_check_chars((*d)->map->file[*i], "01NSEW \t\n\v\f\r") == 0)
		{
			if (!(*d)->tex->no || !(*d)->tex->so || !(*d)->tex->ea
				|| !(*d)->tex->we || !(*d)->tex->ce || !(*d)->tex->flo)
				error_exit(*d, ERR_MAP_ISFIRST, NULL);
			else
				error_exit(*d, ERR_MAP_CHARS, NULL);
		}
		else if (has_only_spaces((*d)->map->file[*i]) == 1)
			(*i)++;
		else
			error_exit(*d, ERR_MAP_INVALID, NULL);
	}
}

static void	get_end_map(int *end, int nb_line, t_data **d, int *i)
{
	int	len;

	len = 0;
	while (*i < nb_line && (*d)->map->file[*i])
	{
		*end = *i;
		if (ft_check_chars((*d)->map->file[*i], "01NSEW \t\n\v\f\r") == 0)
			error_exit(*d, ERR_MAP_CHARS, NULL);
		else if (has_only_spaces((*d)->map->file[*i]) == 1)
		{
			*end = *i - 1;
			break ;
		}
		len = ft_strlend((*d)->map->file[*i]);
		if (len > (*d)->map->width)
			(*d)->map->width = len;
		(*i)++;
	}
	check_rest_of_map(nb_line, d, i);
}

static char	*transform_line(char *str, int max_width)
{
	int		i;
	char	*tmp;

	tmp = malloc(sizeof(char) * (max_width + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	while (++i < max_width && str[i] && str[i] != '\n')
		tmp[i] = str[i];
	while (i < max_width)
		tmp[i++] = ' ';
	tmp[i] = '\0';
	return (tmp);
}

static char	*get_map_line(char *str, int max_width)
{
	char	*tmp;
	int		str_len;

	str_len = ft_strlend(str);
	if (str_len < max_width)
		tmp = transform_line(str, max_width);
	else
		tmp = ft_substr(str, 0, max_width);
	return (tmp);
}

void	fill_map(int *i, int nb_line, t_data **d)
{
	int		start;
	int		end;

	start = *i;
	end = start;
	get_end_map(&end, nb_line, d, i);
	if (*i == nb_line)
	{
		(*d)->map->height = (end - start) + 1;
		(*d)->map->map = malloc(sizeof(char *) * ((*d)->map->height + 1));
		if (!(*d)->map->map)
			error_exit(*d, ERR_MALLOC, NULL);
		nb_line = 0;
		while (nb_line < (*d)->map->height)
		{
			(*d)->map->map[nb_line] = get_map_line((*d)->map->file[start++], \
			(*d)->map->width);
			if (!(*d)->map->map[nb_line])
				error_exit(*d, ERR_MALLOC, NULL);
			nb_line++;
		}
		(*d)->map->map[nb_line] = 0;
	}
}
