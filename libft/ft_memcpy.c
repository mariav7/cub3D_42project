/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:19:57 by nmunoz            #+#    #+#             */
/*   Updated: 2021/12/29 13:32:54 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	int	count;

	if (dest == NULL && src == NULL)
		return (NULL);
	count = len;
	while (len)
	{
		*(char *)dest ++ = *(const char *)src ++;
		len--;
	}
	dest -= count;
	return (dest);
}
