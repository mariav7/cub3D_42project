/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:56:11 by nmunoz            #+#    #+#             */
/*   Updated: 2022/01/06 20:57:23 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*est;

	est = (t_list *) malloc(sizeof(*est));
	if (!est)
		return (NULL);
	est->content = content;
	est->next = NULL;
	return (est);
}
