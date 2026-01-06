/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player_mov_and_rot.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:07:22 by nuno              #+#    #+#             */
/*   Updated: 2026/01/05 04:06:37 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	is_colision(t_game *game, float nx, float ny);
static bool	check_diagonally_strafing(t_game *game);

void	change_player_rot(t_game *game)
{
	float		dt_seconds;
	float		rot_deg_per_update;
	const float	updates_per_sec = 1000.0f / 16.0f;
	float		rot_deg_per_sec;
	float		rot_delta_deg;

	dt_seconds = (float)game->delta_time / 1000.0f;
	rot_deg_per_update = rad_to_deg(0.07f);
	rot_deg_per_sec = rot_deg_per_update * updates_per_sec;
	rot_delta_deg = rot_deg_per_sec * dt_seconds;
	rot_delta_deg *= game->player.player_rot_multiplier;
	if (game->player.player_rot_left)
	{
		game->player.player_angle -= rot_delta_deg;
		if (game->player.player_angle < 0.0f)
			game->player.player_angle += 360.0f;
		game->player.player_delta_x = -cosf(deg_to_rad(game->player.player_angle));
		game->player.player_delta_y = -sinf(deg_to_rad(game->player.player_angle));
	}
	if (game->player.player_rot_right)
	{
		game->player.player_angle += rot_delta_deg;
		if (game->player.player_angle > 360.0f)
			game->player.player_angle -= 360.0f;
		game->player.player_delta_x = -cosf(deg_to_rad(game->player.player_angle));
		game->player.player_delta_y = -sinf(deg_to_rad(game->player.player_angle));
	}
}

void	change_player_mov(t_game *game)
{
	float		nx;
	float		ny;
	bool		strafing_diagonally;
	float		base_per_update;
	const float	updates_per_sec = 1000.0f / 16.0f;
	float		tiles_per_sec;
	float		dt;
	float		displacement;

	nx = game->player.pos_x;
	ny = game->player.pos_y;
	base_per_update = (float)PLAYER_MOV_SPEED / (float)ONE_TILE_SIDE;
	strafing_diagonally = check_diagonally_strafing(game);
	tiles_per_sec = base_per_update * updates_per_sec;
	dt = (float)game->delta_time / 1000.0f;
	displacement = tiles_per_sec * dt;
	displacement *= game->player.player_speed_multiplier;
	if (strafing_diagonally)
		displacement /= 1.4f;
	if (game->player.player_mov_left)
	{
		ny += game->player.player_delta_x * displacement;
		nx -= game->player.player_delta_y * displacement;
	}
	else if (game->player.player_mov_right)
	{
		ny -= game->player.player_delta_x * displacement;
		nx += game->player.player_delta_y * displacement;
	}
	if (game->player.player_mov_forward)
	{
		nx -= game->player.player_delta_x * displacement;
		ny -= game->player.player_delta_y * displacement;
	}
	else if (game->player.player_mov_backward)
	{
		nx += game->player.player_delta_x * displacement;
		ny += game->player.player_delta_y * displacement;
	}
	if (is_colision(game, nx, ny) == false)
	{
		game->player.pos_x = nx;
		game->player.pos_y = ny;
	}
}

static bool	check_diagonally_strafing(t_game *game)
{
	if (game->player.player_mov_forward && game->player.player_mov_left)
		return (true);
	if (game->player.player_mov_backward && game->player.player_mov_left)
		return (true);
	if (game->player.player_mov_forward && game->player.player_mov_right)
		return (true);
	if (game->player.player_mov_backward && game->player.player_mov_right)
		return (true);
	return (false);
}

static bool	is_colision(t_game *game, float nx, float ny)
{
	if (ny >= 0 && (int)ny < game->map.y_max
		&& nx >= 0 && (int)nx < (int)ft_strlen(game->map.map[(int)ny])
		&& game->map.map[(int)(ny)][(int)(nx)] != '1'
		&& game->map.map[(int)(ny)][(int)(nx)] != ' ')
	{
		return (false);
	}
	return (true);
}
