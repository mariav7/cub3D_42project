/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:44:42 by nmunoz            #+#    #+#             */
/*   Updated: 2021/12/29 13:45:40 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_spaces(const char *str)
{
	char	*res;
	size_t	i;

	i = 0;
	while ((str[i] == '\t') || (str[i] == '\n') || (str[i] == '\v')
		|| (str[i] == '\f') || (str[i] == '\r') || (str[i] == ' '))
		i++;
	if ((str[i] == '+') && (str[i + 1] >= '0') && (str[i + 1] <= '9'))
		i++;
	res = &((char *)str)[i];
	return (res);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	res;
	int		sign;
	char	*nstr;

	i = 0;
	res = 0;
	sign = 1;
	nstr = ft_spaces(str);
	if (nstr[i] == '-' && nstr[i + 1] >= '0' && nstr[i + 1] <= '9' && ++i)
		sign = -1;
	while (nstr[i] >= '0' && nstr[i] <= '9')
	{
		if ((res * 10 + (nstr[i] - '0')) / 10 != res)
		{
			if (sign == -1)
				return (0);
			else
				return (-1);
		}
		res = res * 10 + (nstr[i] - '0');
		i++;
	}
	return ((int)res * sign);
}
