/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_equals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:10:23 by nmunoz            #+#    #+#             */
/*   Updated: 2022/06/21 11:10:23 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	list_equals(t_list *list, t_list_elem *elem_1, t_list_elem *elem_2)
{
	return (!list->compare_func(elem_1->content, elem_2->content));
}

int	list_equals_value(t_list *list, void *value_1, void *value_2)
{
	return (!list->compare_func(value_1, value_2));
}
