/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:26:56 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/14 20:21:36 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	no_digit(char *str)
{
	int		i;
	int	found_no_digit;

	i = 0;
	found_no_digit = 1;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			found_no_digit = 0;
		i++;
	}
	return (found_no_digit);
}

static int	*copy_into_rgb_array(char **rgb_to_convert, int *rgb)
{
	int	    	i;

	i = -1;
	while (rgb_to_convert[++i])
	{
		rgb[i] = ft_atoll(rgb_to_convert[i]);
		if (rgb[i] == -1 || no_digit(rgb_to_convert[i]) == 1 
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

static int	*set_rgb_color(char *line, int *j)
{
	char	**rgb_to_convert;
	int		*rgb;
	int		count;
    char    *str;
    int     i;

    *j = *j + 2;
    while (line[*j] && ft_isspace(line[*j]))
        (*j)++;
    i = *j;
    while (line[i] && !ft_isspace(line[i]))
        i++;
    str = ft_substr(line, *j, (i - *j));
    if (!str)
        return (0);
    *j = i;
    rgb_to_convert = ft_split(str, ',');
    if (!rgb_to_convert)
        return (free(str), NULL);
    free(str);
	count = 0;
	while (rgb_to_convert[count])
		count++;
    if (count != 3)
		return (free_tab((void **)rgb_to_convert), NULL);
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (0);
    return (copy_into_rgb_array(rgb_to_convert, rgb));
}

int	fill_colors(t_tex *tex, char *line, int *j)
{
	if (!(tex->ce) && line[*j] == 'C')
	{
		tex->ce = set_rgb_color(line, j);
		if (tex->ce == 0)
			return (0);
	}
	else if (!(tex->flo) && line[*j] == 'F')
	{
		tex->flo = set_rgb_color(line, j);
		if (tex->flo == 0)
			return (0);
	}
	else
		return (0);
    return (1);
}