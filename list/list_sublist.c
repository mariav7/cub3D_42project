/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sublist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:26:42 by nmunoz            #+#    #+#             */
/*   Updated: 2022/06/08 23:26:42 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_sublist(t_list *list, int start, int end)
{
	t_list	*sub_list;

	if (!list)
		return (NULL);
	if (end > list->size - 1)
		end = list->size - 1;
	if (start > end)
		return (NULL);
	sub_list = list_create(list->set);
	sub_list->clone_func = list->clone_func;
	sub_list->compare_func = list->compare_func;
	sub_list->del_elem_func = list->del_elem_func;
	while (end >= start)
	{
		list_add_value(sub_list, list_create_elem(list->clone_func(
					list_get_by_index(list, start++)->content)), -1);
	}
	return (sub_list);
}
