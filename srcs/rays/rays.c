#include <cub3d.h>


void	raycasting(t_game *game)
{
	for (int rays = 0; rays < screenWidth; rays++)
	{
		double multiplier = 2 * (rays / (double)screenWidth) - 1;
// cria o plano
		t_vec camera_pixel = game->plane;
		vec_scale(&camera_pixel, multiplier);
// direção atual raio
		t_vec ray_dir = game->direction;
		vec_sum(&ray_dir, &camera_pixel); 
// calcular os deltas
		// vec_magnitude(&ray_dir);

		double deltaDistX = ray_dir.x == 0 ? 10000000 : fabs(1 / ray_dir.x);
		double deltaDistY = ray_dir.y == 0 ? 10000000 : fabs(1 / ray_dir.y);

// calculando posição no mapa

		t_int_vec map_pos = (t_int_vec){
			.x = (int)game->player.x,
			.y = (int)game->player.y
		};

// calculando a distancia ate a parede
		int stepX;
		int stepY;
	// linhas verticais
		double sideDistX;
		if (ray_dir.x < 0)
		{
			stepX = -1;
			sideDistX = (game->player.x - map_pos.x) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (map_pos.x + 1 - game->player.x) * deltaDistX;
		}

	// linhas horizontais
		double sideDistY;
		if (ray_dir.x < 0)
		{
			stepY = -1;
			sideDistY = (game->player.y - map_pos.y) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (map_pos.y + 1 - game->player.y) * deltaDistY;
		}

// Algoritmo DDA
		int hit_side = 0;

		while (game->map[map_pos.y][map_pos.x] == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				map_pos.x += stepX;
				hit_side = 0;// em parede vertical 
			}
			else
			{
				sideDistY += deltaDistY;
				map_pos.y += stepY;
				hit_side = 1;// em parede horizontal
			}
		}

// calculo da proporção da parede
		int perpWallDist;
		if (hit_side == 0)
			perpWallDist = (fabs(map_pos.x - game->player.x + ((1 - stepX)/2)) / ray_dir.x);
		else
			perpWallDist = (fabs(map_pos.y - game->player.y + ((1 - stepY)/2)) / ray_dir.y);

// Renderização da parede
		int lineHeight =  abs(screenHeight / perpWallDist);
		
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		draw_line((t_vec){.x = rays, .y = drawStart}, (t_vec){.x = rays, .y = drawEnd}, 0xFF, game);


	}

}



// void	draw_rays(t_game *game)
// {
// 	for (int x = 0; x < game->width * 64; x++)
// 	{
// 		double cameraX = 2 *x / (double)(game->width * 64) - 1;
// 		double rayDirX = game->direction.x + game->plane.x * cameraX;
// 		double rayDirY = game->direction.y + game->plane.y * cameraX;
// 		//which box of the map we're in
// 		int mapX = (int)(game->player.x);
// 		int mapY = (int)(game->player.y);

// 		//length of ray from current position to next x or y-side
// 		double sideDistX;
// 		double sideDistY;

// 		//length of ray from one x or y-side to next x or y-side
// 		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
// 		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
// 		double perpWallDist;

// 		//what direction to step in x or y-direction (either +1 or -1)
// 		int stepX;
// 		int stepY;

// 		int hit = 0; //was there a wall hit?
// 		int side; //was a NS or a EW wall hit?
		
// 		//calculate step and initial sideDist
// 		if (rayDirX < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (game->player.x - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - game->player.x) * deltaDistX;
// 		}
// 		if (rayDirY < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (game->player.y - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - game->player.y) * deltaDistY;
// 		}
		
// 		//perform DDA
// 		while (game->map[mapX][mapY] == 0)
// 		{
// 			//jump to next map square, either in x-direction, or in y-direction
// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 		}

		
// 		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
// 		if(side == 0)
// 			perpWallDist = (sideDistX - deltaDistX);
// 		else
// 			perpWallDist = (sideDistY - deltaDistY);

		
// 		//Calculate height of line to draw on screen
// 		int lineHeight = (int)(game->height * 64 / perpWallDist);

// 		//calculate lowest and highest pixel to fill in current stripe
// 		int drawStart = -lineHeight / 2 + game->height * 64 / 2;
// 		if(drawStart < 0)
// 			drawStart = 0;
// 		int drawEnd = lineHeight / 2 + game->height * 64 / 2;
// 		if(drawEnd >= game->height * 64)
// 			drawEnd = game->height * 64 - 1;
			
//       //choose wall color
//       int color;
//       switch(game->map[mapX][mapY])
//       {
//         case 1:  color = 0XFF0000;  	break; //red
//         case 2:  color = 0X00FF00;  	break; //red
//         default: color = 0X0000FF;		break; //yellow
//       }

//       //give x and y sides different brightness
//       if (side == 1){color = color / 2;}

//       //draw the pixels of the stripe as a vertical line
//       draw_line((t_vec){.x = x, .y = drawStart}, (t_vec){.x = x, .y = drawEnd}, color, game);
// 	}
// }
