/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:15:01 by nmunoz            #+#    #+#             */
/*   Updated: 2022/01/06 20:25:35 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	select_digit(long number, int sign)
{
	unsigned int	other;

	if (number == 0)
		return (1);
	other = 0;
	while (number > 0)
	{
		number /= 10;
		other++;
	}
	if (sign == -1)
		other++;
	return (other);
}

static void	get_for_dest(char *dest, long number, unsigned int other,
		int sign)
{
	dest[other] = '\0';
	dest[--other] = number % 10 + '0';
	number /= 10;
	while (number > 0)
	{
		dest[--other] = number % 10 + '0';
		number /= 10;
	}
	if (sign == -1)
		dest[0] = '-';
}

char	*ft_itoa(int n)
{
	unsigned int	other;
	long			number;
	int				sign;
	char			*dest;

	sign = 1;
	if (n < 0)
	{
		number = (long)n * -1;
		sign = -1;
	}
	else
		number = n;
	other = select_digit(number, sign);
	dest = malloc(sizeof(char) * (other + 1));
	if (!dest)
		return (NULL);
	get_for_dest(dest, number, other, sign);
	return (dest);
}
