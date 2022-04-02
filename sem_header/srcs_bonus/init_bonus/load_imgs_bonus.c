#include <cub3d_bonus.h>

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

void	load_minimap(t_game *game)
{
	int		width;
	int		height;
	t_data	*d;

	d = &game->resources.map;
	width = get_higher_len(game->map) * MBS;
	height = matrix_len(game->map) * MBS;
	if (width < 100)
		width = 100;
	if (height < 100)
		height = 100;
	d->img = mlx_new_image(game->mlx, width, height);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->line_len, &d->endian);
	clean_minimap(game);
	draw_map(game);
}

void	load_canvas(t_game *game)
{
	t_data	*d;

	d = &game->resources.canvas;
	d->img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->line_len, &d->endian);
}

void	load_sprite(t_game *game)
{
	t_data	*d;

	d = &game->final.sprite;
	d->img = mlx_xpm_file_to_image(game->mlx, "./imgs/monkey.xpm", \
	&d->width, &d->height);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->line_len, &d->endian);
	if (game->ghost)
	{
		d = &game->resources.g_sprite;
		d->img = mlx_xpm_file_to_image(game->mlx, "./imgs/ghost5.xpm", \
		&d->width, &d->height);
		d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->line_len, &d->endian);
	}
	d = &game->resources.floor;
	d->img = mlx_xpm_file_to_image(game->mlx, "./imgs/floor_1.xpm", \
	&d->width, &d->height);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->line_len, &d->endian);
}

void	load_imgs(t_game *game)
{
	t_resource	*r;

	r = &game->resources;
	load_canvas(game);
	load_minimap(game);
	if (game->ghost)
		init_animation(game, &game->resources.g_animation, "./imgs/ghost", 5);
	load_sprite(game);
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
