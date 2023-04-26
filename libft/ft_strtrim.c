/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:03:18 by nmunoz            #+#    #+#             */
/*   Updated: 2022/01/06 20:05:01 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_contains(char const c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	length;

	if (!s1)
		return (NULL);
	start = 0;
	length = ft_strlen(s1);
	end = length;
	while (*s1 && ft_contains(*s1, set) && s1++)
		start++;
	s1 += (length - start - 1);
	while (length-- && ft_contains(*s1, set) && s1--)
		end--;
	s1 -= (length);
	if (start >= end)
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start));
}
