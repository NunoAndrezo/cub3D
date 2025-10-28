#include "../inc/cub3d.h"

int main(int ac, char **av)
{
	t_game	game;

	parse(ac, av);
	setup_signals();
	ft_bzero(&game, sizeof(t_game));
	handle_map(av[1], &game);
	if (map_is_valid(&game) == true)
	{
		game.is_valid_to_start = true;
		initiate_and_allocate(&game); // initialize mlx, window, etc.
		//load_textures(&game); // load game textures
		//start_gaming(&game); //main game loop
	}
	else
	{
		game.is_valid_to_start = false;
		fprintf(stderr, "Error: Map validation failed. Cannot start the game.\n");
	}
	//free_game(&game); // free allocated memory
	return (0);
}
// need to implement freeing of memory and error handling later
// need to implement signals handling for graceful exit
// need to implement window resizing?
// need to implement user input handling