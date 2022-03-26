#include <cub3d.h>

static int	open_xpm_file(t_data *data, t_game *game)
{
	int	trash;

	data->img = mlx_xpm_file_to_image(game->mlx, data->name, \
	&trash, &trash);
	if (!data->img)
		return (-1);
	data->addr = mlx_get_data_addr(data->img, \
	&data->bits_per_pixel, &data->line_length, &data->endian);
	return (0);
}

static void	load_block(t_game *game, t_block *block)
{
	if (open_xpm_file(&block->no, game))
		show_error(game, 1, "cannot open this image");
	if (open_xpm_file(&block->so, game))
		show_error(game, 1, "cannot open this image");
	if (open_xpm_file(&block->we, game))
		show_error(game, 1, "cannot open this image");
	if (open_xpm_file(&block->ea, game))
		show_error(game, 1, "cannot open this image");
}

int	get_higher_len(char **matrix)
{
	int	index;
	int	size;
	int	tmp;

	index = 0;
	size = 0;
	while (matrix[index])
	{
		tmp = ft_strlen(matrix[index]);
		if (tmp > size)
			size = tmp;
		index++;
	}
	return (size);
}

void	load_imgs(t_game *game)
{
	int			trash;
	t_resource	*r;

	r = &game->resources;
	r->canvas.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	r->canvas.addr = mlx_get_data_addr(r->canvas.img, \
	&r->canvas.bits_per_pixel, &r->canvas.line_length, &r->canvas.endian);


	r->map.img = mlx_new_image(game->mlx, get_higher_len(game->map) * MAP_BLOCK_SIZE, matrix_len(game->map) * MAP_BLOCK_SIZE);
	r->map.addr = mlx_get_data_addr(r->map.img, \
	&r->map.bits_per_pixel, &r->map.line_length, &r->map.endian);
	draw_map(game);

	r->pov.img = mlx_xpm_file_to_image(game->mlx, POV, \
	&trash, &trash);
	r->pov.addr = mlx_get_data_addr(r->pov.img, &r->pov.bits_per_pixel, \
	&r->pov.line_length, &r->pov.endian);
	load_block(game, &r->wall);
	r->door.so.name = ft_strdup("./imgs/closed_door.xpm");
	r->door.no.name = ft_strdup("./imgs/closed_door.xpm");
	r->door.we.name = ft_strdup("./imgs/closed_door.xpm");
	r->door.ea.name = ft_strdup("./imgs/closed_door.xpm");
	load_block(game, &r->door);
	r->open_door.so.name = ft_strdup("./imgs/opened_door.xpm");
	r->open_door.no.name = ft_strdup("./imgs/opened_door.xpm");
	r->open_door.we.name = ft_strdup("./imgs/opened_door.xpm");
	r->open_door.ea.name = ft_strdup("./imgs/opened_door.xpm");
	load_block(game, &r->open_door);
}
