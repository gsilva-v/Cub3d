#include <cub3d_bonus.h>


int get_previous_wall_x(t_game *game)
{
	int	index;

	index = 0;
	while (game->map[(int)game->player.pos.y][(int)game->player.pos.x - index] != WALL)
		index--;
	return (index);

}

int get_previous_wall_y(t_game *game)
{
	int	index;

	index = 0;
	while (game->map[(int)game->player.pos.y - index][(int)game->player.pos.x] != WALL)
		index--;
	return (index);

}



int	get_collum_len(int player_x, int player_y, char **map)
{
	int index;

	index = 0;
	while (map[player_y + index][player_x] != WALL)
		index++;

	printf("y index: %d\n", index);
	return (index);
}


int	get_next_wall_x(int player_x, int player_y, char **map)
{
	int index;

	index = 0;
	while (map[player_y ][player_x + index] != WALL)
		index++;
	printf("x index: %d\n", index);
	return (index);
}


void	watch_rotate(t_game *game)
{
	if (game->player.rotate_cam)
	{
		change_direction(game, game->player.rotate_cam * game->elapsed_time);
		change_plane(game, game->player.rotate_cam * game->elapsed_time);
		game->player.rotate_cam = 0;
	}
}

void	watch_walk(t_game *game)
{
	t_vec	velocity;
	float	movespeed;
	t_int_vec map_pos;

	movespeed = game->player.movespeed * game->elapsed_time;
	velocity = game->player.direction;
	if (game->buttons.up)
		vec_scale(&velocity, movespeed);
	else if (game->buttons.down)
		vec_scale(&velocity, -movespeed);
	else
		vec_scale(&velocity, 0);
	map_pos.x = (int)(velocity.x * 1.6f);
	map_pos.y = (int)(velocity.y * 1.6f);
	if(map_pos.y >= get_collum_len((int)game->player.pos.x, (int)game->player.pos.y, game->map) && velocity.y > 0)
		return ;
	if (map_pos.x >= get_next_wall_x((int)game->player.pos.x, (int)game->player.pos.y, game->map) && velocity.x > 0)
		return ;
	if (map_pos.x + game->player.pos.x <= get_previous_wall_x(game) && velocity.x < 0)
		return ;
	if (map_pos.y + game->player.pos.y <= get_previous_wall_y(game) && velocity.y < 0)
		return ;
	if (ft_char_in_set(game->map[(int)game->player.pos.y][(int)
			(game->player.pos.x + velocity.x * 1.6f)], "03"))
		move_cam_x(game, velocity);
	if (ft_char_in_set(game->map[(int)(game->player.pos.y + velocity.y * \
	1.6f)][(int)game->player.pos.x], "03"))
		move_cam_y(game, velocity);
}

void	watch_strafe(t_game *game)
{
	t_vec	strafe_vel;
	double	old_dir_x;
	t_int_vec map_pos;

	strafe_vel = game->player.direction;
	old_dir_x = strafe_vel.x;
	strafe_vel.x = strafe_vel.x * cos(PI / 2) - strafe_vel.y * sin(PI / 2);
	strafe_vel.y = old_dir_x * sin(PI / 2) + strafe_vel.y * cos(PI / 2);
	if (game->buttons.right)
		vec_scale(&strafe_vel, game->player.movespeed * game->elapsed_time);
	else if (game->buttons.left)
		vec_scale(&strafe_vel, -game->player.movespeed * game->elapsed_time);
	else
		vec_scale(&strafe_vel, 0);
	map_pos.x = (int)(strafe_vel.x * 1.6f);
	map_pos.y = (int)(strafe_vel.y * 1.6f);

	if(map_pos.y >= get_collum_len((int)game->player.pos.x, (int)game->player.pos.y, game->map) && strafe_vel.y > 0)
		return ;
	if (map_pos.x >= get_next_wall_x((int)game->player.pos.x, (int)game->player.pos.y, game->map) && strafe_vel.x > 0)
		return ;
	if (map_pos.x + game->player.pos.x <= get_previous_wall_x(game) && strafe_vel.x < 0)
		return ;
	if (map_pos.y + game->player.pos.y <= get_previous_wall_y(game) && strafe_vel.y < 0)
		return ;
	
	if (ft_char_in_set(game->map[(int)game->player.pos.y][(int)
			(game->player.pos.x + strafe_vel.x * 1.6f)], "03"))
		move_cam_x(game, strafe_vel);
		
	if (ft_char_in_set(game->map[(int)(game->player.pos.y + \
	strafe_vel.y * 1.6f)][(int)game->player.pos.x], "03"))
		move_cam_y(game, strafe_vel);
}

void	watch_functions(t_game *game)
{
	t_vec	pos;

	if (game->buttons.function)
	{
		pos = game->player.pos;
		pos.x += game->player.direction.x * 0.8;
		pos.y += game->player.direction.y * 0.8;
		if (game->map[(int)pos.y][(int)pos.x] == DOOR)
		{
			game->map[(int)pos.y][(int)pos.x] = OPEN_DOOR;
			game->buttons.function = 0;
		}
		else if (game->map[(int)pos.y][(int)pos.x] == OPEN_DOOR)
		{
			game->map[(int)pos.y][(int)pos.x] = DOOR;
			game->buttons.function = 0;
		}
	}
}
