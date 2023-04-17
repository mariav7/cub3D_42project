/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:31:03 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/17 16:22:27 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int    fill_map(t_map *m, char *line, int *i)
{
    int     s;
    int     e;
    char    *tmp;

    s = *i;
    while (line[*i] && (line[*i] == '0' || line[*i] == '1'
        || ft_isspace(line[*i]) || line[*i] == 'N' || line[*i] == 'S' 
        || line[*i] == 'E' || line[*i] == 'W'))
        (*i)++;
    e = *i;
    tmp = ft_substr((const char *)line, s, e);
    if (!tmp)
        return (0);
    m->map = ft_split(tmp, '\n');
    free(tmp);
    if (!m->map)
        return (0);
    s = -1;
    while (m->map[++s])
        printf("[%d]%s\n", s, m->map[s]);
    free_tab((void **)m->map);
    return (1);
}
