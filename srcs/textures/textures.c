#include "cub3d.h"

int	list_texture_compare(void *value1, void *value2)
{
	t_texture	*elem_1;
	t_texture	*elem_2;
	int 	result;

	elem_1 = (t_texture *) value1;
	elem_2 = (t_texture *) value2;

	result = ft_strcmp(elem_1->id, elem_2->id);
	if (result > 0)
		return (1);
	if (0 > result)
		return (-1);
	return (0);
}

void	list_texture_delete(void *content)
{
	t_texture	*elem;

	elem = (t_texture *) content;
	free(elem->image);
	free(elem->utils);
	free(elem);
}


t_texture *init_texture(t_screen *screen, char *id, char *file)
{
	t_texture	*texture;

	texture = ft_calloc(sizeof(t_texture), 1);
	if (!texture)
		return (NULL);
	texture->id = id;
	texture->image = ft_calloc(sizeof(t_image), 1);
	if (!texture->image)
	{
		free(texture);
		return (NULL);
	}
	texture->utils = ft_calloc(sizeof(t_screen_utils), 1);
	if (!texture->utils)
	{
		free(texture->image);
		free(texture);
		return (NULL);
	}
	texture->image->holder = mlx_xpm_file_to_image(screen->holder, file, &texture->width, &texture->height);
	texture->image->addr = mlx_get_data_addr(texture->image->holder, &texture->utils->bits_per_pixel, &texture->utils->line_length, &texture->utils->endian);
	return (texture);
}

t_list	*init_load_textures(t_data *d)
{
	t_list	*textures;

	textures = list_create(1);
	if (!textures)
		return (NULL);
	textures->compare_func = list_texture_compare;
	textures->del_elem_func = list_texture_delete;
	if (!list_add_value(textures, list_create_elem(init_texture(d->game->screen, ft_strdup("NO") ,d->tex->no)), -1) ||
		!list_add_value(textures, list_create_elem(init_texture(d->game->screen, ft_strdup("SO"), d->tex->so)), -1) ||
		!list_add_value(textures, list_create_elem(init_texture(d->game->screen, ft_strdup("EA"), d->tex->ea)), -1) ||
		!list_add_value(textures, list_create_elem(init_texture(d->game->screen, ft_strdup("WE"), d->tex->we)), -1)
	)
	{
		list_delete(textures);
		return (NULL);
	}
	return (textures);
}
