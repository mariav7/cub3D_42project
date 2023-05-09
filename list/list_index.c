/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_index.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:39:53 by nmunoz            #+#    #+#             */
/*   Updated: 2022/06/21 13:39:53 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	list_index_of(t_list *list, t_list_elem *elem)
{
	t_list_elem	*iterator;
	int			i;

	if (!list)
		return (-1);
	i = 0;
	iterator = list->head;
	while (iterator)
	{
		if (list_equals(list, iterator, elem))
			return (i);
		i++;
		iterator = iterator->next;
	}
	return (-1);
}

int	list_index_of_value(t_list *list, void *value)
{
	t_list_elem	*iterator;
	int			i;

	if (!list)
		return (-1);
	i = 0;
	iterator = list->head;
	while (iterator)
	{
		if (list_equals_value(list, iterator->content, value))
			return (i);
		i++;
		iterator = iterator->next;
	}
	return (-1);
}
