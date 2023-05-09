/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_reverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 00:00:10 by nmunoz            #+#    #+#             */
/*   Updated: 2022/06/09 00:00:10 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_reverse(t_list *list)
{
	int	i;
	int	j;

	if (!list || 2 > list->size)
		return ;
	i = 0;
	j = list->size - 1;
	while (j > i)
		list_swap(list, i++, j--);
}
