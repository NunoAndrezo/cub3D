#include "../inc/cub3d.h"

int main(int ac, char **av)
{
	t_game	game;

	parse(ac, av);
	ft_bzero(&game, sizeof(t_game));
	handle_map(av[1], &game);
	if (map_is_valid(&game) == true)
	{
		
	}
	
	return (0);
}
