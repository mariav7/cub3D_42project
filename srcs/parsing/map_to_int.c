#include "cub3d.h"

void	free_blabla(int x, int j)
{
	(void) x;
	(void) j;
}

void debug_map(t_data *d)
{
	int	i = 0;
	int	j;
	printf("height %d\n", d->map->height);
	while(d->map->height > i)
	{
		j = 0;
		printf("%s\n", d->map->map[i]);
		i++;
	}
}
