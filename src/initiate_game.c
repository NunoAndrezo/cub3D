#include "../inc/cub3d.h"

static int	key_press(int keycode, void *param);

void	initiate_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		perror("mlx_init failed");
		// we need a clean exit function here
		exit(1);
	}
	/* create window and store its size in the game struct */
	game->win_w = 1920;
	game->win_h = 1000;
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "Cub3D");
	if (!game->win)
	{
		perror("mlx_new_window failed");
		// we need a clean exit function here
		exit(1);
	}
	mlx_hook(game->win, 2, 1L<<0, key_press, game); // key press. 1L<<0 mask, means KeyPress. 2 event means KeyPress
	mlx_hook(game->win, 3, 1L<<1, key_press, game); // key release. 1L<<1 mask, means KeyRelease. 3 event means KeyRelease

/*	char *game_menu_image_path; game_menu_image_path = "assets/textures/game_menu1.xpm"; 
	mlx_clear_window(game->mlx, game->win); // clear window before drawing menu
	if (!game->menu_image.img_ptr)
	{
		game->menu_image.path = game_menu_image_path;
		game->menu_image.img_ptr = mlx_xpm_file_to_image(game->mlx, game->menu_image.path, &game->menu_image.w, &game->menu_image.h);
	}*/
	mlx_loop(game->mlx);
}

static int	key_press(int keycode, void *param)
{
	t_game *g = (t_game *)param;
	/* Global ESC behavior */
	if (keycode == 65307) /* ESC */
	{
		if (g->menu_image.img_ptr)
			mlx_destroy_image(g->mlx, g->menu_image.img_ptr);
		if (g->cursor.img_ptr)
			mlx_destroy_image(g->mlx, g->cursor.img_ptr);
		if (g->win)
			mlx_destroy_window(g->mlx, g->win);
		exit(0);
	}
	return (0);
}
