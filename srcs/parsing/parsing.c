/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:03:10 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/26 11:08:25 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* static char	*string_join(char *s1, char *s2, char **err_msg)
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
} */

/* void	parse_file(t_data **d)
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
} */

////////////////////////////////////////////////////////////////////////////

static	int	ft_char_in_set(char *str, char const *set)
{
	size_t	i;
	size_t	x;

	x = 0;
	while (str[x])
	{
		i = 0;
		while (set[i])
		{
			if (set[i] == str[x])
				return (1);
			i++;
		}
		x++;
	}
	return (0);
}

static int	count_lines(char *path)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	else
	{
		line = get_next_line(fd);
		while (line)
		{
			i++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (i);
}

static void	texture_or_color(t_data **d, int *i, char *row)
{
	char	*err_msg;

	err_msg = ERR_ID_INVALID;
	if (row[*i + 1] && ft_isalpha(row[*i + 1])
		&& !ft_isdigit(row[*i + 1]))
	{
		if (fill_textures((*d)->tex, row, i) == 0)
			error_exit(*d, err_msg, NULL);
	}
	else if (row[*i + 1]
		&& ft_isspace(row[*i + 1])
		&& !ft_isdigit(row[*i + 1]))
	{
		if (fill_colors((*d)->tex, row, i, &err_msg) == 0)
			error_exit(*d, err_msg, NULL);
	}
	else
		error_exit(*d, ERR_TEXCO_FORMAT, NULL);
}

static int	parse_row(t_data **d, int *flag, char *row)
{
	int		i;
	int		start;

	i = 0;
	while (row[i])
	{
		start = i;
		while (row[i] && ft_isspace(row[i]))
			i++;
		if (row[i] && ft_isalpha(row[i]))
			texture_or_color(d, &i, row);
		else if (row[i] && ft_isdigit(row[i]))
		{
			if (!(*d)->tex->no || !(*d)->tex->so || !(*d)->tex->ea
				|| !(*d)->tex->we || !(*d)->tex->ce || !(*d)->tex->flo)
				*flag = 1;
			return (2);
			//i = start;
/* 			if (fill_map((*d)->map, (*d)->map->file, &i) == 0)
				error_exit(*d, ERR_MAP_INVALID, NULL); */
		}
		else
			return (1);
	}
	return (1);
}

static int	has_only_spaces(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{ 
		if (str[i] && !ft_isspace(str[i]))
			return (0);
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
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
	char	**tab;
	char	*err_msg;
	char	*line;
	int		flag;
	int		nb_line;
	int		i;
	int		x;
	int		map_lines;

	err_msg = ERR_FILE_EMPTY;
	flag = 0;
	nb_line = count_lines((*d)->map->path);
	if (nb_line == 0 || nb_line == -1)
		error_exit(*d, err_msg, NULL);
	tab = malloc(sizeof(char *) * (nb_line + 1));
	if (!tab)
		error_exit(*d, ERR_MALLOC, NULL);
	tab[nb_line] = 0;
	nb_line = 0;
	line = get_next_line((*d)->map->fd);
	while (line)
	{
		tab[nb_line] = ft_strdup(line);
		free(line);
		if (!tab[nb_line])
		{
			free_tab((void **)tab);
			error_exit(*d, ERR_MALLOC, NULL);
		}
		printf("tab[%d]%s", nb_line, tab[nb_line]);
		nb_line++;
		line = get_next_line((*d)->map->fd);
	}
	i = 0;
	while (i < nb_line)
	{
		//printf("[%d]%s", i, tab[i]);
		map_lines = parse_row(d, &flag, tab[i]);
		if (map_lines == 2)
			break ;
		else if (map_lines == -1)
		{
			free_tab((void **)tab);
			error_exit(*d, ERR_TEXCO_FORMAT, NULL);
		}
		i++;
	}
	if (map_lines == 2)
	{
		map_lines = 0;
		x = i;
		while (i < nb_line)
		{
			if (ft_char_in_set(tab[i], "01NSEW \t\v\f\r") == 0)
			{
				free_tab((void **)tab);
				error_exit(*d, ERR_MAP_INVALID, NULL);
			}
			i++;
		}
		--i;
		while (i > x)
		{
			//printf("HERE=>[%d]%s", i, tab[i]);
			if (has_only_spaces(tab[i]) == 1)
				--i;
			else
				break;
		}
		map_lines = (i - x) + 1;
		printf("map_lines:%d\n", map_lines);
		(*d)->map->map = malloc(sizeof(char *) * (map_lines + 1));
		if (!(*d)->map->map)
			error_exit(*d, ERR_MALLOC, NULL);
		(*d)->map->map[map_lines] = 0;
		nb_line = 0;
		while (nb_line < map_lines)
		{
			(*d)->map->map[nb_line] = ft_strdup(tab[x++]);
			if (!(*d)->map->map[nb_line])
			{
				free_tab((void **)tab);
				error_exit(*d, ERR_MALLOC, NULL);
			}
			nb_line++;
		}
		free_tab((void **)tab);
	}
	//parse_buffer(d, &flag);
	if (flag == 1)
		error_exit(*d, ERR_MAP_ISFIRST, NULL);
/* 	if (flag == 1 && (*d)->tex->no && (*d)->tex->so && (*d)->tex->ea
		&& (*d)->tex->we && (*d)->tex->ce && (*d)->tex->flo)
		error_exit(*d, ERR_MAP_ISFIRST, NULL); */
	if (!(*d)->tex->ce || !(*d)->tex->flo)
		error_exit(*d, ERR_FILE_INVALID, NULL);
	check_data(d);
}
