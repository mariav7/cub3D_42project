/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:15:26 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/28 12:46:56 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_only_spaces(char *str)
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

int	is_special_char(char c, int check_zero)
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

void	ignore_spaces(char *str, int *index, int add)
{
	if (str && index)
	{
		while (str[*index] && ft_isspace(str[*index]))
		{
			if (add)
				(*index)++;
			else
				(*index)--;
		}
	}
}

long long	ft_atoll(const char *str)
{
	unsigned int	i;
	int				neg;
	long long		nb;

	i = 0;
	neg = 1;
	nb = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * neg);
}

unsigned long	rgb_to_hex(int *rgb)
{
	unsigned long	res;
	int				r;
	int				g;
	int				b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	res = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (res);
}
