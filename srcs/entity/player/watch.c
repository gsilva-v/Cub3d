#include <cub3d.h>

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


	movespeed = game->player.movespeed * game->elapsed_time;
	velocity = game->player.direction;
	if (game->buttons.up)

		vec_scale(&velocity, movespeed);
	else if (game->buttons.down)
		vec_scale(&velocity, -movespeed);
	else
		vec_scale(&velocity, 0);
	if (ft_char_in_set(game->map[(int)game->player.pos.y][(int)(game->player.pos.x + \
	velocity.x * 1.6f)], "03"))
		game->player.pos.x += velocity.x;
	if (ft_char_in_set(game->map[(int)(game->player.pos.y + velocity.y * \
	1.6f)][(int)game->player.pos.x], "03"))
		game->player.pos.y += velocity.y;
}

void	watch_strafe(t_game *game)
{
	t_vec	strafe_velocity;
	double	old_dir_x;

	strafe_velocity = game->player.direction;
	old_dir_x = strafe_velocity.x;
	strafe_velocity.x = strafe_velocity.x * cos(PI / 2) - \
	strafe_velocity.y * sin(PI / 2);
	strafe_velocity.y = old_dir_x * sin(PI / 2) + strafe_velocity.y * \
	cos(PI / 2);
	if (game->buttons.right)
		vec_scale(&strafe_velocity, game->player.movespeed * game->elapsed_time);
	else if (game->buttons.left)
		vec_scale(&strafe_velocity, -game->player.movespeed * game->elapsed_time);
	else
		vec_scale(&strafe_velocity, 0);
	if (ft_char_in_set(game->map[(int)game->player.pos.y][(int)(game->player.pos.x + \
	strafe_velocity.x * 1.6f)], "03"))
		game->player.pos.x += strafe_velocity.x;
	if (ft_char_in_set(game->map[(int)(game->player.pos.y + strafe_velocity.y * \
	1.6f)][(int)game->player.pos.x], "03"))
		game->player.pos.y += strafe_velocity.y;

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
	system("clear");
	for (int i = 0; game->map[i]; i++)
		printf("%s\n", game->map[i]);


}
