/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:12:00 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/14 19:42:08 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    debug(t_data *d)
{
    printf(PURPLE"<======\tTesting Program\t=====>\n"DEFAULT);
	printf(WHITE" => Connection to Minilibx...\n"DEFAULT);
	printf(WHITE" => Window %dx%d "TITLE"\n"DEFAULT, WIN1_SX, WIN1_SY);
	printf(BLUE"\n--- STRUCT MAP ---\nfile:%s\n"DEFAULT, d->map->file);
	printf(YELLOW"\n--- STRUCT TEXTURES ---\n");
	printf("NO: %s\nSO: %s\nEA: %s\nWE: %s\n", \
	d->tex->no, d->tex->so, d->tex->ea, d->tex->we);
	printf("CE: %d\nFLO: %d\n"DEFAULT, d->tex->ce[0], d->tex->flo[0]);
}