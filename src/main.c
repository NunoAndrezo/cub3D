#include "../inc/cub3d.h"

int main(int ac, char **av)
{
	t_game	game;

	parse(ac, av);
	setup_signals();
	ft_bzero(&game, sizeof(t_game));
	handle_map(av[1], &game);
	if (map_is_valid(&game) == true && last_map_adjustments(&game))
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

// need to implement window resizing? if so, how to handle the image buffer resizing? simple, destroy and recreate it? what about aspect ratio? simple, just scale the image to fit the new window size, even if it distorts a bit
// what about resizing the window while the game is running? should be handled in the main loop. how? simple, check for window size changes and recreate the image buffer if needed