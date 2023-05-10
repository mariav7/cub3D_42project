/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:24:28 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/10 12:59:52 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	check_between_walls(t_map *map, int i, int x, int j)
{
	while (++x < j && map->map[i][x])
	{
		if (is_special_char(map->map[i][x], 1))
		{
			if ((map->map[i][x + 1] && ft_isspace(map->map[i][x + 1]))
				|| (x != 0 && ft_isspace(map->map[i][x - 1])))
				return (0);
		}
	}
	return (1);
}

int	ft_check_chars(char *str, char const *set)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_char_in_set(str[i], set) == 0)
			return (0);
		i++;
	}
	return (1);
}

size_t	ft_strlend(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (len);
	while (s[len] && s[len] != '\n')
		len++;
	return (len);
}

int	check_lines(t_map *m, char **err_msg, int height)
{
	int	x;
	int	i;

	*err_msg = ERR_MAP_NOTCLOSED;
	i = 1;
	while (i < height)
	{
		x = 0;
		while (m->map[i][x])
		{
			if (is_special_char(m->map[i][x], 1))
			{
				if (i > 1 && i < height && (ft_isspace(m->map[i + 1][x])
					|| ft_isspace(m->map[i - 1][x])))
					return (0);
			}
			x++;
		}
		i++;
	}
	return (1);
}
