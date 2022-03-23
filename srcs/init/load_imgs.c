#include <cub3d.h>

void	load_block(t_game *game, t_block *block)
{
	int	trash;

	block->no.img = mlx_xpm_file_to_image(game->mlx, "./imgs/wall.xpm", \
	&trash, &trash);
	block->no.addr = mlx_get_data_addr(block->no.img, \
	&block->no.bits_per_pixel, &block->no.line_length, &block->no.endian);
	block->so.img = mlx_xpm_file_to_image(game->mlx, "./imgs/wall.xpm", \
	&trash, &trash);
	block->so.addr = mlx_get_data_addr(block->so.img, \
	&block->so.bits_per_pixel, &block->so.line_length, &block->so.endian);
	block->we.img = mlx_xpm_file_to_image(game->mlx, "./imgs/wall.xpm", \
	&trash, &trash);
	block->we.addr = mlx_get_data_addr(block->we.img, \
	&block->we.bits_per_pixel, &block->we.line_length, &block->we.endian);
	block->ea.img = mlx_xpm_file_to_image(game->mlx, "./imgs/wall.xpm", \
	&trash, &trash);
	block->ea.addr = mlx_get_data_addr(block->ea.img, \
	&block->ea.bits_per_pixel, &block->ea.line_length, &block->ea.endian);
}

void	load_imgs(t_game *game)
{
	int			trash;
	t_resource	*r;

	r = &game->resources;
	r->canvas.img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	r->canvas.addr = mlx_get_data_addr(r->canvas.img, \
	&r->canvas.bits_per_pixel, &r->canvas.line_length, &r->canvas.endian);
	r->pov.img = mlx_xpm_file_to_image(game->mlx, "./imgs/pov.xpm", \
	&trash, &trash);
	r->pov.addr = mlx_get_data_addr(r->pov.img, &r->pov.bits_per_pixel, \
	&r->pov.line_length, &r->pov.endian);
	load_block(game, &r->wall);
	load_block(game, &r->door);
}
