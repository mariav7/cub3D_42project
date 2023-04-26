/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:34:00 by nmunoz            #+#    #+#             */
/*   Updated: 2021/12/29 13:39:14 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t	i;

	i = 1;
	while (n >= i)
	{
		if (*(unsigned char *)str == (unsigned char)c)
			return ((unsigned char *) str);
		str++;
		i++;
	}
	return (NULL);
}
