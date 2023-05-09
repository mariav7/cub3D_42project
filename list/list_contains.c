/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_contains.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:21:04 by nmunoz            #+#    #+#             */
/*   Updated: 2022/06/21 14:21:04 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	list_contains(t_list *list, t_list_elem *elem)
{
	t_list_elem	*iterator;

	if (!list || !list->compare_func)
		return (0);
	iterator = list->head;
	while (iterator)
	{
		if (list_equals(list, iterator, elem))
			return (1);
		iterator = iterator->next;
	}
	return (0);
}

int	list_contains_value(t_list *list, void *value)
{
	t_list_elem	*iterator;

	if (!list || !list->compare_func)
		return (0);
	iterator = list->head;
	while (iterator)
	{
		if (list_equals_value(list, iterator->content, value))
			return (1);
		iterator = iterator->next;
	}
	return (0);
}
