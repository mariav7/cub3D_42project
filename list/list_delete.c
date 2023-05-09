/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:20:49 by nmunoz            #+#    #+#             */
/*   Updated: 2022/06/24 12:15:58 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_delete_index(t_list *list, int index)
{
	t_list_elem	*value;
	t_list_elem	*index_one;

	if (!list)
		return ;
	value = list_get_by_index(list, index);
	if (!value)
		return ;
	if (index > 0 && list->size > index + 1)
	{
		index_one = list_get_by_index(list, index + 1);
		list_get_by_index(list, index - 1)->next = index_one;
	}
	else if (list->size - 1 == index && index != 0)
		list_get_by_index(list, index - 1)->next = NULL;
	if (index == 0)
		list->head = value->next;
	list->del_elem_func(value->content);
	free(value);
	list->size = list->size - 1;
}

void	list_delete_values(t_list *list)
{
	t_list_elem	*tmp;

	while (list->head)
	{
		tmp = list->head->next;
		list->del_elem_func(list->head->content);
		free(list->head);
		list->head = tmp;
		list->size = list->size - 1;
	}
}

void	list_delete_value(t_list *list, t_list_elem *elem)
{
	int	index;

	index = list_index_of(list, elem);
	if (index == -1)
		return ;
	list_delete_index(list, index);
}

void	list_delete(t_list *list)
{
	list_delete_values(list);
	free(list);
}
