/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player_mov_and_rot_helper.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:44:32 by nuno              #+#    #+#             */
/*   Updated: 2026/01/06 15:40:50 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	is_colision(t_game *game, float nx, float ny)
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

void	initiate_cpm(t_cpm *c)
{
	c->base_per_update = 0.0f;
	c->dt = 0.0f;
	c->updates_per_sec = 0.0f;
	c->tiles_per_sec = 0.0f;
	c->updates_per_sec = 1000.0f / 16.0f;
}
