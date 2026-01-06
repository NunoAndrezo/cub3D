/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:07:36 by nuno              #+#    #+#             */
/*   Updated: 2026/01/06 15:08:49 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	check_player(t_game *game);

bool	map_is_valid(t_game *game)
{
	if (check_player(game) && flood_fill(game))
		return (true);
	perror("Error\nMap is invalid.\n");
	free_game(game);
	exit(EXIT_FAILURE);
}

bool	last_map_adjustments(t_game *game)
{
	int	j;
	int	max_len;

	max_len = find_max_len(game);
	j = 0;
	while (j < game->map.y_max)
	{
		if (!pad_row_to_max(game, j, max_len))
			return (false);
		j++;
	}
	game->map.x_max = max_len;
	return (true);
}

void	handle_map_char(t_game *game, char c, t_map_ctx *ctx)
{
	if (is_player_char(c))
	{
		ctx->player_count++;
		game->map.player_orientation = c;
		game->map.player_start_x = ctx->x;
		game->map.player_start_y = ctx->y;
	}
	if (!is_valid_map_char(c))
	{
		perror("Error\nInvalid character in map.\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
}

static bool	check_player(t_game *game)
{
	t_map_ctx	ctx;

	ctx.y = 0;
	ctx.player_count = 0;
	while (game->map.map[ctx.y])
	{
		ctx.x = 0;
		while (game->map.map[ctx.y][ctx.x])
		{
			handle_map_char(game, game->map.map[ctx.y][ctx.x], &ctx);
			ctx.x++;
		}
		ctx.y++;
	}
	if (ctx.player_count != 1)
		return (false);
	return (true);
}
