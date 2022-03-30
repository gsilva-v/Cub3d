#include <cub3d_bonus.h>

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


void	clean_minimap(t_game *game)
{
	int	col;
	int	line;

	col = 0;
	line = 0;
	while (line < matrix_len(game->map) * MBS)
	{
		col = 0;
		while (col < get_higher_len(game->map) * MBS)
		{
			draw_pixel(&game->resources.map, (t_vec){.x = col, \
				.y = line}, 0x0);
			col++;
		}
		line++;
	}
}

void	init_animation(t_game *game, t_animation *animation, char *name, int n_sprites)
{
	int		index;
	char	*tmp;
	char	*tmp2;

	index = 0;
	animation->index = 0;
	animation->sprites = ft_calloc(n_sprites, sizeof(t_data));
	animation->n_sprites = n_sprites;
	animation->seconds = 0.2f;
	while (index < n_sprites)
	{
		tmp2 = ft_itoa(index);
		tmp = ft_strjoin(ft_strdup(name), tmp2);
		free (tmp2);
		tmp = ft_strjoin(tmp, ".xpm");
		animation->sprites[index].img = mlx_xpm_file_to_image(game->mlx, tmp, \
		&animation->sprites[index].width, &animation->sprites[index].height);
		animation->sprites[index].addr = mlx_get_data_addr(animation->sprites[index].img, &animation->sprites[index].bits_per_pixel, \
		&animation->sprites[index].line_length, &animation->sprites[index].endian);
		free(tmp);
		index++;
	}
}


void	load_imgs(t_game *game)
{
	int			trash;
	t_resource	*r;

	r = &game->resources;
	r->canvas.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	r->canvas.addr = mlx_get_data_addr(r->canvas.img, \
	&r->canvas.bits_per_pixel, &r->canvas.line_length, &r->canvas.endian);


	r->map.img = mlx_new_image(game->mlx, get_higher_len(game->map) * MBS, matrix_len(game->map) * MBS);
	r->map.addr = mlx_get_data_addr(r->map.img, \
	&r->map.bits_per_pixel, &r->map.line_length, &r->map.endian);
	clean_minimap(game);
	draw_map(game);
	init_animation(game, &game->ghost.animation, "./imgs/ghost", 5);

	game->final.sprite.img = mlx_xpm_file_to_image(game->mlx, "./imgs/macaco.xpm", \
	&game->final.sprite.width, &game->final.sprite.height);
	game->final.sprite.addr = mlx_get_data_addr(game->final.sprite.img, &game->final.sprite.bits_per_pixel, \
	&game->final.sprite.line_length, &game->final.sprite.endian);

	game->ghost.sprite.img = mlx_xpm_file_to_image(game->mlx, "./imgs/ghost5.xpm", \
	&game->ghost.sprite.width, &game->ghost.sprite.height);
	game->ghost.sprite.addr = mlx_get_data_addr(game->ghost.sprite.img, &game->ghost.sprite.bits_per_pixel, \
	&game->ghost.sprite.line_length, &game->ghost.sprite.endian);
	

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
