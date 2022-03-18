#include <cub3d.h>

int    take_step(float dx, float dy)
{
    if (dx < 0)
        dx *= -1;
    if (dy < 0)
        dy *= -1;
    return (dx > dy ? dx : dy);
}

void draw_line(t_vec vec1, t_vec vec2, int color, t_game *game)
{
    double    dx, dy, x, y;
    int        steps;
	t_vec point;

    dx=vec2.x-vec1.x;
    dy=vec2.y-vec1.y;
    

    x = vec1.x;
    y = vec1.y;

    steps = take_step(dx, dy);
    dx = (double) (dx / steps);
    dy = (double) (dy / steps);
    while (steps--)
    {
    
		point = (t_vec){.x = x, .y = y};
		draw_pixel(&game->canvas, point, color);
        x += dx;
        y += dy;
    }
}