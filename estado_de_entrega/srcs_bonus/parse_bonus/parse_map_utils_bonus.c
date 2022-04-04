/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:28:19 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/04 09:16:42 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static char	*normalize_line(char *line, int size)
{
	int		index;
	char	*new_line;

	new_line = ft_calloc(size + 1, sizeof(char));
	ft_memset(new_line, WALL, size);
	index = 0;
	while (line[index])
	{
		new_line[index] = line[index];
		index++;
	}
	free(line);
	return (new_line);
}

void	normalize_map(t_game *game)
{
	int	index;
	int	size;

	size = get_higher_len(game->map);
	index = 0;
	while (game->map[index])
	{
		if (ft_strlen(game->map[index]) < size)
			game->map[index] = normalize_line(game->map[index], size);
		index++;
	}
}
