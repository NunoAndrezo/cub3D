/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_game_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 23:32:07 by joaoleote         #+#    #+#             */
/*   Updated: 2026/01/04 23:35:52 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_player_angle(t_game *game)
{
	if (game->player.dir == 'N')
		game->player.player_angle = 270.0f;
	else if (game->player.dir == 'S')
		game->player.player_angle = 90.0f;
	else if (game->player.dir == 'E')
		game->player.player_angle = 0.0f;
	else if (game->player.dir == 'W')
		game->player.player_angle = 180.0f;
}
