#include <cub3d.h>

int matrix_len(char **matrix)
{
	int	i; 

	i = 0;
	if (!matrix)
		return (-1);
	while (matrix[i])
		i++;
	return (i);
}