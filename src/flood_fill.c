#include "../inc/cub3d.h"

static void allocate_map_for_flood_fill(char ***flood_fill_map, int y_max, t_game *game);
static void copy_map_for_flood_fill(t_game *game, char ***flood_fill_map, int y_max);
static bool	flood_fill_the_map(char **flood_fill_map, int start_x, int start_y, int y_max);
static void	free_flood_fill_map(char ***flood_fill_map, int y_max);

bool	flood_fill(t_game *game)
{
	bool	good_map;
	char	**flood_fill_map;

	good_map = false;
	flood_fill_map = NULL;
	copy_map_for_flood_fill(game, &flood_fill_map, game->map.y_max);
	good_map = flood_fill_the_map(flood_fill_map, game->map.player_start_x, game->map.player_start_y, game->map.y_max);
	free_flood_fill_map(&flood_fill_map, game->map.y_max);
	return (good_map);
}


static void copy_map_for_flood_fill(t_game *game, char ***flood_fill_map, int y_max)
{
	int		i;

	i = 0;
	allocate_map_for_flood_fill(flood_fill_map, y_max, game);
	while (i < y_max)
	{
		(*flood_fill_map)[i] = ft_strdup(game->map.map[i]);
		if (!(*flood_fill_map)[i])
		{
			perror("Error\nMemory allocation failed while copying map for flood fill\n");
			free_flood_fill_map(flood_fill_map, y_max);
			free_game(game);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void allocate_map_for_flood_fill(char ***flood_fill_map, int y_max, t_game *game)
{
	*flood_fill_map = (char **)ft_calloc((y_max + 1), sizeof(char *));
	if (!*flood_fill_map)
	{
		perror("Error\nMemory allocation failed for flood fill map\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	(*flood_fill_map)[y_max] = NULL;
}

static bool	flood_fill_the_map(char **flood_fill_map, int start_x, int start_y, int y_max)
{
	int	x;
	int	y;

	x = start_x;
	y = start_y;
	if (y < 0 || y >= y_max)
		return (0);
	if (!flood_fill_map[y])
		return (0);
	if (x < 0 || x >= (int)ft_strlen(flood_fill_map[y]))
		return (0);
	if (flood_fill_map[y][x] == ' ')
		return (0);
	if (flood_fill_map[y][x] == '1' || flood_fill_map[y][x] == 'V')
		return (1);
	flood_fill_map[y][x] = 'V';
	if (!flood_fill_the_map(flood_fill_map, x + 1, y, y_max))
		return (0);
	if (!flood_fill_the_map(flood_fill_map, x - 1, y, y_max))
		return (0);
	if (!flood_fill_the_map(flood_fill_map, x, y + 1, y_max))
		return (0);
	if (!flood_fill_the_map(flood_fill_map, x, y - 1, y_max))
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
