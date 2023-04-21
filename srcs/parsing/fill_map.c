/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:31:03 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/21 17:53:20 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_map(t_map *m, char *line, int *i)
{
	int		s;
	char	*tmp;

	if (m->map)
		return (0);
	s = *i;
	while (line[*i] && (line[*i] == '0' || line[*i] == '1'
			|| ft_isspace(line[*i]) || (line[*i] == 'N'
				&& !ft_isalpha(line[*i + 1])) || (line[*i] == 'S'
				&& !ft_isalpha(line[*i + 1])) || (line[*i] == 'E'
				&& !ft_isalpha(line[*i + 1])) || (line[*i] == 'W'
				&& !ft_isalpha(line[*i + 1]))))
		(*i)++;
	tmp = ft_substr((const char *)line, s, *i);
	if (!tmp)
		return (0);
	m->map = ft_split(tmp, '\n');
	free(tmp);
	if (!m->map)
		return (0);
	return (1);
}
