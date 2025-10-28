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
	if (game)
		return (true);
	return (false);
	// Placeholder for flood fill algorithm to check if the map is closed and playable
	// This function should implement the flood fill logic
	// For now, we will just return true
}