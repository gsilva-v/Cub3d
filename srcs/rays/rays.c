#include <cub3d.h>

int    create_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

int    get_color_shade(int color, double qnt_shade)
{
    int    r;
    int    g;
    int    b;

    r = ((color & (0xFF << 16)) >> 16) * qnt_shade;
    g = ((color & (0xFF << 8)) >> 8) * qnt_shade;
    b = (color & 0xFF) * qnt_shade;
    return (create_rgb(r, g, b));
}



void raycasting(t_game *game)
{
	t_rays values;

	values = init_values(game);
	while (values.rays < screenWidth)
	{
		// reset values
		values.multiplier = 2 * values.rays / (double)screenWidth - 1;
		values.camera_pixel = game->plane;
		vec_scale(&values.camera_pixel, values.multiplier);
		values.ray_dir = game->direction;
		vec_sum(&values.ray_dir, &values.camera_pixel);
		values.delta_x = 10000000;
		if (values.ray_dir.x != 0)
			values.delta_x = fabs(1/values.ray_dir.x);
		values.delta_y = 10000000;
		if (values.ray_dir.y != 0)
			values.delta_y = fabs(1/values.ray_dir.y);
		
		// calculo de distancias atuais
		values.map_pos.x = (int)game->player.x;
		values.map_pos.y = (int)game->player.y;
		if (values.ray_dir.x < 0)
		{
			values.step_x = -1;
			values.dist_x = (game->player.x - values.map_pos.x) * values.delta_x;
		}
		else
		{
			values.step_x = 1;
			values.dist_x = (values.map_pos.x + 1 - game->player.x) * values.delta_x;
		}
		
		if (values.ray_dir.y < 0)
		{
			values.step_y = -1;
			values.dist_y = (game->player.y - values.map_pos.y) * values.delta_y;
		}
		else
		{
			values.step_y = 1;
			values.dist_y = (values.map_pos.y + 1 - game->player.y) * values.delta_y;
		}
		
		// algoritmo DDA
		while (game->map[values.map_pos.y][values.map_pos.x] == 0)
		{
			if (values.dist_x < values.dist_y)
			{
				values.dist_x += values.delta_x;
				values.map_pos.x += values.step_x;
				values.hit_side = 0; //parede vertical
			}
			else
			{
				values.dist_y += values.delta_y;
				values.map_pos.y += values.step_y;
				values.hit_side = 1; //parede horizontal
			}
		}
		
		// calculo da perspectiva

		if (values.hit_side == 0)
			values.perp_wall = (fabs(values.map_pos.x - game->player.x + ((1 - values.step_x)/2)) / values.ray_dir.x);
		else
			values.perp_wall = (fabs(values.map_pos.y - game->player.y + ((1 - values.step_y)/2)) / values.ray_dir.y);
		
		// renderização da parede 
		values.line_height = abs(screenHeight / values.perp_wall);
		
		values.start_line = -values.line_height / 2 + screenHeight / 2;
		if(values.start_line < 0)
			values.start_line = 0;
		values.end_line = values.line_height / 2 + screenHeight / 2;
		if(values.end_line >= screenHeight)
			values.end_line = screenHeight - 1;
		values.color = get_color_shade(0xFF0000, 0.7);
		if (values.hit_side)
			values.color = get_color_shade(values.color, 0.7); 

		draw_line((t_vec){.x = values.rays, .y = values.start_line}, (t_vec){.x = values.rays, .y = values.end_line}, values.color, game);

		values.rays++;
	}




}



// void	raycasting(t_game *game)
// {
// 	for (int rays = 0; rays < screenWidth; rays++)
// 	{
// 		double multiplier = 2 * rays / (double)screenWidth - 1;
// // cria o plano
// 		t_vec camera_pixel = game->plane;
// 		vec_scale(&camera_pixel, multiplier);
// // direção atual raio
// 		t_vec ray_dir = game->direction;
// 		vec_sum(&ray_dir, &camera_pixel); 
// // calcular os deltas
// 		// vec_magnitude(&ray_dir);
// 		double deltaDistX = ray_dir.x == 0 ? 10000000 : fabs(1 / ray_dir.x);
// 		double deltaDistY = ray_dir.y == 0 ? 10000000 : fabs(1 / ray_dir.y);

// // calculando posição no mapa

// 		t_int_vec map_pos = (t_int_vec){
// 			.x = (int)game->player.x,
// 			.y = (int)game->player.y
// 		};

// // calculando a distancia ate a parede
// 		int stepX;
// 		int stepY;
// 	// linhas verticais
// 		double sideDistX;
// 		if (ray_dir.x < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (game->player.x - map_pos.x) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (map_pos.x + 1 - game->player.x) * deltaDistX;
// 		}

// 	// linhas horizontais
// 		double sideDistY;
// 		if (ray_dir.y < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (game->player.y - map_pos.y) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (map_pos.y + 1 - game->player.y) * deltaDistY;
// 		}

// // Algoritmo DDA
// 		int hit_side = 0;

// 		while (game->map[map_pos.y][map_pos.x] == 0)
// 		{
// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				map_pos.x += stepX;
// 				hit_side = 0;// em parede vertical 
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				map_pos.y += stepY;
// 				hit_side = 1;// em parede horizontal
// 			}
// 		}

// // calculo da proporção da parede
// 		double perpWallDist;
// 		if (hit_side == 0)
// 			perpWallDist = (fabs(map_pos.x - game->player.x + ((1 - stepX)/2)) / ray_dir.x);
// 		else
// 			perpWallDist = (fabs(map_pos.y - game->player.y + ((1 - stepY)/2)) / ray_dir.y);

// // Renderização da parede
// 		int lineHeight = abs(screenHeight / perpWallDist);
		
// 		int drawStart = -lineHeight / 2 + screenHeight / 2;
// 		if(drawStart < 0)
// 			drawStart = 0;
// 		int drawEnd = lineHeight / 2 + screenHeight / 2;
// 		if(drawEnd >= screenHeight)
// 			drawEnd = screenHeight - 1;

// 		int color = get_color_shade(0xFF0000, 0.7);
// 		if (hit_side)
// 			color = get_color_shade(color, 0.7); 

// 		draw_line((t_vec){.x = rays, .y = drawStart}, (t_vec){.x = rays, .y = drawEnd}, color, game);


// 	}

// }



// {
// 	t_rays	values;

// 	values = init_values(game);
// 	while (values.rays < 60)
// 	{
// 		values.disH = 1000000;
// 		values.disV = 1000000;
// 		values.doff = 0;
// 		set_rays_horizontal(&values, game);
// 		set_horizontal_walls(&values, game);
// 		values.doff = 0;
// 		set_rays_vertical(&values, game);
// 		set_vertical_walls(&values, game);
// 		set_distance(&values);
// 		draw_line((t_vec){.x = game->player.x, .y = game->player.y}, \
// 		(t_vec){.x = values.ray_vec.x, .y = values.ray_vec.y}, 0x00FF00, game);
// 		draw_3d(&values, game);
// 		values.ray_angle += DR;
// 		values.ray_angle = check_valid_pi(values.ray_angle);
// 		values.rays++;
// 	}
// }
