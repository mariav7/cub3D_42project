/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sort_asc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:10:34 by nmunoz            #+#    #+#             */
/*   Updated: 2022/06/08 14:10:34 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_sort_asc(t_list *list)
{
	int	i;

	if (!list)
		return ;
	if (2 > list->size)
		return ;
	i = 0;
	while (list->size > ++i)
	{
		if (list->compare_func(list_get_by_index(list, i - 1)->content,
				list_get_by_index(list, i)->content) == 1)
		{
			list_swap(list, i, i - 1);
			i = 0;
		}
	}
}

int	list_is_sort_asc_index(t_list *list, int start, int max)
{
	if (!list)
		return (0);
	if (max == -1 || max == 0 || max > list->size)
		max = list->size - 1;
	if (start == 0)
		start++;
	while (max >= start)
	{
		if (list->compare_func(list_get_by_index(list, start - 1)->content,
				list_get_by_index(list, start)->content) == 1)
			return (0);
		start++;
	}
	return (1);
}

int	list_is_sort_asc(t_list *list)
{
	return (list_is_sort_asc_index(list, 0, -1));
}
