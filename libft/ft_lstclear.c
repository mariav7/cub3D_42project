/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:51:40 by nmunoz            #+#    #+#             */
/*   Updated: 2022/01/06 20:52:23 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*est;

	if (!lst)
		return ;
	while (*lst)
	{
		est = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = est;
	}
}
