/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:24:21 by nmunoz            #+#    #+#             */
/*   Updated: 2022/06/08 14:24:21 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_clone(t_list *list)
{
	t_list		*new_list;
	t_list_elem	*elem;

	if (!list)
		return (NULL);
	new_list = list_create(list->set);
	new_list->compare_func = list->compare_func;
	new_list->clone_func = list->clone_func;
	new_list->del_elem_func = list->del_elem_func;
	elem = list->head;
	while (elem)
	{
		list_add_value(new_list,
			list_create_elem(list->clone_func(elem->content)), -1);
		elem = elem->next;
	}
	return (new_list);
}
