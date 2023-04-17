/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:10:59 by nmunoz            #+#    #+#             */
/*   Updated: 2022/06/07 18:10:59 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list_elem	*list_get_by_index(t_list *list, int index)
{
	t_list_elem	*elem;
	int			i;

	if (!list)
		return (NULL);
	elem = list->head;
	i = 0;
	while (elem)
	{
		if (index == i++)
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}
