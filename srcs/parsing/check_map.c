/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:15:44 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/10 12:58:49 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_next_wall(t_map *map, int x, int j, int top)
{
	while (map->map[x][j])
	{
		if (map->map[x][j] != '1' && !ft_isspace(map->map[x][j]))
			return (0);
		else if (map->map[x][j] == '1')
			break ;
		else if (ft_isspace(map->map[x][j]))
		{
			if ((map->map[x][j + 1] && is_special_char(map->map[x][j + 1], 1))
				|| (j != 0 && map->map[x][j - 1]
				&& is_special_char(map->map[x][j - 1], 1)))
				return (0);
		}
		if (top)
		{
			if (++x == map->height)
				break ;
		}
		else
		{
			if (--x < 0)
				break ;
		}
	}
	return (1);
}

static int	check_top_or_bottom(t_map *map, int i, int j, int top)
{
	int		x;

	if (!map->map || !map->map[i] || !map->map[i][j])
		return (0);
	while (map->map[i][j])
	{
		if (map->map[i][j] != '1' && !ft_isspace(map->map[i][j]))
			return (0);
		if (ft_isspace(map->map[i][j]))
		{
			if (top)
				x = 1;
			else
				x = i - 1;
			if ((map->map[i][j + 1] && is_special_char(map->map[i][j + 1], 1))
				|| (j != 0 && map->map[i][j - 1]
				&& is_special_char(map->map[i][j - 1], 1)))
				return (0);
			if (!check_next_wall(map, x, j, top))
				return (0);
		}
		j++;
	}
	return (1);
}

static int	check_map_sides(t_map *map, char **err_msg)
{
	int	i;
	int	j;
	int	x;

	*err_msg = ERR_MAP_NOTCLOSED;
	if (!check_top_or_bottom(map, 0, 0, 1)
		|| !check_top_or_bottom(map, (map->height - 1), 0, 0))
		return (0);
	i = 1;
	while (i < (map->height - 1))
	{
		x = 0;
		j = ft_strlen(map->map[i]) - 1;
		ignore_spaces(map->map[i], &x, 1);
		ignore_spaces(map->map[i], &j, 0);
		if (map->map[i][x] != '1' || map->map[i][j] != '1')
			return (0);
		if (!check_between_walls(map, i, x, j))
		{
			*err_msg = ERR_MAP_SPACES;
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_map_elements(t_map *map, char **err_msg)
{
	int	i;
	int	j;
	int	pos;

	i = -1;
	pos = 0;
	*err_msg = ERR_MAP_PLAYER;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (is_special_char(map->map[i][j], 0))
			{
				map->pos_x = j;
				map->pos_y = i;
				map->dir = map->map[i][j];
				pos++;
			}
		}
	}
	if (pos != 1 || !is_special_char(map->dir, 0))
		return (0);
	return (1);
}

int	check_map(t_map *m, char **err_msg)
{
	int	y;
	int	x;

	if (check_map_sides(m, err_msg) == 0)
		return (0);
	if (check_lines(m, err_msg, (m->height - 1)) == 0)
		return (0);
	if (check_map_elements(m, err_msg) == 0)
		return (0);
	y = m->pos_y;
	x = m->pos_x;
	if (m->map[y + 1][x] == '1' && m->map[y - 1][x] == '1'
			&& m->map[y][x + 1] == '1' && m->map[y][x - 1] == '1')
	{
		*err_msg = ERR_MAP_PATH;
		return (0);
	}
	return (1);
}
