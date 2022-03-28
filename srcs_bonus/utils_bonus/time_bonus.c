#include <cub3d_bonus.h>

long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

double	passed_time(long time_started)
{
	return ((current_time() - time_started) / 1000.0f);
}
