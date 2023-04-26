/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 19:55:51 by nmunoz            #+#    #+#             */
/*   Updated: 2022/01/06 20:00:15 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*values;

	if (!s || !f)
		return (NULL);
	values = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!values)
		return (NULL);
	i = 0;
	while (*s)
		*values++ = f(i++, *s++);
	*values = 0;
	return (values -= i);
}
