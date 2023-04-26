/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:05:17 by nmunoz            #+#    #+#             */
/*   Updated: 2022/01/06 20:12:45 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	get_size_split(char const *s, char delimiter)
{
	int		i;
	size_t	size;

	size = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != delimiter && (!s[i + 1] || s[i + 1] == delimiter))
			size++;
		i++;
	}
	return (size);
}

long	str_index(char const *s, char c, size_t start)
{
	while (s[start])
	{
		if (s[start] == c)
			return (start);
		start++;
	}
	return (-1);
}

long	get_start(char const *s, char delimiter, size_t start)
{
	if (ft_strlen(s) >= start)
	{
		while (s[start])
		{
			if (s[start] != delimiter)
				return (start);
			start++;
		}
	}
	return (-1);
}

long	get_next(char const *s, long start, char delimiter)
{
	long	end;
	long	length;

	length = ft_strlen(s);
	if (start >= length - (long)1)
		return ((long) 0);
	end = str_index(s, delimiter, start);
	if (end == (long) -1)
		return (length);
	return (end);
}

char	**ft_split(char const *s, char c)
{
	char	**data;
	long	start;
	long	next;
	size_t	size;

	if (!s)
		return (NULL);
	size = get_size_split(s, c);
	start = get_start(s, c, 0);
	data = (char **) malloc(sizeof(char *) * (size + 1));
	if (!data)
		return (NULL);
	while (size--)
	{
		next = get_next(s, start, c);
		if (next == 0 && start != (long) -1)
			next = start + 1;
		*data = ft_substr(s, start, next - start);
		data++;
		start = get_start(s, c, next + 1);
	}
	*data = 0;
	return (data -= (get_size_split(s, c)));
}
