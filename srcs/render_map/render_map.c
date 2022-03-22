#include <cub3d.h>

int	update( t_game *game)
{
	
}

int	render_map(t_game *game)
{
	clean_map(game);
	update(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas.img, 0, 0);
}