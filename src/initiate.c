#include "../inc/cub3d.h"

static int	key_press(int keycode, t_game *game);

void	initiate_and_allocate(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		perror("mlx_init failed");
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, 1000, 500, "Cub3D");
	if (!game->win)
	{
		perror("mlx_new_window failed");
		exit(1);
	}
	mlx_hook(game->win, 2, 1L<<0, key_press, &game); // this one im using event 2 = key press
	//mlx_key_hook(game->win, key_press, &game); this one is an alias of mlx_hook on key up event (3). 
	mlx_loop(game->mlx);
/*	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
	(void)mlx_win;*/
}

static int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307) // ESC key = destroy window and exit
		mlx_destroy_window(game->mlx, game->win);
	
	return (0);
}