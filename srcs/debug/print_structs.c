/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:12:00 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/26 10:42:04 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_struct_textures(t_tex *t)
{
	printf(YELLOW"\n<-----\tSTRUCT TEXTURES\t----->\n\n"DEFAULT);
	printf(YELLOW"NO: %s\nSO: %s\nEA: %s\nWE: %s\n"DEFAULT, \
	t->no, t->so, t->ea, t->we);
	if (t->ce && t->flo)
	{
		printf(YELLOW"CEILING: [%d][%d][%d]\n"DEFAULT, t->ce[0], \
		t->ce[1], t->ce[2]);
		printf(YELLOW"FLOOR: [%d][%d][%d]\n"DEFAULT, t->flo[0], \
		t->flo[1], t->flo[2]);
	}
	printf(YELLOW"\n<-----\tEND STRUCT TEXTURES\t----->\n"DEFAULT);
}

void	print_struct_map(t_map *m)
{
	int		i;

	i = -1;
	printf(BLUE"\n<-----\tSTRUCT MAP\t----->\n\n"DEFAULT);
	if (m->file)
		printf(BLUE"file:%s\n"DEFAULT, m->file);
	if (m->path)
		printf(BLUE"path:%s\n"DEFAULT, m->path);
	if (m->map)
	{
		printf(BLUE"map:\n"DEFAULT);
		while (m->map[++i])
			printf(BLUE"\t[%d]\t%s"DEFAULT, i, m->map[i]);
	}
	printf(BLUE"\n<-----\tEND STRUCT MAP\t----->\n"DEFAULT);
}

void	debug(t_data *d)
{
	printf(PURPLE"<======\tTesting Program\t=====>\n"DEFAULT);
	printf(WHITE" => Connection to Minilibx...\n"DEFAULT);
	printf(WHITE" => Window %dx%d "TITLE"\n"DEFAULT, WIN1_SX, WIN1_SY);
	print_struct_map(d->map);
	print_struct_textures(d->tex);
}
