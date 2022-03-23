#include <cub3d.h>

t_data	*get_direction(t_block *block, t_rays *values)
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

int	solve_mirroring(int texture, t_rays *values)
{
	if(values->hit_side == 0 && values->ray_dir.x < 0)
		texture = 64 - texture - 1;
    if(values->hit_side == 1 && values->ray_dir.y > 0) 
		texture = 64 - texture - 1;
	return(texture);
}

