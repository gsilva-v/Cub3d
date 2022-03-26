#include <cub3d.h>

void fps(t_game *game)
{

	static float second;
	static int	frame;

	game->elapsed_time = passed_time(game->last_time);
	second += game->elapsed_time;
	game->last_time = current_time();
	frame++;
	if (second >= 1)
	{
		char *buffer;
		buffer =  ft_itoa(frame);
		write (1, buffer, ft_strlen(buffer));
		write(1, "\n", 1);
		frame = 0;
		second = 0;
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
	r->pov.img = mlx_xpm_file_to_image(game->mlx, POV, \
	&trash, &trash);
	r->pov.addr = mlx_get_data_addr(r->pov.img, &r->pov.bits_per_pixel, \
	&r->pov.line_length, &r->pov.endian);
	load_block(game, &r->wall);
	r->door.so.name = ft_strdup("./imgs/door.xpm");
	r->door.no.name = ft_strdup("./imgs/door.xpm");
	r->door.we.name = ft_strdup("./imgs/door.xpm");
	r->door.ea.name = ft_strdup("./imgs/door.xpm");
	load_block(game, &r->door);
	r->open_door.so.name = ft_strdup("./imgs/so_redbrick.xpm");
	r->open_door.no.name = ft_strdup("./imgs/no_redbrick.xpm");
	r->open_door.we.name = ft_strdup("./imgs/we_redbrick.xpm");
	r->open_door.ea.name = ft_strdup("./imgs/ea_redbrick.xpm");
	load_block(game, &r->open_door);
}
