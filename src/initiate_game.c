/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:07:25 by nuno              #+#    #+#             */
/*   Updated: 2026/01/06 03:20:11 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	initiate_mlx(t_game *game);
static void	initiate_window(t_game *game);
static void	initiate_image_buffer(t_game *game);
static void	initiate_player(t_game *game);

void	initiate_game(t_game *game)
{
	initiate_mlx(game);
	initiate_window(game);
	game->max_distance = sqrt((game->win_w * ONE_TILE_SIDE) * (game->win_w
				* ONE_TILE_SIDE) + (game->win_h * ONE_TILE_SIDE)
			* (game->win_h * ONE_TILE_SIDE));
	game->start_time = get_time_in_ms();
	initiate_player(game);
	ft_bzero(&game->ray, sizeof(t_ray));
	initiate_image_buffer(game);
	handle_mlx_events(game);
}

static void	initiate_mlx(t_game *game)
{
	game->mlx_struct = mlx_init();
	if (!game->mlx_struct)
	{
		perror("Error\nmlx_init failed");
		free_game(game);
		exit(1);
	}
}

static void	initiate_window(t_game *game)
{
	game->win_w = WWIDTH;
	game->win_h = WHEIGHT;
	if (WWIDTH > 1920 || WWIDTH <= 0)
		game->win_w = 1920;
	if (WHEIGHT > 1000 || WHEIGHT <= 0)
		game->win_h = 1000;
	game->win_struct = mlx_new_window(game->mlx_struct,
			game->win_w, game->win_h, "Cub3D");
	if (!game->win_struct)
	{
		perror("Error\nmlx_new_window failed");
		free_game(game);
		exit(1);
	}
}

static void	initiate_image_buffer(t_game *game)
{
	game->image.width = game->win_w;
	game->image.height = game->win_h;
	game->image.img_ptr = mlx_new_image(game->mlx_struct,
			game->win_w, game->win_h);
	game->image.bits_per_pixel = ONE_TILE_SIDE;
	game->image.img_pixels_ptr = mlx_get_data_addr(game->image.img_ptr,
			&game->image.bits_per_pixel, &game->image.line_length,
			&game->image.endian);
	game->bg_image.width = game->win_w;
	game->bg_image.height = game->win_h;
	game->bg_image.img_ptr = mlx_new_image(game->mlx_struct,
			game->win_w, game->win_h);
	game->bg_image.bits_per_pixel = ONE_TILE_SIDE;
	game->bg_image.img_pixels_ptr = mlx_get_data_addr(game->bg_image.img_ptr,
			&game->bg_image.bits_per_pixel, &game->bg_image.line_length,
			&game->bg_image.endian);
	draw_map_to_image(game, &game->bg_image);
}

static void	initiate_player(t_game *game)
{
	ft_bzero(&game->player, sizeof(t_player));
	game->player.pos_x = game->map.player_start_x + 0.5;
	game->player.pos_y = game->map.player_start_y + 0.5;
	game->player.dir = game->map.player_orientation;
	game->player.move_speed = (float)PLAYER_MOV_SPEED;
	game->player.player_speed_multiplier = 0.5f;
	game->player.player_rot_multiplier = 0.3f;
	set_player_angle(game);
	game->player.player_delta_x = -cosf(
			deg_to_rad(game->player.player_angle));
	game->player.player_delta_y = -sinf(
			deg_to_rad(game->player.player_angle));
	game->player.fov_degrees = 45.0f;
	game->ray.num_rays = 10;
}
