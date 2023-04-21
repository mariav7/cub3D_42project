/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:26:56 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/21 16:32:57 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	only_digits(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (i == 0 && (str[i] == '+' || str[i] == '-'))
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

static int	*copy_into_rgb_array(char **rgb_to_convert, int *rgb)
{
	int		i;

	i = -1;
	while (rgb_to_convert[++i])
	{
		rgb[i] = ft_atoll(rgb_to_convert[i]);
		if (rgb[i] == -1 || only_digits(rgb_to_convert[i]) == 0
			|| rgb[i] > 255 || rgb[i] < 0)
		{
			free_tab((void **)rgb_to_convert);
			free(rgb);
			return (0);
		}
	}
	free_tab((void **)rgb_to_convert);
	return (rgb);
}

static char	**get_str_delimiter(char *line, int *j)
{
	int		i;
	char	*str;
	char	**tab;

	*j = *j + 2;
	ignore_spaces(line, j);
	i = *j;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	str = ft_substr(line, *j, (i - *j));
	if (!str)
		return (NULL);
	*j = i;
	tab = ft_split(str, ',');
	if (!tab)
		return (free(str), NULL);
	free(str);
	return (tab);
}

static int	*set_rgb_color(char *line, int *j)
{
	int		i;
	int		*rgb;
	char	**rgb_to_convert;

	rgb_to_convert = get_str_delimiter(line, j);
	if (!rgb_to_convert)
		return (NULL);
	i = 0;
	while (rgb_to_convert[i])
		i++;
	if (i != 3)
		return (free_tab((void **)rgb_to_convert), NULL);
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (NULL);
	return (copy_into_rgb_array(rgb_to_convert, rgb));
}

int	fill_colors(t_tex *tex, char *line, int *i)
{
	if ((tex->ce) && (tex->flo))
		return (0);
	else if (!(tex->ce) && line[*i] == 'C' && (line[*i + 1] == ' '
			|| line[*i + 1] == '\t'))
	{
		tex->ce = set_rgb_color(line, i);
		if (tex->ce == 0)
			return (0);
	}
	else if (!(tex->flo) && line[*i] == 'F' && (line[*i + 1] == ' '
			|| line[*i + 1] == '\t'))
	{
		tex->flo = set_rgb_color(line, i);
		if (tex->flo == 0)
			return (0);
	}
	else
		return (0);
	return (1);
}
