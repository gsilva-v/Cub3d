#include <cub3d.h>

int	open_xpm_file(t_data *data, t_game *game)
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

void	load_block(t_game *game, t_block *block)
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

void	load_imgs(t_game *game)
{
	int			trash;
	t_resource	*r;

	r = &game->resources;
	r->canvas.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	r->canvas.addr = mlx_get_data_addr(r->canvas.img, \
	&r->canvas.bits_per_pixel, &r->canvas.line_length, &r->canvas.endian);
	r->pov.img = mlx_xpm_file_to_image(game->mlx, "./imgs/pov.xpm", \
	&trash, &trash);
	r->pov.addr = mlx_get_data_addr(r->pov.img, &r->pov.bits_per_pixel, \
	&r->pov.line_length, &r->pov.endian);
	load_block(game, &r->wall);
// G A M B I A R R A
	r->door = r->wall;
// G A M B I A R R A
	// load_block(game, &r->door);
}
