#include <cub3d_bonus.h>

static t_data	*get_direction(t_block *block, t_rays *values)
{
	if (values->hit_side == 0 && values->ray_dir.x > 0)
		return (&block->ea);
	if (values->hit_side == 0 && values->ray_dir.x < 0)
		return (&block->we);
	if (values->hit_side == 1 && values->ray_dir.y > 0)
		return (&block->so);
	if (values->hit_side == 1 && values->ray_dir.y < 0)
		return (&block->no);
	return ((t_data *)0);
}

t_data	*get_texture(t_game *game, t_rays *values)
{
	if (game->map[values->map_pos.y][values->map_pos.x] == WALL)
		return (get_direction(&game->resources.wall, values));
	if (game->map[values->map_pos.y][values->map_pos.x] == DOOR)
		return (get_direction(&game->resources.door, values));
	if (game->map[values->map_pos.y][values->map_pos.x] == OPEN_DOOR)
		return (get_direction(&game->resources.open_door, values));
	return ((t_data *)0);
}

void	set_perp_wall(t_rays *values, t_game *game)
{
	if (values->hit_side == 0)
		values->perp_wall = (fabs(values->map_pos.x - game->player.pos.x + \
		((1 - values->step_x) / 2)) / values->ray_dir.x);
	else
		values->perp_wall = (fabs(values->map_pos.y - game->player.pos.y + \
		((1 - values->step_y) / 2)) / values->ray_dir.y);
}

static int	is_full(char *c, int size)
{
	while (size)
	{
		size--;
		if (c[size] == 0)
			return (0);
	}
	return (1);
}

void	check_transparence(t_game *game, t_rays *values)
{
	if (game->map[values->map_pos.y][values->map_pos.x] \
	!= WALL && !is_full(game->buffer, SCREENHEIGHT))
	{
		if (values->dst_x < values->dst_y)
		{
			values->dst_x += values->dlt_x;
			values->map_pos.x += values->step_x;
			values->hit_side = 0; //parede vertical
		}
		else
		{
			values->dst_y += values->dlt_y;
			values->map_pos.y += values->step_y;
			values->hit_side = 1; //parede horizontal
		}
		dda(values, game);
		render_engine(values, game);
	}
}
