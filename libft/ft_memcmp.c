/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:39:32 by nmunoz            #+#    #+#             */
/*   Updated: 2021/12/29 13:41:08 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 1;
	while (*(const unsigned char *)s1 == *(const unsigned char *)s2 && n > i)
	{
		s1++;
		s2++;
		i++;
	}
	if (n > 0)
		return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
	return (0);
}
