/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:15:26 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/21 17:45:31 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ignore_spaces(char *str, int *index)
{
	if (str && index)
	{
		while (str[*index] && ft_isspace(str[*index]))
			(*index)++;
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