/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player_mov_and_rot.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:07:22 by nuno              #+#    #+#             */
/*   Updated: 2026/01/06 15:38:55 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	change_player_rot_helper(t_game *game, float *rot_delta_deg);
static void	change_player_mov_helper(t_game *game, float *nx,
				float *ny, float displacement);
static bool	check_diagonally_strafing(t_game *game);

void	change_player_rot(t_game *game)
{
	float		dt_seconds;
	float		rot_deg_per_update;
	float		rot_deg_per_sec;
	float		rot_delta_deg;
	const float	updates_per_sec = 1000.0f / 16.0f;

	dt_seconds = (float)game->delta_time / 1000.0f;
	rot_deg_per_update = rad_to_deg(0.07f);
	rot_deg_per_sec = rot_deg_per_update * updates_per_sec;
	rot_delta_deg = rot_deg_per_sec * dt_seconds;
	rot_delta_deg *= game->player.player_rot_multiplier;
	change_player_rot_helper(game, &rot_delta_deg);
}

static void	change_player_rot_helper(t_game *game, float *rot_delta_deg)
{
	if (game->player.player_rot_left)
	{
		game->player.player_angle -= *rot_delta_deg;
		if (game->player.player_angle < 0.0f)
			game->player.player_angle += 360.0f;
		game->player.player_delta_x = -cosf(
				deg_to_rad(game->player.player_angle));
		game->player.player_delta_y = -sinf(
				deg_to_rad(game->player.player_angle));
	}
	if (game->player.player_rot_right)
	{
		game->player.player_angle += *rot_delta_deg;
		if (game->player.player_angle > 360.0f)
			game->player.player_angle -= 360.0f;
		game->player.player_delta_x = -cosf(
				deg_to_rad(game->player.player_angle));
		game->player.player_delta_y = -sinf(
				deg_to_rad(game->player.player_angle));
	}
}

void	change_player_mov(t_game *game)
{
	float		nx;
	float		ny;
	bool		strafing_diagonally;
	float		displacement;
	t_cpm		c;

	initiate_cpm(&c);
	nx = game->player.pos_x;
	ny = game->player.pos_y;
	c.base_per_update = (float)PLAYER_MOV_SPEED / (float)ONE_TILE_SIDE;
	strafing_diagonally = check_diagonally_strafing(game);
	c.tiles_per_sec = c.base_per_update * c.updates_per_sec;
	c.dt = (float)game->delta_time / 1000.0f;
	displacement = c.tiles_per_sec * c.dt;
	displacement *= game->player.player_speed_multiplier;
	if (strafing_diagonally)
		displacement /= 1.4f;
	change_player_mov_helper(game, &nx, &ny, displacement);
}

static void	change_player_mov_helper(t_game *game, float *nx,
				float *ny, float displacement)
{
	if (game->player.player_mov_left)
	{
		*ny += game->player.player_delta_x * displacement;
		*nx -= game->player.player_delta_y * displacement;
	}
	else if (game->player.player_mov_right)
	{
		*ny -= game->player.player_delta_x * displacement;
		*nx += game->player.player_delta_y * displacement;
	}
	if (game->player.player_mov_forward)
	{
		*nx -= game->player.player_delta_x * displacement;
		*ny -= game->player.player_delta_y * displacement;
	}
	else if (game->player.player_mov_backward)
	{
		*nx += game->player.player_delta_x * displacement;
		*ny += game->player.player_delta_y * displacement;
	}
	if (is_colision(game, *nx, *ny) == false)
	{
		game->player.pos_x = *nx;
		game->player.pos_y = *ny;
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
