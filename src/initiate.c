#include "../inc/cub3d.h"

void	initiate_and_allocate(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1000, 500, "Cub3D");
	mlx_loop(game->mlx);
/*	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
	(void)mlx_win;*/
}