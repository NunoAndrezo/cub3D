#include "../inc/cub3d.h"

void	initiate_and_allocate(t_game *game)
{
	ft_bzero(&game->map, sizeof(t_map));
	//ft_bzero(&game->window, sizeof(t_win));
}