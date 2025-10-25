#include "../inc/handle_map.h"

void handle_map(char *map)
{
	int		fd;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Error: Cannot open file\n");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	if (!line)
	{
		fprintf(stderr, "Error: Empty or invalid map file\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
/*	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	game->map_dimensions.y = 1;
	game->map_dimensions.x = get_len(line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!line)
			break ;
		if (game->map_dimensions.x != get_len(line))
		{
			write(2, "Error: Invalid number of columns\n", 34);
			(free(line), close(fd), exit(EXIT_FAILURE));
		}
		game->map_dimensions.y++;
	}
	close(fd);*/
/*	if (valid_map(av[1], &game) == true)
	{
		flood_fill(&game);
		count_collectibles(&game);
		init_game(&game);
	}*/
}