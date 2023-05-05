/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:57:52 by nmunoz            #+#    #+#             */
/*   Updated: 2022/06/07 17:57:52 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_create(int set)
{
	t_list	*list;

	list = (t_list *) malloc(sizeof(t_list));
	list->size = 0;
	list->head = NULL;
	list->clone_func = NULL;
	list->compare_func = NULL;
	list->del_elem_func = NULL;
	list->set = set;
	return (list);
}

t_list_elem	*list_create_elem(void *content)
{
	t_list_elem	*elem;

	elem = (t_list_elem *) malloc(sizeof(t_list_elem));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}
