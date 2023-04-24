/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:31:03 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/24 20:27:31 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* int	fill_map(t_map *m, char *line, int *i)
{
	int		s;
	char	*tmp;

	if (m->map)
		return (0);
	s = *i;
	while (line[*i] && (line[*i] == '0' || line[*i] == '1'
			|| ft_isspace(line[*i]) || (line[*i] == 'N'
				&& !ft_isalpha(line[*i + 1])) || (line[*i] == 'S'
				&& !ft_isalpha(line[*i + 1])) || (line[*i] == 'E'
				&& !ft_isalpha(line[*i + 1])) || (line[*i] == 'W'
				&& !ft_isalpha(line[*i + 1]))))
		(*i)++;
	tmp = ft_substr((const char *)line, s, *i);
	if (!tmp)
		return (0);
	m->map = ft_split(tmp, '\n');
	free(tmp);
	if (!m->map)
		return (0);
	return (1);
} */

static	int	ft_char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/* static int	check_line()
{
	
} */

int	fill_map(t_map *m, char *line, int *i)
{
	int		s;
	char	*tmp;
	int		x;

	if (m->map)
		return (0);
	s = *i;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (line[*i] != '1' || !line[*i])
		return (0);
	x = *i;
	while (line[x])
	{
		if (ft_char_in_set(line[x++], "01NSEW \t\n\v\f\r") == 0)
			return (0);
	}
	while (line[*i] && (line[*i] == '0' || line[*i] == '1'
			|| ft_isspace(line[*i]) || (line[*i] == 'N'
				&& !ft_isalpha(line[*i + 1])) || (line[*i] == 'S'
				&& !ft_isalpha(line[*i + 1])) || (line[*i] == 'E'
				&& !ft_isalpha(line[*i + 1])) || (line[*i] == 'W'
				&& !ft_isalpha(line[*i + 1]))))
	{
/* 		if (line[*i] == '\n')
			if (check_line(line, *i) == 0)
				return (0); */
		(*i)++;
	}
	tmp = ft_substr((const char *)line, s, *i);
	if (!tmp)
		return (0);
	m->map = ft_split(tmp, '\n');
	free(tmp);
	if (!m->map)
		return (0);
	return (1);
}

int	check_map(t_data **d, char **err_msg)
{
	(void)err_msg;
	(void)d;
/* 	if (check_map_sides(d, err_msg))
		return (0);
	if (check_map_elements(d, err_msg))
		return (0);
	if (check_player_position(d, err_msg))
		return (0); */
	return (1);
}
