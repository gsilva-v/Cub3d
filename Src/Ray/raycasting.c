#include <ray.h>

/* void	raycasting(t_game *game)
{
	for (int x = 0; x < screenWidth; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
		double rayDirX = game->player.dir.x + game->plane.x * cameraX;
		double rayDirY = game->player.dir.y + game->plane.y * cameraX;


		//which box of the map we're in
		int mapX = (int)game->player.position.x;
		int mapY = (int)game->player.position.y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		
		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?




		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player.position.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.position.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player.position.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.position.y) * deltaDistY;
		}



		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (game->map[mapX][mapY] > 0)hit = 1;
		}


		 //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		

		//choose wall color
		int	color;
		switch(game->map[mapX][mapY])
		{
			case 1:  color = 0xFF0000;  break; //red
			case 2:  color = 0x00FF00;  break; //green
			case 3:  color = 0x0000FF;   break; //blue
			default: color = 0xFFFFFF; break; //yellow
		}

		//give x and y sides different brightness
		if (side == 1)
			color = color / 2;
		//draw the pixels of the stripe as a vertical line
		drawline((t_vec){.x = x, .y = drawStart}, (t_vec){.x = x, .y = drawEnd}, color, &game->server);
	}
}
 */

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_color_shade(int color, double qnt_shade)
{
	int	r;
	int	g;
	int	b;

	r = ((color & (0xFF << 16)) >> 16) * qnt_shade;
	g = ((color & (0xFF << 8)) >> 8) * qnt_shade;
	b = (color & 0xFF) * qnt_shade;
	return (create_rgb(r, g, b));
}


void	raycasting(t_game *game)
{
	//Iremos soltar raios da mesma quantidade da largura da tela
	for (int x = 0; x < screenWidth; x++)
	{
		//a escala do raio pode ir de -1 a 1
		double	multiplier = 2 * x / (double)screenWidth - 1;
		// a onde no nosso plane que representa nossa tela o raio atual esta batento
		t_vec	cameraPixel = game->plane;
		vec_scale(&cameraPixel, multiplier);
		
		//Vector que representa aonde no plane esta ray atual
		t_vec	rayDir = game->player.dir;
		vec_sum(&rayDir, &cameraPixel);

//		vec_magnitude(&rayDir);

		//Distancia de um x para o outro
		double	deltaDistX = rayDir.x == 0 ? 100000000 :  fabs(1 / rayDir.x);

		//Distancia de um Y para o outro
		double	deltaDistY = rayDir.y == 0 ? 100000000 : fabs(1 / rayDir.y);


		//Bloco onde o personagem esta
		t_ivec	mapPos;

		mapPos.x = (int) game->player.position.x;
		mapPos.y = (int) game->player.position.y;


		//primeira distancia ate encontrar o primeiro x
		double	distToSideX;
		//primeira distancia ate encontrar o primeiro y
		double	distToSideY;

		//direção a onde o x do mapa vai se mover
		int	stepX;
		//direção a onde o y do mapa vai se mover
		int	stepY;



		if (rayDir.x < 0)
		{
			distToSideX = (game->player.position.x - mapPos.x) * deltaDistX;
			stepX = -1;
		}
		else
		{
			distToSideX = (mapPos.x + 1 - game->player.position.x) * deltaDistX;
			stepX = 1;
		}


		if (rayDir.y < 0)
		{
			distToSideY = (game->player.position.y - mapPos.y) * deltaDistY;
			stepY = -1;
		}
		else
		{
			distToSideY = (mapPos.y + 1 - game->player.position.y) * deltaDistY;
			stepY  = 1;
		}


		//Bateu na parede
		int		hit = 0;
		double	ddaLineSizeX = distToSideX;
		double	ddaLineSizeY = distToSideY;
		
		// posição onde achou a parede

		//lado que bateu
		int		side;



		while (game->map[mapPos.y][mapPos.x] == 0)
		{
			if (ddaLineSizeX < ddaLineSizeY)
			{
				mapPos.x += stepX;
				ddaLineSizeX += deltaDistX;
				side = 0;
			}
			else
			{
				mapPos.y += stepY;
				ddaLineSizeY += deltaDistY;
				side = 1;
			}
		}

		//-1 = 1, 1 = 0
		double	perpendicularDist;

		//Distancia Perpendicular do player ate a parede
		if (side == 0)
			perpendicularDist = fabs((mapPos.x - game->player.position.x + ((1 - stepX) / 2))) / rayDir.x;
		else
			perpendicularDist = fabs((mapPos.y - game->player.position.y + ((1 - stepY) / 2))) / rayDir.y;


		int wallLineHeight = abs(screenHeight / perpendicularDist);

		int	lineStartY = screenHeight / 2 - wallLineHeight / 2;
		int	lineEndY = screenHeight / 2 + wallLineHeight / 2;

		if(lineStartY < 0)
			lineStartY = 0;
		if(lineEndY >= screenHeight)
			lineEndY = screenHeight - 1;
		




		double wallX;
		if (side == 0)
		{
			if (rayDir.x > 0)
				wallX = fabs(game->player.position.y + perpendicularDist * rayDir.y);
			else
				wallX = fabs(game->player.position.y - perpendicularDist * rayDir.y);
		}
		else
		{
			if (rayDir.y > 0)
				wallX = fabs(game->player.position.x + perpendicularDist * rayDir.x);
			else
				wallX = fabs(game->player.position.x - perpendicularDist * rayDir.x);
		}

		wallX -= floor(wallX);

		int	textureX = (int)(wallX * (double)64);

		/* if(side == 0 && rayDir.x > 0) textureX = 64 - textureX - 1;
		if(side == 1 && rayDir.y < 0) textureX = 64 - textureX - 1; */

		int color;
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * 64 / wallLineHeight;
		// Starting texture coordinate
		double texPos = (lineStartY - screenHeight / 2 + wallLineHeight / 2) * step;
		for(int y = lineStartY; y< lineEndY; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (64 - 1);
			texPos += step;
			if (game->map[mapPos.y][mapPos.x] >= 2)
				color = get_pixel(&game->door, (t_vec){.x = textureX, .y = texY});
			else
				color = get_pixel(&game->wall, (t_vec){.x = textureX, .y = texY});
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			put_pixel(&game->server.canvas, (t_vec){.x = x, .y = y}, color);
		}
		//drawline((t_vec){.x = x, .y = lineStartY}, (t_vec){.x = x, .y = lineEndY}, color, &game->server);
	




	}
}
