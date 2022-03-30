#include <cub3d_bonus.h>

void draw_sprite(t_game *game, t_vec pos, t_data *text)
{
	t_sprite	sprite;
	int stripe;
	int y;
	int	d;
	int	color;

// checar a distancia entre a sprite e o player
	sprite.pos.x = pos.x - game->player.pos.x;
	sprite.pos.y = pos.y - game->player.pos.y;
	
	if (game->sprite_pos.x - game->player.pos.x <= 0.2f && game->sprite_pos.y - game->player.pos.y <= 0.2f)
		game->lose = 1;

// cria a projeção no mapa
	sprite.inv_delta = 1.0 / (game->player.plane.x * game->player.direction.y \
	- game->player.direction.x * game->player.plane.y);
	sprite.transform.x = sprite.inv_delta * (game->player.direction.y * \
	sprite.pos.x - game->player.direction.x * sprite.pos.y);
	sprite.transform.y = sprite.inv_delta * (-game->player.plane.y * \
	sprite.pos.x + game->player.plane.x * sprite.pos.y);

// cria a sprite com o tamanho dependendo da projeção criada
	sprite.sprite_screen = (int)((SCREENWIDTH/2) * (1 + \
	sprite.transform.x/ sprite.transform.y));
	sprite.v_move_screen = (int)(VMOVE / sprite.transform.y);
	sprite.sprite_h = abs(((int)(SCREENHEIGHT / (sprite.transform.y)))) / VDIV;
	sprite.draw_start.y = -sprite.sprite_h / 2 + SCREENHEIGHT / 2 + \
	sprite.v_move_screen;
	if (sprite.draw_start.y < 0)
		sprite.draw_start.y = 0;
	sprite.draw_end.y = sprite.sprite_h / 2 + SCREENHEIGHT / 2 + \
	sprite.v_move_screen;
	if (sprite.draw_end.y >= SCREENHEIGHT)
		sprite.draw_end.y = SCREENHEIGHT - 1;
	sprite.sprite_w= abs((int)(SCREENHEIGHT / (sprite.transform.y))) / UDIV;
	sprite.draw_start.x = -sprite.sprite_w/ 2 + sprite.sprite_screen;
	if (sprite.draw_start.x < 0)
		sprite.draw_start.x = 0;
	sprite.draw_end.x = sprite.sprite_w/ 2 + sprite.sprite_screen;
	if (sprite.draw_end.x >= SCREENWIDTH)
		sprite.draw_end.x = SCREENWIDTH;
	stripe = sprite.draw_start.x;

// desenha a sprite
	while (stripe < sprite.draw_end.x)
	{
		sprite.text.x = ((int)(256 * (stripe - (-sprite.sprite_w/ 2 + \
		sprite.sprite_screen)) * text->width / sprite.sprite_w)) / 256;
		if(sprite.transform.y > 0 && stripe > 0 && stripe < SCREENWIDTH && \
		sprite.transform.y < fabs(game->z_buffer[stripe]))
		{
			y = sprite.draw_start.y;
			while (y < sprite.draw_end.y)
			{
				d = (y - sprite.v_move_screen) * 256 - SCREENHEIGHT * 127 + \
				sprite.sprite_h * 128;
				sprite.text.y = ((d * text->height) / sprite.sprite_h) / 256;
				get_and_draw(game,  (t_vec){.y = y, .x = stripe}, (t_vec){.x = 
					sprite.text.x, .y = sprite.text.y}, &game->resources.enemy);
				y++;
			}
		}
		stripe++;
	}
}
