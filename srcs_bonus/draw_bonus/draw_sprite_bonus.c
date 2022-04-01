#include <cub3d_bonus.h>

void	set_project(t_sprite *sprite, t_vec pos, t_game *game)
{
	t_vec	p_dir;

	p_dir = game->player.direction;
// checar a distancia entre a sprite e o player
	sprite->pos.x = pos.x - game->player.pos.x;
	sprite->pos.y = pos.y - game->player.pos.y;
// cria a projeção no mapa
	sprite->inv_delta = 1.0 / (game->player.plane.x * p_dir.y \
	- p_dir.x * game->player.plane.y);
	sprite->trans.x = sprite->inv_delta * (p_dir.y * \
	sprite->pos.x - p_dir.x * sprite->pos.y);
	sprite->trans.y = sprite->inv_delta * (-game->player.plane.y * \
	sprite->pos.x + game->player.plane.x * sprite->pos.y);
}

void	config_sprite(t_sprite *sprite)
{
	sprite->sprite_screen = (int)((SCREENWIDTH / 2) * (1 + \
	sprite->trans.x / sprite->trans.y));
	sprite->v_move_screen = (int)(VMOVE / sprite->trans.y);
	sprite->sprite_h = abs(((int)(SCREENHEIGHT / (sprite->trans.y)))) / VDIV;
	sprite->draw_start.y = -sprite->sprite_h / 2 + SCREENHEIGHT / 2 + \
	sprite->v_move_screen;
	if (sprite->draw_start.y < 0)
		sprite->draw_start.y = 0;
	sprite->draw_end.y = sprite->sprite_h / 2 + SCREENHEIGHT / 2 + \
	sprite->v_move_screen;
	if (sprite->draw_end.y >= SCREENHEIGHT)
		sprite->draw_end.y = SCREENHEIGHT - 1;
	sprite->sprite_w = abs((int)(SCREENHEIGHT / (sprite->trans.y))) / UDIV;
	sprite->draw_start.x = -sprite->sprite_w / 2 + sprite->sprite_screen;
	if (sprite->draw_start.x < 0)
		sprite->draw_start.x = 0;
	sprite->draw_end.x = sprite->sprite_w / 2 + sprite->sprite_screen;
	if (sprite->draw_end.x >= SCREENWIDTH)
		sprite->draw_end.x = SCREENWIDTH - 1;
}

void	put_sprite(t_sprite *sprite, t_game *game, t_data *text, t_int_vec st)
{
	int		d;
	int		c;
	int		is_transparence;
	t_vec	aux;

	is_transparence = 0;
	aux = (t_vec){.y = st.y, .x = st.x};
	d = (st.y - sprite->v_move_screen) * 256 - SCREENHEIGHT * 127 + \
	sprite->sprite_h * 128;
	sprite->text.y = ((d * text->height) / sprite->sprite_h) / 256;
	c = get_pixel(text, (t_vec){.x = sprite->text.x, .y = sprite->text.y});
	if (c == 0xff00ff)
		is_transparence = 1;
	c = reshade(c);
	c = lamp(aux, game, c, sprite->trans.y);
	if (!is_transparence)
		draw_pixel(&game->resources.canvas, aux, c);
}

void	draw_sprite(t_game *game, t_vec pos, t_data *text)
{
	t_sprite	sprite;
	t_int_vec	stripe;

// // checar a distancia entre a sprite e o player
	set_project(&sprite, pos, game);
// cria a sprite com o tamanho dependendo da projeção criada
	config_sprite(&sprite);
	stripe.x = sprite.draw_start.x;
// desenha a sprite
	while (stripe.x < sprite.draw_end.x)
	{
		sprite.text.x = ((int)(256 * (stripe.x - (-sprite.sprite_w / 2 + \
		sprite.sprite_screen)) * text->width / sprite.sprite_w)) / 256;
		if (sprite.trans.y > 0 && stripe.x > 0 && stripe.x < SCREENWIDTH
			&& sprite.trans.y < fabs(game->z_buffer[stripe.x]))
		{
			stripe.y = sprite.draw_start.y;
			while (stripe.y < sprite.draw_end.y)
			{
				put_sprite(&sprite, game, text, stripe);
				stripe.y++;
			}
		}
		stripe.x++;
	}
}
