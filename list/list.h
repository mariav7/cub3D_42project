/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:50:07 by nmunoz            #+#    #+#             */
/*   Updated: 2022/06/07 17:50:07 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIST_H
# define LIST_H

# include <stdlib.h>

typedef struct s_list
{
	int					size;
	struct s_list_elem	*head;
	int					(*compare_func)(void *, void *);
	void				*(*clone_func)(void *);
	void				(*del_elem_func)(void *);
	int					set;
}	t_list;

typedef struct s_list_elem
{
	void				*content;
	struct s_list_elem	*next;

}	t_list_elem;

int			list_add_value(t_list *list, t_list_elem *elem, int index);
t_list		*list_clone(t_list *list);
int			list_contains(t_list *list, t_list_elem *elem);
int			list_contains_value(t_list *list, void *value);
t_list		*list_create(int set);
t_list_elem	*list_create_elem(void *content);
void		list_delete_index(t_list *list, int index);
void		list_delete_value(t_list *list, t_list_elem *elem);
void		list_delete_values(t_list *list);
void		list_delete(t_list *list);
int			list_equals(t_list *list, t_list_elem *elem_1, t_list_elem *elem_2);
int			list_equals_value(t_list *list, void *value_1, void *value_2);
t_list_elem	*list_get_by_index(t_list *list, int index);
int			list_index_of(t_list *list, t_list_elem *elem);
int			list_index_of_value(t_list *list, void *value);
void		list_reverse(t_list *list);
void		list_sort_asc(t_list *list);
int			list_is_sort_asc_index(t_list *list, int start, int max);
int			list_is_sort_asc(t_list *list);
void		list_sort_desc(t_list *list);
int			list_is_sort_desc_index(t_list *list, int start, int max);
int			list_is_sort_desc(t_list *list);
t_list		*list_sublist(t_list *list, int start, int end);
void		list_swap(t_list *list, int index_1, int index_2);

#endif
