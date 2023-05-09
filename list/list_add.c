/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:59:02 by nmunoz            #+#    #+#             */
/*   Updated: 2022/06/07 17:59:02 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	list_add_value(t_list *list, t_list_elem *elem, int index)
{
	if (!list || !elem)
		return (0);
	if (list->set && list_contains(list, elem))
	{
		list->del_elem_func(elem->content);
		free(elem);
		return (0);
	}
	if (index == -1)
		index = list->size;
	if (list->size != index)
		elem->next = list_get_by_index(list, index);
	if (index > 0)
		list_get_by_index(list, index - 1)->next = elem;
	if (index == 0)
		list->head = elem;
	list->size = list->size + 1;
	return (1);
}
