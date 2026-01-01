#include "../inc/cub3d.h"

static int	key_press(int key_sym, t_game *game);
static int	key_release(int key_sym, t_game *game);
static int	button_x_on_window(void *param);

void	handle_mlx_events(t_game *game)
{
	mlx_hook(game->win_struct, 2, 1L<<0, key_press, game);
	mlx_hook(game->win_struct, 3, 1L<<1, key_release, game);
	mlx_hook(game->win_struct, 17, 1L<<0, button_x_on_window, game);
}

// keysymbolics are better than keycodes for portability, because keycodes can vary between systems since keycode is hardware specific
// whereas keysymol is more abstract and represents the actual character or function of the key
static int	key_press(int key_sym, t_game *game)
{
	if (key_sym == XK_Escape)
	{
		free_game(game);
		exit(0);
	}
	if (key_sym == XK_w)
		game->player.player_mov_forward = true;
	if (key_sym == XK_a)
		game->player.player_mov_left = true;
	if (key_sym == XK_s)
		game->player.player_mov_backward = true;
	if (key_sym == XK_d)
		game->player.player_mov_right = true;
	if (key_sym == XK_Left)
		game->player.player_rot_left = true;
	if (key_sym == XK_Right)
		game->player.player_rot_right = true;
	return (0);
}

static int	key_release(int key_sym, t_game *game)
{
	if (key_sym == XK_w)
		game->player.player_mov_forward = false;
	if (key_sym == XK_a)
		game->player.player_mov_left = false;
	if (key_sym == XK_s)
		game->player.player_mov_backward = false;
	if (key_sym == XK_d)
		game->player.player_mov_right = false;
	if (key_sym == XK_Left)
		game->player.player_rot_left = false;
	if (key_sym == XK_Right)
		game->player.player_rot_right = false;
	return (0);
}

static int	button_x_on_window(void *param)
{
	t_game *g = (t_game *)param;
	free_game(g);
	exit(0);
	return (0);
}