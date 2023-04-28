/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:24:28 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/28 11:28:47 by mflores-         ###   ########.fr       */
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
