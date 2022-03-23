#include <cub3d.h>

static int	set_texture_x(t_rays *values, t_game *game)
{
	int texture_x;
	double wall_x;

	if (values->hit_side == 0)
	{
		if (values->ray_dir.x > 0)
			wall_x = fabs(game->player.pos.y + values->perp_wall  * \
			values->ray_dir.y);
		else
			wall_x = fabs(game->player.pos.y - values->perp_wall  * \
			values->ray_dir.y);
	}
	else
	{
		if (values->ray_dir.y > 0)
			wall_x = fabs(game->player.pos.x + values->perp_wall  * \
			values->ray_dir.x);
		else
			wall_x = fabs(game->player.pos.x - values->perp_wall  * \
			values->ray_dir.x);
	}
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * (double)BLOCK_SIZE);
	texture_x = solve_mirroring(texture_x, values);
	return (texture_x);
}

static void	render_3d(t_texture *text, t_rays *values, t_game *game)
{
	int index;
	int color;

	index = text->start_line;
	while (index < text->end_line)
	{
		text->texture_y = (int)text->texture_pos & (64 - 1);
		text->texture_pos += text->step;
		color = get_pixel(text->data, (t_vec){.x = text->texture_x, \
		.y = text->texture_y});
		if (values->hit_side == 1)
			color = get_color_shade(color, 0.6);
		draw_pixel(&game->resources.canvas, (t_vec){.x = values->rays, \
		.y = index}, color);
		index++;
	}
}

static void	render_last_set(t_texture *text, t_rays *values, t_game *game)
{
	text->texture_x = set_texture_x(values, game);
	text->step = 1.0 * 64 / text->line_height;
	text->texture_pos = (text->start_line - screenHeight /2 + \
	text->line_height / 2) * text->step;
	text->data = get_texture(game, values);
	render_3d(text, values, game);
}

void	render_engine(t_rays *values, t_game *game)
{
	t_texture text;

	set_perp_wall(values, game);
	text.line_height = abs(screenHeight / values->perp_wall);
	text.start_line= -text.line_height / 2 + screenHeight / 2;
	if(text.start_line< 0)
		text.start_line= 0;
	text.end_line = text.line_height / 2 + screenHeight / 2;
	if(text.end_line >= screenHeight)
		text.end_line = screenHeight - 1;
	render_last_set(&text, values, game);
}
