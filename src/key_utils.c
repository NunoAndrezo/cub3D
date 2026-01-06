/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:06:38 by joaoleote         #+#    #+#             */
/*   Updated: 2026/01/05 01:13:11 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	handle_speed_keys(int key_sym, t_game *game)
{
	if (key_sym == XK_plus || key_sym == XK_equal)
	{
		game->player.player_speed_multiplier += 0.1f;
		if (game->player.player_speed_multiplier > 4.0f)
			game->player.player_speed_multiplier = 4.0f;
	}
	if (key_sym == XK_minus)
	{
		game->player.player_speed_multiplier -= 0.1f;
		if (game->player.player_speed_multiplier < 0.1f)
			game->player.player_speed_multiplier = 0.1f;
	}
}

static void	handle_rot_mult_keys(int key_sym, t_game *game)
{
	if (key_sym == XK_bracketright)
	{
		game->player.player_rot_multiplier += 0.1f;
		if (game->player.player_rot_multiplier > 4.0f)
			game->player.player_rot_multiplier = 4.0f;
	}
	if (key_sym == XK_bracketleft)
	{
		game->player.player_rot_multiplier -= 0.1f;
		if (game->player.player_rot_multiplier < 0.1f)
			game->player.player_rot_multiplier = 0.1f;
	}
}

void	handle_key_press(int key_sym, t_game *game)
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
	handle_speed_keys(key_sym, game);
	handle_rot_mult_keys(key_sym, game);
}

void	handle_key_release(int key_sym, t_game *game)
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
}
