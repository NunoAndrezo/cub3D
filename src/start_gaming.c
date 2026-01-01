#include "../inc/cub3d.h"

static int	main_loop(t_game *game);
static void	update_player(t_game *game);
static int	game_loop(t_game *game);

void	start_gaming(t_game *game)
{
	mlx_loop_hook(game->mlx_struct, main_loop, game);
	mlx_loop(game->mlx_struct);
}

int	main_loop(t_game *game)
{
	uint64_t		current_time;
	uint64_t		elapsed;
	uint64_t		accu;

	// reduce accumulator to ~2ms for ~500Hz updates
	accu = 0;
	current_time = get_time_in_ms();
	elapsed = current_time - game->start_time;
	game->start_time = current_time;
	game->delta_time = elapsed;
	accu += elapsed;
	// Update game state at fixed intervals (~16 ms => ~60 updates/sec), explaining the math: 16 ms per update means 1000 ms / 16 ms = 62.5 updates per second
	while (accu >= 16)
	{
		update_player(game);
		accu -= 16;
	}
	game_loop(game);
	return (0);
}

static void update_player(t_game *game)
{
	change_player_rot(game);
	change_player_mov(game);
}

static int game_loop(t_game *game)
{
	size_t row_bytes;

	row_bytes = (size_t)game->image.line_length * (size_t)game->image.height;
	if (game->bg_image.img_pixels_ptr && game->image.img_pixels_ptr)
		ft_memcpy(game->image.img_pixels_ptr, game->bg_image.img_pixels_ptr, row_bytes);
	draw_player(game);
	lets_see_them_rays(game);
	mlx_put_image_to_window(game->mlx_struct, game->win_struct, game->image.img_ptr, 0, 0);
	return (0);
}
