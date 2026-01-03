/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3d_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoleote <joaoleote@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:14:41 by joaoleote         #+#    #+#             */
/*   Updated: 2026/01/02 18:51:48 by joaoleote        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_3Dgame(t_game *game, float angle, float best_dist,
					int hit_side, int column_index)
{
	int	x;
	int	draw_start;
	int	draw_end;
	int	wall_color;

	x = column_index;
	if (x < 0 || x >= game->image.width)
		return;
	if (!calculate_projection(game, angle, best_dist, &draw_start, 
		&draw_end))
		return;
	wall_color = choose_wall_color(hit_side);
	draw_floor_and_ceiling(&game->image, x, draw_start, draw_end, game);
	draw_wall(&game->image, x, draw_start, draw_end, wall_color, game);
}

int	calculate_projection(t_game *g, float ray_angle, float dist,
						int *start, int *end)
{
	float	corrected;
	float	player_rad;
	int		line_h;

	player_rad = deg_to_rad(g->player.player_angle);
	corrected = dist * cosf(ray_angle - player_rad);
	if (corrected < 0.0001f)
		corrected = 0.0001f;

	line_h = (int)(g->image.height / corrected);
	if (line_h < 2)
		return (0);
	if (line_h > g->image.height)
		line_h = g->image.height;

	*start = -line_h / 2 + g->image.height / 2;
	*end   =  line_h / 2 + g->image.height / 2;
	if (*start < 0)
		*start = 0;
	if (*end >= g->image.height)
		*end = g->image.height - 1;
	return (1);
}

int	choose_wall_color(int hit_side)
{
	if (hit_side == 0)
		return (0x888888);
	return (0xBBBBBB);
}

void	draw_floor_and_ceiling(t_img *img, int x, int start, int end, t_game *game)
{
	int	y;

	y = 0;
	while (y < start)
	{
		my_store_pixel_in_image(img, x, y, rgb_to_color(game->textures.ceiling_color)); // instead of this, we will use ceiling color
		y++;
	}
	y = end + 1;
	while (y < img->height)
	{
		my_store_pixel_in_image(img, x, y, rgb_to_color(game->textures.floor_color)); // instead of this, we will use floor color
		y++;
	}
}

void	draw_wall(t_img *img, int x, int start, int end, int color, t_game *game)
{
	int	y;

	y = start;
	(void)game;
	while (y <= end)
	{
		my_store_pixel_in_image(img, x, y, color); // instead of this, we will use texture mapping
		y++;
	}
}
