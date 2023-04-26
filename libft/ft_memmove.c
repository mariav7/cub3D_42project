/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:34:31 by nmunoz            #+#    #+#             */
/*   Updated: 2021/12/29 13:37:49 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	if (dest == NULL && src == NULL)
		return (NULL);
	if (src > dest)
		ft_memcpy(dest, src, len);
	else
		while (len--)
			*(char *)(dest + len) = *(char *)(src + len);
	return (dest);
}
