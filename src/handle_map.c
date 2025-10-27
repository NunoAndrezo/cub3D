#include "../inc/cub3d.h"

static int count_number_of_lines(t_game *game, char *map_file);

void handle_map(char *map_file, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	if (count_number_of_lines(game, map_file) <= 0)
		fprintf(stderr, "Error: Map file is empty\n"), exit(EXIT_FAILURE);
	i = 0;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		fprintf(stderr, "Error: Cannot open map file\n"), exit(EXIT_FAILURE);
	game->map.map = (char **)ft_calloc(sizeof(char *), (game->map.y + 1));
	game->map.map[game->map.y] = NULL;
	if (!game->map.map)
		fprintf(stderr, "Error: Memory allocation failed\n"), close(fd), exit(EXIT_FAILURE);
	line = get_next_line(fd);
	if (!line)
		fprintf(stderr, "Error: Empty or invalid map file\n"), close(fd), exit(EXIT_FAILURE);
	game->map.map[i++] = ft_strdup(line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!line)
			break ;
		game->map.map[i++] = ft_strdup(line);
	}
	close(fd);
}

static int count_number_of_lines(t_game *game, char *map_file)
{
	char	*line;
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		fprintf(stderr, "Error: Cannot open map file\n"), exit(EXIT_FAILURE);
	game->map.y = 0;
	line = get_next_line(fd);
	while (line)
	{
		game->map.y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (game->map.y);
}

// store map in game struct // allocate memory
// and then further processing (flood fill, collectibles, etc.)
// Now we gotta see if the map is valid and get its dimensions
// It doesn't have to be a rectangle.
// And there's also the walls to check and the player start position
// And flood fill to check if the map is closed and its playable

/*	if (valid_map(av[1], &game) == true)
	{
		flood_fill(&game);
		count_collectibles(&game);
		init_game(&game);
	}*/