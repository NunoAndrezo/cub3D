#include "../inc/cub3d.h"

static void allocate_map_for_flood_fill(char ***flood_fill_map, int y_max);
static void copy_map_for_flood_fill(char *map_file, char ***flood_fill_map, int y_max);
static bool	flood_fill_the_map(char ***flood_fill_map, int start_x, int start_y);
static void	free_flood_fill_map(char ***flood_fill_map, int y_max);

bool	flood_fill(t_game *game)
{
	bool	good_map;
	char	**flood_fill_map;

	good_map = false;
	flood_fill_map = NULL;
	copy_map_for_flood_fill(game->map.map_file, &flood_fill_map, game->map.y_max);
	good_map = flood_fill_the_map(&flood_fill_map, game->map.player_start_x, game->map.player_start_y);
	free_flood_fill_map(&flood_fill_map, game->map.y_max);
	return (good_map);
}


static void copy_map_for_flood_fill(char *map_file, char ***flood_fill_map, int y_max)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	allocate_map_for_flood_fill(flood_fill_map, y_max);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		fprintf(stderr, "Error: Cannot open map file\n"), exit(EXIT_FAILURE);
	line = get_next_line(fd);
	if (!line)
		fprintf(stderr, "Error: Empty or invalid map file\n"), close(fd), exit(EXIT_FAILURE);
	(*flood_fill_map)[i++] = ft_strdup(line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!line)
			break ;
		(*flood_fill_map)[i++] = ft_strdup(line);
	}
	close(fd);
}

static void allocate_map_for_flood_fill(char ***flood_fill_map, int y_max)
{
	*flood_fill_map = (char **)ft_calloc(sizeof(char *), (y_max + 1));
	(*flood_fill_map)[y_max] = NULL;
	if (!*flood_fill_map)
	{
		fprintf(stderr, "Error: Memory allocation failed for flood fill map\n");
		//maybe free other stuff here
		exit(EXIT_FAILURE);
	}
}

static bool	flood_fill_the_map(char ***flood_fill_map, int start_x, int start_y)
{
	int	x;
	int	y;

	x = start_x;
	y = start_y;

// Start flood fill from player's position
// I need to make an extra copy of the map to not modify the original one!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// out of bounds (line missing or shorter)
	if (y < 0 || !(*flood_fill_map)[y] || x < 0 || x >= (int)ft_strlen((*flood_fill_map)[y]))
		return (0);

	// hit "outside" space — map not closed
	if ((*flood_fill_map)[y][x] == ' ')
		return (0);

	// hit wall or already visited
	if ((*flood_fill_map)[y][x] == '1' || (*flood_fill_map)[y][x] == 'V')
		return (1);

	// mark visited
	(*flood_fill_map)[y][x] = 'V';
	// recursively check all directions
	if (!flood_fill_the_map(flood_fill_map, x + 1, y))
		return (0);
	if (!flood_fill_the_map(flood_fill_map, x - 1, y))
		return (0);
	if (!flood_fill_the_map(flood_fill_map, x, y + 1))
		return (0);
	if (!flood_fill_the_map(flood_fill_map, x, y - 1))
		return (0);

	return (1);
}

static void	free_flood_fill_map(char ***flood_fill_map, int y_max)
{
	int	i;

	i = 0;
	if (!*flood_fill_map)
		return ;
	while (i < y_max)
	{
		free((*flood_fill_map)[i]);
		i++;
	}
	free(*flood_fill_map);
}
