/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:19:19 by nmunoz            #+#    #+#             */
/*   Updated: 2022/06/08 14:19:19 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_swap(t_list *list, int index_1, int index_2)
{
	t_list_elem	*tmp_1;
	t_list_elem	*tmp_2;
	t_list_elem	*before_1;

	if (list->size <= index_1 || list->size <= index_2)
		return ;
	before_1 = NULL;
	tmp_1 = list_get_by_index(list, index_1);
	tmp_2 = list_get_by_index(list, index_2);
	if (index_1 != 0)
		before_1 = list_get_by_index(list, index_1 - 1);
	if (index_2 != 0)
		list_get_by_index(list, index_2 - 1)->next = tmp_1;
	if (before_1)
		before_1->next = tmp_2;
	before_1 = tmp_1->next;
	tmp_1->next = tmp_2->next;
	tmp_2->next = before_1;
	if (index_1 == 0)
		list->head = tmp_2;
	if (index_2 == 0)
		list->head = tmp_1;
}
