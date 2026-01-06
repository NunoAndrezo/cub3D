/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3d_game_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:43:25 by nuno              #+#    #+#             */
/*   Updated: 2026/01/04 23:14:16 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	calculate_projection(t_game *g, t_column *col)
{
	float	corrected;
	float	player_rad;
	int		line_h;

	player_rad = deg_to_rad(g->player.player_angle);
	corrected = col->dist * cosf(col->angle - player_rad);
	if (corrected < 0.0001f)
		corrected = 0.0001f;
	line_h = (int)(g->image.height / corrected);
	col->line_h = line_h;
	if (line_h < 2)
		return (0);
	col->start = -line_h / 2 + g->image.height / 2;
	col->end = line_h / 2 + g->image.height / 2;
	if (col->start < 0)
		col->start = 0;
	if (col->end >= g->image.height)
		col->end = g->image.height - 1;
	return (1);
}

void	draw_floor_and_ceiling(t_game *game, int x, int start, int end)
{
	int	y;

	y = 0;
	while (y < start)
	{
		my_store_pixel_in_image(&game->image, x, y,
			rgb_to_color(game->textures.ceiling_color));
		y++;
	}
	y = end + 1;
	while (y < game->image.height)
	{
		my_store_pixel_in_image(&game->image, x, y,
			rgb_to_color(game->textures.floor_color));
		y++;
	}
}
