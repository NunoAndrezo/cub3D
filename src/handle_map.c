#include "../inc/cub3d.h"

void handle_map(char *map_file, t_game *game)
{

	// check map dimensions and validity
	// store map in game struct // allocate memory
	// further processing (flood fill, collectibles, etc.)
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Error: Cannot open map file\n");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	if (!line)
	{
		fprintf(stderr, "Error: Empty or invalid map file\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	// Now we gotta see if the map is valid and get its dimensions
	// It doesn't have to be a rectangle.
	// I want to store the different lines lenghts and check if its possible
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!line)
			break ;
		if (game->map.map_dim_x != get_len(line))
		{
			write(2, "Error: Invalid number of columns\n", 34);
			(free(line), close(fd), exit(EXIT_FAILURE));
		}
		game->map.map_dim_y++;
	}
	close(fd);
}


/*	if (valid_map(av[1], &game) == true)
	{
		flood_fill(&game);
		count_collectibles(&game);
		init_game(&game);
	}*/