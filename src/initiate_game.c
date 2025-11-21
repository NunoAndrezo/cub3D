#include "../inc/cub3d.h"

static int	key_press(int key_sym, void *param);
static int	button_x_on_window(void *param);

void	initiate_mlx(t_game *game)
{
	game->mlx_struct = mlx_init(); // Create a structure to hold minilibx info
	if (!game->mlx_struct)
	{
		perror("mlx_init failed");
		// we need a clean exit function here
		exit(1);
	}
	game->win_w = WWIDTH;
	game->win_h = WHEIGHT;
	if (WWIDTH > 1920 || WWIDTH <= 0)
		game->win_w = 1920;
	if (WHEIGHT > 1000 || WHEIGHT <= 0)
		game->win_h = 1000;
	game->win_struct = mlx_new_window(game->mlx_struct, game->win_w, game->win_h, "Cub3D"); // Create a structure to hold window info
	if (!game->win_struct)
	{
		perror("mlx_new_window failed");
		// we need a clean exit function here
		exit(1);
	}
	mlx_hook(game->win_struct, 2, 1L<<0, key_press, game); // key press. 1L<<0 mask, means KeyPress. 2 event means KeyPress
	mlx_hook(game->win_struct, 17, 1L<<0, button_x_on_window, game); // window close button (X) pressed - 17 event is DestroyNotify
	//mlx_hook(game->win_struct, 3, 1L<<1, key_press, game); // key release. 1L<<1 mask, means KeyRelease. 3 event means KeyRelease
	mlx_loop(game->mlx_struct); // function that keeps the window open and listens for events.
	//events: key presses, mouse movements, window close, etc.
}

// keysyms are better than keycodes for portability, because keycodes can vary between systems
static int	key_press(int key_sym, void *param)
{
	t_game *g = (t_game *)param;
	/* Global ESC behavior */
	if (key_sym == XK_Escape) // ESC key code == 65307, key_sym == XK_Escape == 0xff1b
	{
		free_game(g);
		exit(0);
	}
	return (0);
}

static int	button_x_on_window(void *param)
{
	t_game *g = (t_game *)param;
	free_game(g);
	exit(0);
	return (0);
}
