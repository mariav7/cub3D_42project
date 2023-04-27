/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:31:03 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/27 21:08:52 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_only_spaces(char *str)
{
	int		i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

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

static int	ft_check_chars(char *str, char const *set)
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

static size_t	ft_strlend(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (len);
	while (s[len] && s[len] != '\n')
		len++;
	return (len);
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
	while (*i < nb_line && (*d)->map->file[*i])
	{
		if (ft_check_chars((*d)->map->file[*i], "01NSEW \t\n\v\f\r") == 0)
			error_exit(*d, ERR_MAP_CHARS, NULL);
		else if (has_only_spaces((*d)->map->file[*i]) == 1)
			(*i)++;
		else
			error_exit(*d, ERR_MAP_INVALID, NULL);
	}
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

static int	is_special_char(char c, int check_zero)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (check_zero)
	{
		if (c == '0')
			return (1);
	}
	return (0);
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
			if ((map->map[i][j + 1] && is_special_char(map->map[i][j + 1], 1))
				|| (j != 0 && map->map[i][j - 1]
				&& is_special_char(map->map[i][j - 1], 1)))
				return (0);
			if (top)
			{
				x = 1;
				while (map->map[x][j])
				{
					if (map->map[x][j] != '1' && !ft_isspace(map->map[x][j]))
						return (0);
					else if (map->map[x][j] == '1')
						break ;
					else if (ft_isspace(map->map[x][j]))
					{
						if ((map->map[x][j + 1]
							&& is_special_char(map->map[x][j + 1], 1))
							|| (j != 0 && map->map[x][j - 1]
							&& is_special_char(map->map[x][j - 1], 1)))
							return (0);
					}
					x++;
					if (x == map->height)
						break ;
				}
			}
			else
			{
				x = i - 1;
				while (map->map[x][j] && x >= 0)
				{
					if (map->map[x][j] != '1' && !ft_isspace(map->map[x][j]))
						return (0);
					else if (map->map[x][j] == '1')
						break ;
					else if (ft_isspace(map->map[x][j]))
					{
						if ((map->map[x][j + 1]
							&& is_special_char(map->map[x][j + 1], 1))
							|| (j != 0 && map->map[x][j - 1]
							&& is_special_char(map->map[x][j - 1], 1)))
							return (0);
					}
					x--;
					if (x < 0)
						break ;
				}	
			}
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
	if (check_top_or_bottom(map, 0, 0, 1) == 0)
		return (0);
	i = (map->height - 1);
	if (check_top_or_bottom(map, i, 0, 0) == 0)
		return (0);
	i = 1;
	while (i < (map->height - 1))
	{
		x = 0;
		j = ft_strlen(map->map[i]) - 1;
		while (map->map[i][x] && ft_isspace(map->map[i][x]))
			x++;
		if (map->map[i][x] != '1')
			return (0);
		while (map->map[i][j] && ft_isspace(map->map[i][j]))
			j--;
		if (map->map[i][j] != '1')
			return (0);
		while (++x < j && map->map[i][x])
		{
			if (is_special_char(map->map[i][x], 1))
			{
				if ((map->map[i][x + 1] && ft_isspace(map->map[i][x + 1]))
					|| (x != 0 && ft_isspace(map->map[i][x - 1])))
				{
					*err_msg = ERR_MAP_SPACES;
					return (0);
				}
			}
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
	{
		*err_msg = ERR_MAP_PLAYER;
		return (0);
	}
	return (1);
}

static int	check_pos_is_valid(t_map *m, char **err_msg)
{
	int	y;
	int	x;

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

int	check_map(t_map *m, char **err_msg)
{
	if (check_map_sides(m, err_msg) == 0)
		return (0);
	if (check_map_elements(m, err_msg) == 0)
		return (0);
	if (check_pos_is_valid(m, err_msg) == 0)
		return (0);
	return (1);
}
