/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:31:03 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/25 15:16:45 by mflores-         ###   ########.fr       */
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
//////////////////////////////////////////////////////

/* static	int	ft_char_in_set(char c, char const *set)
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
} */

/* int	fill_map(t_map *m, char *line, int *i)
{
	int		s;
	char	*tmp;
	int		x;

	printf("TOTO\n");
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
			|| ft_isspace(line[*i]) || line[*i] == 'N' || line[*i] == 'S'
				|| line[*i] == 'E' || line[*i] == 'W'))
	{
		if (ft_isdigit(line[*i]))
		{
			(*i)++;
			x = *i;
			while (line[x] && ft_isspace(line[x]))
				x++;
			if (line[x] == '\0')
				break ;
			else
				(*i)++;
		}
		else
			(*i)++;
	}
	// if (line[*i] == '\0')
	// {
	// 	x = *i;
	// 	//--(*i);
	// 	printf("HERE=>%s\n", line + *i);
	// 	while (line[*i] && ft_isspace(line[*i]))
	// 		--(*i);
	// 	printf("HERE 2=>%s\n*i=>%d\n", line + *i, *i);
	// }
	tmp = ft_substr((const char *)line, s, *i);
	if (!tmp)
		return (0);
	printf("tmp=>%s-end\n", tmp);
	// *i = x;
	m->map = ft_split(tmp, '\n');
	free(tmp);
	if (!m->map)
		return (0);
	while (line[*i])
		(*i)++;
	return (1);
} */

int	fill_map(t_map *m, char *line, int *i)
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
