#include <ray.h>
#include <stdio.h>

void	draw_map(t_game *game)
{
	t_vec	point;
	t_vec	point_tranformed;

	point.x = 0;
	while (point.x < WIDTH)
	{
		point.y = 0;
		while (point.y < HEIGHT)
		{
			point_tranformed = point;
			vec_scale(&point_tranformed, BLOCK_SIZE);
			if (game->map[(int)point.y][(int)point.x] == 1)
				drawsquare(point_tranformed, BLOCK_SIZE - 2, 0xFFFFFF, &game->server);
			else if (game->map[(int)point.y][(int)point.x] == 2)
				drawsquare(point_tranformed, BLOCK_SIZE - 2, 0xFFFF, &game->server);
			else
				drawsquare(point_tranformed, BLOCK_SIZE - 2, 0x0, &game->server);
			point.y++;
		}
		point.x++;
	}
}