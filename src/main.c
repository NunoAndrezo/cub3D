#include "../inc/cub3d.h"

static bool	check_max_dimensions(t_game *game);

int main(int ac, char **av)
{
	t_game	game;

	parse(ac, av);
	setup_signals();
	ft_bzero(&game, sizeof(t_game));
	handle_map(av[1], &game);
	if (map_is_valid(&game) == true && last_map_adjustments(&game) && check_max_dimensions(&game))
	{
		initiate_game(&game);
		load_game(&game);
		start_gaming(&game);
	}
	else
	{
		free_game(&game);
		perror("Error\nMap validation failed. Cannot start the game.\n");
		return (1);
	}
	free_game(&game);
	return (0);
}

static bool	check_max_dimensions(t_game *game)
{
	if (WWIDTH == 1920 && WHEIGHT == 1000)
	{
		if (game->map.x_max > 110 || game->map.y_max > 60 || (game->map.x_max <= 2 && game->map.y_max <= 2))
		{
			perror("Error\nMap dimensions exceed maximum allowed size of 110x50.\n");
			free_game(game);
			exit(EXIT_FAILURE);
		}
	}
	return (true);
}

// need to implement window resizing? if so, how to handle the image buffer resizing? simple, destroy and recreate it? what about aspect ratio? simple, just scale the image to fit the new window size, even if it distorts a bit
// what about resizing the window while the game is running? should be handled in the main loop. how? simple, check for window size changes and recreate the image buffer if needed