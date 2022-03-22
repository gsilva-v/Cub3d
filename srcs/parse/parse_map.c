#include <cub3d.h>

int	parse_map(t_game *game, char *file)
{
	int fd;
	char *line;
	char *map_str;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line && line[0] != 'C')
	{
		free(line);	
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	else
		return (1);
	line = get_next_line(fd);
	if (!line)
		return (1);
	map_str = ft_strdup("");
	int i = 0;
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (!ft_char_in_set(line[i], VALID_BLOCK))
				return (1);
			i++;
		}	
		map_str = ft_strjoin(map_str, line);
		free(line);
		line = get_next_line(fd);
	}
	game->map = ft_split(map_str, '\n');
	close(fd);
	free(map_str);
	return (0);
}