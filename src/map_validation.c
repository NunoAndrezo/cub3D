#include "../inc/cub3d.h"

static bool	check_player(t_game *game);
static bool	is_map_playable(t_game *game);
// It doesn't have to be a rectangle.
// And flood fill to check if the map is closed and its playable

bool	map_is_valid(t_game *game)
{
	//check for walls, valid characters, etc.
	if (check_player(game) && is_map_playable(game))
		return (true);
	fprintf(stderr, "Error: Map is invalid. Either Flood fill failed or player check failed\n");
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
				game->map.player_start_x = i;
				game->map.player_start_y = j;
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
	return (flood_fill(game));
}

bool last_map_adjustments(t_game *game)
{
	int	j;
	int	i;
	int	max_len;
	char *new_row;

	j = 0;
	max_len = 0;
	while (j < game->map.y_max)
	{
		i = 0;
		while (game->map.map[j][i])
			i++;
		if (i > max_len)
			max_len = i;
		j++;
	}
	j = 0;
	while (j < game->map.y_max)
	{
		i = 0;
		while (game->map.map[j][i])
		{
			if ((int)ft_strlen(game->map.map[j]) < max_len)
			{
				// pad with spaces
				while ((int)ft_strlen(game->map.map[j]) < max_len)
				{
					new_row = ft_strjoin_char(game->map.map[j], ' ');
					if (new_row == NULL)
						return (false);
					free(game->map.map[j]);
					game->map.map[j] = new_row;
				}
			}
			i++;
		}
		j++;
	}
	game->map.x_max = max_len;
	return (true);
}
