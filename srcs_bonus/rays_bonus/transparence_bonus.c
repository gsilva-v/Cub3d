#include <cub3d_bonus.h>

static void	one_dda(t_rays *values)
{
	if (values->dst_x < values->dst_y)
	{
		values->dst_x += values->dlt_x;
		values->map_pos.x += values->step_x;
		values->hit_side = 0;
	}
	else
	{
		values->dst_y += values->dlt_y;
		values->map_pos.y += values->step_y;
		values->hit_side = 1;
	}
}

static void	vertical_transparence(t_game *game, t_rays *values)
{
	if (values->dst_x < values->dst_y)
	{
		one_dda(values);
		game->is_open_door = 1;
		render_engine(values, game);
		game->is_open_door = 0;
	}
}

static void	horizontal_transparence(t_game *game, t_rays *values)
{
	if (values->dst_y < values->dst_x)
	{
		one_dda(values);
		game->is_open_door = 1;
		render_engine(values, game);
		game->is_open_door = 0;
	}
}

void	check_open_wall(t_game *game, t_rays *values)
{
	if (game->map[values->map_pos.y][values->map_pos.x] == OPEN_DOOR)
	{
		if (values->hit_side == 0)
			vertical_transparence(game, values);
		else if (values->hit_side == 1)
			horizontal_transparence(game, values);
		dda(values, game);
		render_engine(values, game);
	}
}
