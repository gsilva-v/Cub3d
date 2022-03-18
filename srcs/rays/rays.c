#include <cub3d.h>





void	draw_rays(t_game *game)
{
	for (int x = 0; x < game->width * 64; x++)
	{
		double cameraX = 2 *x / (double)(game->width * 64) - 1;
		double rayDirX = game->direction.x + game->plane.x * cameraX;
		double rayDirY = game->direction.y + game->plane.y * cameraX;
		//which box of the map we're in
		int mapX = (int)(game->player.x);
		int mapY = (int)(game->player.y);

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
			sideDistX = (game->player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.y) * deltaDistY;
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
			if (game->map[mapX][mapY] > 0) 
				hit = 1;
		}

		
		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		
		//Calculate height of line to draw on screen
		int lineHeight = (int)(game->height * 64 / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + game->height * 64 / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + game->height * 64 / 2;
		if(drawEnd >= game->height * 64)
			drawEnd = game->height * 64 - 1;
			
      //choose wall color
      int color;
      switch(game->map[mapX][mapY])
      {
        case 1:  color = 0XFF0000;  	break; //red
        case 2:  color = 0X00FF00;  	break; //red
        default: color = 0X0000FF;		break; //yellow
      }

      //give x and y sides different brightness
      if (side == 1){color = color / 2;}

      //draw the pixels of the stripe as a vertical line
      draw_line((t_vec){.x = x, .y = drawStart}, (t_vec){.x = x, .y = drawEnd}, color, game);
	}
}
