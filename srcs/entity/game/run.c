#include <cub3d.h>

int	press_key(int key_code, t_game *game)
{
	if (key_code == 'w')
		game->buttons.up = 1;
	if (key_code == 'a')
		game->buttons.left = 1;
	if (key_code == 's')
		game->buttons.down = 1;
	if (key_code == 'd')
		game->buttons.right = 1;
	if (key_code == ' ')
		game->buttons.function = 1;
	if (key_code == ESC)
		game->buttons.exit = 1;
	if (key_code == RIGHT_ARROW)
		game->buttons.rotate_right = 1;
	if (key_code == LEFT_ARROW)
		game->buttons.rotate_left = 1;
	if (key_code == SHIFT)
		game->buttons.acelerate = 1;
	if (key_code == 'f')
		game->buttons.light = 1;
	return (0);
}

int	release_key(int key_code, t_game *game)
{
	if (key_code == 'w')
		game->buttons.up = 0;
	if (key_code == 'a')
		game->buttons.left = 0;
	if (key_code == 's')
		game->buttons.down = 0;
	if (key_code == 'd')
		game->buttons.right = 0;
	if (key_code == ' ')
		game->buttons.function = 0;
	if (key_code == ESC)
		game->buttons.exit = 0;
	if (key_code == RIGHT_ARROW)
		game->buttons.rotate_right = 0;
	if (key_code == LEFT_ARROW)
		game->buttons.rotate_left = 0;
	if (key_code == SHIFT)
		game->buttons.acelerate = 0;
	if (key_code == 'f')
		game->buttons.light = 0;
	return (0);
}

int	enter_window(t_game *game)
{
	game->is_on_focus = 1;
}

int	leave_window(t_game *game)
{
	game->is_on_focus = 0;
}

int	rotate(int x, int y, t_game *game)
{
	int		move;
	t_int_vec	middle_screen;

	middle_screen = (t_int_vec){
		.x = SCREENWIDTH / 2,
		.y = SCREENHEIGHT / 2
	};
	move = x - middle_screen.x;
	if (x != middle_screen.x)
		game->player.rotate_cam = move / 5 * 0.08f; 
}

void	game_run(t_game *game)
{
	mlx_loop_hook(game->mlx, &game_render, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, press_key, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, release_key, game);
	mlx_hook(game->win, FocusIn, FocusChangeMask, enter_window, game);
	mlx_hook(game->win, FocusOut, FocusChangeMask, leave_window, game);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, rotate, game);
	mlx_hook(game->win, 17, 0L, red_cross, game);
	game->last_time = current_time();
	mlx_loop(game->mlx);
}
