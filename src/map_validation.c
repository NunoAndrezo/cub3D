#include "../inc/cub3d.h"

static bool	check_player(t_game *game);
static bool	is_map_playable(t_game *game);
static bool	flood_fill_the_map(t_game *game);

// It doesn't have to be a rectangle.
// And flood fill to check if the map is closed and its playable

bool	map_is_valid(t_game *game)
{
	//check for walls, valid characters, etc.
	if (check_player(game) && is_map_playable(game))
		return (true);
	return (false);
}

static bool	check_player(t_game *game)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	j = 0;
	player = 0;
	while (game->map.map[j])
	{
		i = 0;
		while (game->map.map[j][i])
		{
			if (game->map.map[j][i] == 'N' || game->map.map[j][i] == 'W' || game->map.map[j][i] == 'E' || game->map.map[j][i] == 'S')
			{
				player++;
				game->map.player_orientation = game->map.map[j][i];
			}
			i++;
		}
		j++;
	}
	if (player != 1)
		return (false);
	return (true);
}

static bool	is_map_playable(t_game *game)
{
	bool	is_playable;

	is_playable = flood_fill_the_map(game);
	return (is_playable);
}

static bool	flood_fill_the_map(t_game *game)
{
	int	x;
	int	y;

	x = game->map.x;
	y = game->map.y;

// Start flood fill from player's position
// I need to make an extra copy of the map to not modify the original one!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// out of bounds (line missing or shorter)
	if (y < 0 || !game->map.map[y] || x < 0 || x >= (int)ft_strlen(game->map.map[y]))
		return (0);

	// hit "outside" space — map not closed
	if (game->map.map[y][x] == ' ')
		return (0);

	// hit wall or already visited
	if (game->map.map[y][x] == '1' || game->map.map[y][x] == 'V')
		return (1);

	// mark visited
	game->map.map[y][x] = 'V';

	// recursively check all directions
	if (!flood_fill(game, x + 1, y))
		return (0);
	if (!flood_fill(game, x - 1, y))
		return (0);
	if (!flood_fill(game, x, y + 1))
		return (0);
	if (!flood_fill(game, x, y - 1))
		return (0);

	return (1);
}
