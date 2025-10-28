#include "../inc/cub3d.h"

static int count_and_store_number_of_lines(t_game *game, char *map_file);
static void copy_map(char *map_file, t_game *game);
static void allocate_map(t_game *game);

void handle_map(char *map_file, t_game *game)
{
	ft_bzero(&game->map, sizeof(t_map)); // set map struct
	if (count_and_store_number_of_lines(game, map_file) <= 0)
		fprintf(stderr, "Error: Map file is empty\n"), exit(EXIT_FAILURE);
	copy_map(map_file, game);
}

static void copy_map(char *map_file, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	allocate_map(game);
	// need to see what I have to do white empty spaces or lines ? replace with 0 probably or 1 or i cut or ignore them
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		fprintf(stderr, "Error: Cannot open map file\n"), exit(EXIT_FAILURE);
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

static void allocate_map(t_game *game)
{
	game->map.map = (char **)ft_calloc(sizeof(char *), (game->map.y + 1));
	game->map.map[game->map.y] = NULL;
	if (!game->map.map)
	{
		fprintf(stderr, "Error: Memory allocation failed\n");
		//maybe free other stuff here
		exit(EXIT_FAILURE);
	}
}

static int count_and_store_number_of_lines(t_game *game, char *map_file)
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
