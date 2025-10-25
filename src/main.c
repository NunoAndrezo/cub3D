#include "../inc/cub3d.h"

int main(int ac, char **av)
{
	t_game	game;

	parse(ac, av);
	game = ft_bzero(sizeof(t_game));
	handle_map(av[1], &game);
	
	return (0);
}