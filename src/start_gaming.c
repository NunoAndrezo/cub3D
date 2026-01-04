/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_gaming.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:08:15 by nuno              #+#    #+#             */
/*   Updated: 2026/01/04 21:41:52 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	uint64_t	frame_start;
	uint64_t	frame_end;
	uint64_t	elapsed;
	const uint64_t target_frame_ms = 16; /* ~60 FPS */

	/* frame timing: compute elapsed since last frame (ms) */
	frame_start = get_time_in_ms();
	elapsed = frame_start - game->start_time;
	if (elapsed == 0)
		elapsed = 1; /* avoid zero delta */
	game->start_time = frame_start;
	game->delta_time = elapsed;

	/* update once per frame using delta time (ms) so movement is frame-rate independent */
	update_player(game);
	game_loop(game);

	/* simple frame cap to smooth presentation: sleep remaining time to target ~60 FPS */
	frame_end = get_time_in_ms();
	uint64_t frame_time = frame_end - frame_start;
	if (frame_time < target_frame_ms)
		usleep((target_frame_ms - frame_time) * 1000);
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
